#include "client.h"

Client::Client() {
    int rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc != 0) {
        throw NetworkException("WSAStartup failed with error", rc);
    }
    conInfo = nullptr;
    connector = nullptr;
    handler = WSA_INVALID_EVENT;
    result = -100;
    extractSize = 0;
}

Client::~Client() {
    if (handler != WSA_INVALID_EVENT)
        WSACloseEvent(handler);
    if (connector->socket != INVALID_SOCKET) {
        shutdown(connector->socket, SD_BOTH);
        closesocket(connector->socket);
    }
    delete connector;
    WSACleanup();
}

bool Client::connectTo(const string& svIP) {
    //If the socket is already connected
    if (connector != nullptr && connector->socket != INVALID_SOCKET)
        return true;
    int rc = 0;
    addrinfo hints, *ptr = nullptr;
    ZeroMemory(&hints, sizeof(hints)) ;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    rc = getaddrinfo(svIP.c_str(), DEFAULT_PORT, &hints, &conInfo);
    if (rc != 0) {
        cerr << "getaddrinfo failed with error: " << rc << endl;
        return false;
    }
    // Attempt to connect to an address until one succeeds
    SOCKET temp = INVALID_SOCKET;
    for (ptr = conInfo; ptr != nullptr ;ptr=ptr->ai_next) {
        // Create a SOCKET for connecting to server
        temp = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (temp == INVALID_SOCKET) {
            cerr << "Socket failed with error: " << WSAGetLastError() << endl;
            return false;
        }
        rc = 0;
        // Connect to server.
        rc = connect(temp, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (rc == SOCKET_ERROR) {
            closesocket(temp);
            temp = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(conInfo);
    //If can't connect after trying all addresses
    if (temp == INVALID_SOCKET) {
        cerr << "Unable to connect to server! Error " << WSAGetLastError() << endl;
        return false;
    }
    //Create socket info
    if (connector != nullptr)
        delete connector;
    connector = new SocketInfo(temp);
    //Create an event handler for the socket
    handler = WSACreateEvent();
    if (handler == WSA_INVALID_EVENT) {
        cerr << "Can't create event handle for connection, error " << WSAGetLastError() << endl;
        return false;
    }
    //Tell the handler to notify about read/write/close events
    rc = WSAEventSelect(connector->socket, handler, FD_READ | FD_WRITE | FD_CLOSE);
    if (rc == SOCKET_ERROR) {
        cerr << "WSAEventSelect() failed, error " << WSAGetLastError() << endl;
        return false;
    }

    return true;
}

bool Client::pollNetworkEvents() {
    if (connector == nullptr || connector->socket == INVALID_SOCKET || handler == WSA_INVALID_EVENT)
        return false;
    int rc = 0;
    // rc = WSAEventSelect(connector->socket, handler, FD_READ | FD_WRITE | FD_CLOSE);
    // if (rc == SOCKET_ERROR) {
    //     cerr << "WSAEventSelect() failed, error " << WSAGetLastError() << endl;
    //     return false;
    // }
    rc = WSAEnumNetworkEvents(connector->socket, handler, &netEvent);
    if (rc == SOCKET_ERROR) {
        cerr << "Can't enumerate network events, error " << WSAGetLastError() << endl;
        return false;
    }
    return true;
}


int Client::canRecv() {
    if (!(netEvent.lNetworkEvents & FD_READ))
        return 0;
    if (netEvent.iErrorCode[FD_READ_BIT] != 0) {
        cerr << "FD_READ failed, error " << netEvent.iErrorCode[FD_READ_BIT] << endl;
        return -1;
    }
    return 1;
}


void Client::recvData(char *buf, size_t dataSize, bool isContinuous) {
    //Set the buffer for receiving
    if (dataSize == 0) {
        cerr << "Can't receive data size 0." << endl;
        return;
    }
    DWORD flag = 0;
    DWORD bRecv = 0;
    if (isContinuous) {
        connector->byteRecv = 0;
    }
    if (buf == nullptr) {
        if (connector->buf.empty()) {
            connector->buf.reserve(2 * dataSize);
            connector->buf.resize(dataSize);
            connector->dataBuf.buf = &(connector->buf[0]);
            connector->dataBuf.len = dataSize;
        }
        else {
            connector->appendBuffer(nullptr, dataSize);
        }
    }
    else {
        connector->dataBuf.buf = buf;
        connector->dataBuf.len = dataSize;
    }
    //Receive data into socket buffer
    do {
        int rc = WSARecv(connector->socket, &connector->dataBuf, 1, &bRecv, &flag, nullptr, nullptr);
        if (rc == SOCKET_ERROR) {
            if (WSAGetLastError() != WSAEWOULDBLOCK) {
                //cerr << "Something went wrong while receiving data from client, error " << WSAGetLastError() << endl;
                throw NetworkException("Something went wrong while receiving data from client, error ", WSAGetLastError());
            }
            else { //If WSAEWOULDBLOCK, wait for a while then try again
                Sleep(100);
                continue;
            }
        }
        connector->byteRecv += bRecv;
        connector->dataBuf.buf += bRecv;
        connector->dataBuf.len -= bRecv;
    } while (isContinuous && connector->byteRecv < dataSize);
}

void Client::sendData(char *buf, size_t dataSize, bool isContinuous) {
    //Set the buffer containing data to send
    if (dataSize == 0) {
        cerr << "Can't send data size 0." << endl;
        return;
    }
    DWORD bSend = 0;
    if (isContinuous) {
        connector->byteSend = 0;
    }
    if (buf != nullptr) {
        connector->setBuffer(buf, dataSize);
    }
    else {
        connector->dataBuf.buf = &connector->buf[0];
        connector->dataBuf.len = dataSize;
    }
    do {
        int rc = WSASend(connector->socket, &connector->dataBuf, 1, &bSend, 0, nullptr, nullptr);
        if (rc == SOCKET_ERROR) {
            if (WSAGetLastError() != WSAEWOULDBLOCK) {
                //cerr << "Something went wrong while receiving data from client, error " << WSAGetLastError() << endl;
                throw NetworkException("Something went wrong while sending data to client, error ", WSAGetLastError());
            }
            else { //If WSAEWOULDBLOCK, wait for a while to call this function again
                Sleep(100);
                continue;
            }
        }
        connector->byteSend += bSend;
        connector->dataBuf.buf += bSend;
        connector->dataBuf.len -= bSend;
    } while (isContinuous && connector->byteSend < dataSize);
    //Flush the send buffer after finished
    if (buf != nullptr)
        connector->extractBuffer(nullptr, dataSize);
}

bool Client::canClose() {
    if (connector == nullptr)
        return false;
    if (connector->socket != INVALID_SOCKET && (netEvent.lNetworkEvents & FD_CLOSE))
        return true;
    return false;
}

void Client::closeConnection() {
    shutdown(connector->socket, SD_SEND);
    closesocket(connector->socket);
    WSACloseEvent(handler);
    connector->socket = INVALID_SOCKET;
    handler = WSA_INVALID_EVENT;
}

bool Client::login(const string &username, const string &password, string& notif) {
    if (username.empty() || password.empty()) {
        notif = "Username and password can't be empty. Try again.";
        connector->lastMsg = '\0';
        return false;
    }
    char rCode = Msg::Login;
    connector->lastMsg = Msg::Pending;
    try {
        //Send command
        sendData(&rCode, sizeof(char));
        //Send username
        size_t expectedSize = username.size();
        sendData((char *)&expectedSize, sizeof(size_t));
        sendData((char *)username.c_str(), expectedSize);
        //Send password
        string encrypted(sha256(password));
        expectedSize = encrypted.size();
        sendData((char *)&expectedSize, sizeof(size_t));
        sendData((char *)encrypted.c_str(), expectedSize);
    } catch (const NetworkException& e) {
        notif = "Failed to send login info to server";
        return false;
    }
    account.username = username;
    return true;
}

bool Client::registerAcc(const string &username, const string &password, string& notif) {
    if (username.empty() || password.empty()) {
        notif = "Username and password can't be empty. Try again.";
        connector->lastMsg = '\0';
        return false;
    }
    char rCode = Msg::Register;
    connector->lastMsg = Msg::Pending;
    try {
        //Send command
        sendData(&rCode, sizeof(char));
        //Send username
        size_t expectedSize = username.size();
        sendData((char *)&expectedSize, sizeof(size_t));
        sendData((char *)username.c_str(), expectedSize);
        //Send password
        string encrypted(sha256(password));
        expectedSize = encrypted.size();
        sendData((char *)&expectedSize, sizeof(size_t));
        sendData((char *)encrypted.c_str(), expectedSize);
    } catch (const NetworkException& e) {
        notif = "Failed to send login info to server";
        return false;
    }

    return true;
}

bool Client::requestMatches() {
    if (isInvalid()) {
        cerr << "Connection has been closed." << endl;
        return false;
    }
    if (connector->lastMsg == Msg::Pending) {
        cerr << "Client is busy. Try again" << endl;
        return false;
    }
    connector->lastMsg = Msg::Pending;
    char rCode = Msg::Matches;
    try {
        sendData(&rCode, sizeof(char));
    } catch (const NetworkException& e) {
        cerr << e.what() << endl;
        return false;
    }
    return true;
}

void Client::extractMatches(ListMatch *&list) {
    vector<char> byteStream;
    byteStream.resize(extractSize);
    connector->extractBuffer(&byteStream[0], extractSize);
    if (list != nullptr) {
        delete list;
    }
    list = new ListMatch(byteStream);
}

bool Client::isAdminAccount(){
    return account.isAdmin;
}

void Client::setMsg(char c) {
    connector->lastMsg = c;
}

char Client::getMsg() {
    return connector->lastMsg;
}

bool Client::isInvalid() {
    return (connector == nullptr || connector->socket == INVALID_SOCKET || handler == WSA_INVALID_EVENT);
}

bool Client::requestDetails(const string& ID) {
    if (isInvalid()) {
        cerr << "Connection has been closed." << endl;
        return false;
    }
    if (connector->lastMsg == Msg::Pending) {
        cerr << "Client is busy. Try again" << endl;
        return false;
    }
    connector->lastMsg = Msg::Pending;
    char rCode = Msg::Details;
    try {
        size_t IDlen = ID.size();
        sendData(&rCode, sizeof(char));
        sendData((char *)&IDlen, sizeof(size_t));
        sendData((char *)ID.c_str(), IDlen);
    } catch (const NetworkException& e) {
        cerr << e.what() << endl;
        return false;
    }
    return true;
}

void Client::extractDetails(const string& ID, MatchDetails *&details) {
    for (int i = 0; i < detailQ.IDs.size(); ++i) {
        if (ID == detailQ.IDs[i]) {
            if (details != nullptr)
                delete details;
            details = new MatchDetails(detailQ.buffers[i]);
            return;
        }
    }
}