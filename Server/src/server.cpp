#include "server.h"

Server::Server(const string& connectString, const char* ipAddr) : db(connectString) {
    svInfo = nullptr;
    rc = err = 0;
    //Start winsock
    rc = WSAStartup(0x0202, &wsaData);
    if (rc != 0) {
        throw NetworkException("WSAStartup failed", rc);
    }
    //Get server address
    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    rc = getaddrinfo(ipAddr, PORT, &hints, &svInfo);
    if (rc != 0) {
        throw NetworkException("Can't get server address", rc);
    }
}

// Server::~Server() {
//     for (int i = socketList.size() - 1; i >= 0; --i)
//     {
//         removeSocket(i);
//     }
//     freeaddrinfo(svInfo);
//     WSACleanup();
//     db.logoutAll();
// }

void Server::OnExit() {
    for (int i = socketList.size() - 1; i >= 0; --i)
    {
        removeSocket(i);
    }
    freeaddrinfo(svInfo);
    WSACleanup();
    db.logoutAll();
}

bool Server::addClientSocket(SOCKET newClient) {
    socketList.push_back(new SocketInfo(newClient));
    eventList.push_back(WSACreateEvent());
    if (WSAEventSelect(socketList.back()->socket, eventList.back(), FD_WRITE | FD_READ | FD_CLOSE) == SOCKET_ERROR) {
        cerr << "Unable to track client " << socketList.size() - 1 << " events. This connection will be closed. Error code: " << WSAGetLastError() << endl;
        socketList.pop_back();
        WSACloseEvent(eventList.back());
        eventList.pop_back();
        return false;
    }
    shouldRefresh.push_back(false);
    accounts.push_back(User());
    return true;
}

bool Server::removeSocket(int index, bool willLogout) {
    if (index < 0 || index >= socketList.size()) {
        cerr << "Invalid socket index" << endl;
        return false;
    }
    closesocket(socketList[index]->socket);
    delete socketList[index];
    socketList.erase(socketList.begin() + index);
    WSACloseEvent(eventList[index]);
    eventList.erase(eventList.begin() + index);
    if (index > 0) {
        shouldRefresh.erase(shouldRefresh.begin() + index - 1);
        if (willLogout) {
            db.logoutUser(accounts[index - 1].username);
        }
        accounts.erase(accounts.begin() + index - 1);
    }
    cout << "Socket " << index << " is removed" << endl;
    cout << "Current client number: " << socketList.size() - 1 << endl;
    return true;
}

bool Server::init() {
    //Reserve the server capacity
    //First socket is for accepting connections
    socketList.reserve(WSA_MAXIMUM_WAIT_EVENTS);
    eventList.reserve(WSA_MAXIMUM_WAIT_EVENTS);
    shouldRefresh.reserve(WSA_MAXIMUM_WAIT_EVENTS - 1);
    accounts.reserve(WSA_MAXIMUM_WAIT_EVENTS - 1);
    //Construct a listen socket
    SOCKET temp = socket(svInfo->ai_family, svInfo->ai_socktype, svInfo->ai_protocol);
    if (temp == INVALID_SOCKET) {
        err = WSAGetLastError();
        cerr << "Can't create listening socket, error " << err << endl;
        return false;
    }
    socketList.push_back(new SocketInfo(temp));
    eventList.push_back(WSACreateEvent());
    if (eventList[0] == WSA_INVALID_EVENT) {
        cerr << "Can't create event handle for listening, error " << WSAGetLastError() << endl;
        return false;
    }
    rc = WSAEventSelect(socketList[0]->socket, eventList[0], FD_ACCEPT);
    if (rc == SOCKET_ERROR) {
        cerr << "WSAEventSelect() failed, error " << WSAGetLastError() << endl;
        return false;
    }
    //Bind the listening socket to the server address
    rc = bind(socketList[0]->socket, svInfo->ai_addr, svInfo->ai_addrlen);
    if (rc == SOCKET_ERROR) {
        cerr <<"Unable to bind server address, error " << WSAGetLastError() << endl;
        return false;
    }
    //Begin listening
    rc = listen(socketList[0]->socket, BACKLOG);
    if (rc == SOCKET_ERROR) {
        cerr << "Can't listen to connections, error " << WSAGetLastError() << endl;
        return false;
    }
    return true;
}

int Server::pollNetEvents() {
    //Wait for a socket to trigger an event
    int eventIndex = WSAWaitForMultipleEvents(eventList.size(), eventList.data(), false, WSA_INFINITE, false);
    if (eventIndex == WSA_WAIT_FAILED) {
        err = WSAGetLastError();
        cerr << "Waiting for multiple events failed, error " << err << endl;
        return -1;
    }
    int iSock = eventIndex - WSA_WAIT_EVENT_0;
    //Check the type of triggered event
    rc = WSAEnumNetworkEvents(socketList[iSock]->socket, eventList[iSock], &netEvent);
    if (rc == SOCKET_ERROR) {
        err = WSAGetLastError();
        cerr << "Can't enumerate network events, error" << err << endl;
        return -1;
    }
    return iSock;
}

int Server::acceptConnects() {
    //Check accept signal
    if (netEvent.lNetworkEvents & FD_ACCEPT) {
        if (netEvent.iErrorCode[FD_ACCEPT_BIT] != 0) {
            cerr << "FD_ACCEPT failed, error " << netEvent.iErrorCode[FD_ACCEPT_BIT] << endl;
            return -1;
        }
        SOCKET newClient = accept(socketList[0]->socket, nullptr, nullptr);
        if (newClient == INVALID_SOCKET) {
            cerr << "Client acception failed, error " << WSAGetLastError() << endl;
            return -1;
        }
        if (socketList.size() == WSA_MAXIMUM_WAIT_EVENTS) {
            cerr << "Too many connections - closing new socket..." << endl;
            closesocket(newClient);
            return 0;
        }
        if (!addClientSocket(newClient))
            return -1;
        cout << "New client connection accepted. Current number: " << socketList.size() - 1 << endl;
        return 1;
    }
    return 0;
}

int Server::canRecv() {
    //Check whether the server is ready to receive data from client
    if (!(netEvent.lNetworkEvents & FD_READ))
        return 0;
    if (netEvent.iErrorCode[FD_READ_BIT] != 0) {
        cerr << "FD_READ failed, error " << netEvent.iErrorCode[FD_READ_BIT] << endl;
        return -1;
    }
    return 1;
}

void Server::recvData(int sockIndex, char *buf, size_t dataSize, bool isContinuous) {
    //Set the buffer for receiving
    if (dataSize == 0) {
        cerr << "Can't receive data size 0." << endl;
        return;
    }
    DWORD flag = 0;
    DWORD bRecv = 0;
    if (isContinuous) {
        socketList[sockIndex]->byteRecv = 0;
    }
    if (buf == nullptr) {
        socketList[sockIndex]->buf.reserve(2 * dataSize);
        socketList[sockIndex]->buf.resize(dataSize);
        socketList[sockIndex]->dataBuf.buf = &(socketList[sockIndex]->buf[0]);
        socketList[sockIndex]->dataBuf.len = dataSize;
    }
    else {
        socketList[sockIndex]->dataBuf.buf = buf;
        socketList[sockIndex]->dataBuf.len = dataSize;
    }
    //Receive data into socket buffer
    do {
        rc = WSARecv(socketList[sockIndex]->socket, &socketList[sockIndex]->dataBuf, 1, &bRecv, &flag, nullptr, nullptr);
        if (rc == SOCKET_ERROR) {
            if (WSAGetLastError() != WSAEWOULDBLOCK) {
                //cerr << "Something went wrong while receiving data from client, error " << WSAGetLastError() << endl;
                removeSocket(sockIndex);
                throw NetworkException("Something went wrong while receiving data from client, error ", WSAGetLastError());
            }
            else { //If WSAEWOULDBLOCK, wait for a while then try again
                Sleep(100);
                continue;
            }
        }
        socketList[sockIndex]->byteRecv += bRecv;
        socketList[sockIndex]->dataBuf.buf += bRecv;
        socketList[sockIndex]->dataBuf.len -= bRecv;
    } while (isContinuous && socketList[sockIndex]->byteRecv < dataSize);
}

int Server::canSend() {
    //Check whether the client is ready to receive data from server
    if (!(netEvent.lNetworkEvents & FD_WRITE))
        return 0;
    if (netEvent.iErrorCode[FD_WRITE_BIT] != 0) {
        cerr << "FD_WRITE failed, error " << netEvent.iErrorCode[FD_WRITE_BIT] << endl;
        return -1;
    }
    return 1;
}

void Server::sendData(int sockIndex, char *buf, size_t dataSize, bool isContinuous) {
    //Set the buffer containing data to send
    if (dataSize == 0) {
        cerr << "Can't send data size 0." << endl;
        return;
    }
    DWORD bSend = 0;
    if (isContinuous) {
        socketList[sockIndex]->byteSend = 0;
    }
    if (buf != nullptr) {
        socketList[sockIndex]->setBuffer(buf, dataSize);
    }
    else {
        socketList[sockIndex]->dataBuf.buf = &socketList[sockIndex]->buf[0];
        socketList[sockIndex]->dataBuf.len = dataSize;
    }
    do {
        rc = WSASend(socketList[sockIndex]->socket, &socketList[sockIndex]->dataBuf, 1, &bSend, 0, nullptr, nullptr);
        if (rc == SOCKET_ERROR) {
            if (WSAGetLastError() != WSAEWOULDBLOCK) {
                //cerr << "Something went wrong while receiving data from client, error " << WSAGetLastError() << endl;
                removeSocket(sockIndex);
                throw NetworkException("Something went wrong while sending data to client, error ", WSAGetLastError());
            }
            else { //If WSAEWOULDBLOCK, wait for a while to call this function again
                Sleep(100);
                continue;
            }
        }
        socketList[sockIndex]->byteSend += bSend;
        socketList[sockIndex]->dataBuf.buf += bSend;
        socketList[sockIndex]->dataBuf.len -= bSend;
    } while (isContinuous && socketList[sockIndex]->byteSend < dataSize);
    //Flush the send buffer after finished
    if (buf != nullptr)
        socketList[sockIndex]->extractBuffer(nullptr, dataSize);
}

bool Server::canClose() {
    if (netEvent.lNetworkEvents & FD_CLOSE)
        return true;
    return false;
}

bool Server::closeConnection(int sockIndex) {
    if (socketList[sockIndex]->socket == INVALID_SOCKET)
        return true;
    cout << "Closing connection with socket " << sockIndex << endl;
    if (!removeSocket(sockIndex)) {
        cerr << "Failed to remove socket " << sockIndex  << endl;
        return false;
    }
    return true;
}

bool Server::loginClient(int iSock, User& user) {
    rc = -100;
    size_t expectedSize = 0;
    string username, password;
    //Receive the username and password from client
    try {
        recvData(iSock, (char *)&expectedSize, sizeof(size_t), true); //Username length
        username.resize(expectedSize);
        recvData(iSock, nullptr, expectedSize, true); //Username
        socketList[iSock]->extractBuffer(&username[0], expectedSize);
        recvData(iSock, (char *)&expectedSize, sizeof(size_t), true); //Password length
        password.resize(expectedSize);
        recvData(iSock, nullptr, expectedSize, true); //Password
        socketList[iSock]->extractBuffer(&password[0], expectedSize);
    } catch (const NetworkException& e) {
        cerr << e.what() << endl;
        cerr << "Failed to receive username and password from client " << iSock << endl;
        return false;
    }
    //Query the account in the database
    rc = db.queryUser(username, password, user);
    socketList[iSock]->setBuffer((char*)&rc, sizeof(int));
    return true;
}

bool Server::registerAccount(int iSock) {
    rc = -100;
    size_t expectedSize = 0;
    string username, password;
    //Receive the username and password from client
    try {
        recvData(iSock, (char *)&expectedSize, sizeof(size_t), true); //Username length
        username.resize(expectedSize);
        recvData(iSock, nullptr, expectedSize, true); //Username
        socketList[iSock]->extractBuffer(&username[0], expectedSize);
        recvData(iSock, (char *)&expectedSize, sizeof(size_t), true); //Password length
        password.resize(expectedSize);
        recvData(iSock, nullptr, expectedSize, true); //Password
        socketList[iSock]->extractBuffer(&password[0], expectedSize);
    } catch (const NetworkException& e) {
        cerr << e.what() << endl;
        cerr << "Failed to receive username and password from client " << iSock << endl;
        return false;
    }
    //Query the account in the database
    rc = db.insertUser(username, password);
    socketList[iSock]->setBuffer((char*)&rc, sizeof(int));
    return true;
}

int Server::handleRequest(char rCode, int iSock) {
    //HANDLE LOGIN REQUEST
    if (rCode == Msg::Login) {
        socketList[iSock]->lastMsg = rCode;
        cout << "Socket " << iSock << " is logging into an account..." << endl;
        if (loginClient(iSock, accounts[iSock - 1])) {
            return 1;
        }
        else {
            cerr << "Client socket " << iSock << " failed to login. Server will close this socket." << endl;
            removeSocket(iSock);
            return -1;
        }
    }
    //HANDLE REGISTER REQUEST
    if (rCode == Msg::Register) {
        socketList[iSock]->lastMsg = rCode;
        cout << "Socket " << iSock << " is registering a new account..." << endl;
        if (registerAccount(iSock)) {
            return 1;
        }
        else {
            cerr << "Client socket " << iSock << " failed to register. Server will close this socket." << endl;
            removeSocket(iSock);
            return -1;
        }
    }
    if (rCode == Msg::Matches) {
        socketList[iSock]->lastMsg = rCode;
        cout << "User " << accounts[iSock - 1].username << " is requesting match list" << endl;
        return 1;
    }
    return 0;
}

bool Server::handleFeedback(int iSock) {
    int result = -100;
    //LOGIN RESULT
    if (socketList[iSock]->lastMsg == Msg::Login) {
        socketList[iSock]->extractBuffer((char*)&result, sizeof(int));
        try {
            sendData(iSock, &socketList[iSock]->lastMsg, sizeof(char));
            sendData(iSock, (char*)&result, sizeof(int));
            if (result == 0)
                sendData(iSock, (char*)&(accounts[iSock - 1].isAdmin), sizeof(bool));
        } catch (const NetworkException& e) {
            cerr << e.what() << endl;
            cerr << "Failed to feedback login result to client " << iSock << ". Socket will be removed." << endl;
            removeSocket(iSock);
            return false;
        }
        if (result != 0) {
            cerr << "Failed to login account " << accounts[iSock - 1].username << ". Socket " << iSock << " will be closed." << endl;
            removeSocket(iSock, false);
            return true;
        }
        socketList[iSock]->lastMsg = Msg::Pending;
        return true;
    }
    //REGISTER RESULT
    if (socketList[iSock]->lastMsg == Msg::Register) {
        socketList[iSock]->extractBuffer((char*)&result, sizeof(int));
        try {
            sendData(iSock, &socketList[iSock]->lastMsg, sizeof(char));
            sendData(iSock, (char*)&result, sizeof(int));
        } catch (const NetworkException& e) {
            cerr << e.what() << endl;
            cerr << "Failed to feedback register result to client " << iSock << ". Socket will be removed." << endl;
            removeSocket(iSock);
            return false;
        }
        if (result != 0) {
            cerr << "Failed to register account for client " << iSock << ". Socket " << iSock << " will be closed." << endl;
            removeSocket(iSock);
            return true;
        }
        socketList[iSock]->lastMsg = Msg::Pending;
        return true;
    }
    //MATCH LIST QUERY RESULT
    if (socketList[iSock]->lastMsg == Msg::Matches) {
        ListMatch list;
        db.queryMatches(list);
        vector<char> bytes;
        list.toByteStream(bytes);
        size_t byteSize = bytes.size();
        try {
            sendData(iSock, &socketList[iSock]->lastMsg, sizeof(char));
            sendData(iSock, (char *)&byteSize, sizeof(size_t));
            //cout << "Expected Size " << byteSize << endl;
            sendData(iSock, &bytes[0], byteSize);
            //cout << "Sent " << socketList[iSock]->byteSend << endl;
        } catch (const NetworkException& e) {
            cerr << e.what() << endl;
            cerr << "Failed to send match list to user " << accounts[iSock - 1].username << ". Connection will be closed." << endl;
            removeSocket(iSock);
            return false;
        }
        cout << "Match list has been sent to user " << accounts[iSock - 1].username << endl;
        socketList[iSock]->lastMsg = Msg::Pending;
        return true;
    }
    return true;
}