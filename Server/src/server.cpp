#include "server.h"

Server::Server() {
    svInfo = nullptr;
    flag = rc = err = 0;
    //Start winsock
    rc = WSAStartup(0x0202, &wsaData);
    if (rc != 0) {
        throw NetworkException("WSAStartup failed", rc);
    }
    //Get server address in localhost
    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    rc = getaddrinfo(nullptr, PORT, &hints, &svInfo);
    if (rc != 0) {
        throw NetworkException("Can't get server address", rc);
    }
    //Begin connecting the server to database
    //Construct the GUI
}

Server::~Server() {
    for (int i = socketList.size() - 1; i >= 0; --i)
    {
        removeSocket(i);
    }
    freeaddrinfo(svInfo);
    WSACleanup();
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
    return true;
}

bool Server::removeSocket(int index) {
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
    }
    return true;
}

bool Server::init() {
    //Reserve the server capacity
    //First socket is for accepting connections
    socketList.reserve(WSA_MAXIMUM_WAIT_EVENTS);
    eventList.reserve(WSA_MAXIMUM_WAIT_EVENTS);
    shouldRefresh.reserve(WSA_MAXIMUM_WAIT_EVENTS - 1);
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
        cerr << "Can't create event handle for listening, error " << endl;
        return false;
    }
    rc = WSAEventSelect(socketList[0]->socket, eventList[0], FD_ACCEPT | FD_CLOSE);
    if (rc == SOCKET_ERROR) {
        cerr << "WSAEventSelect() failed, error " << WSAGetLastError() << endl;
        return false;
    }
    //Bind the listening socket to the server address
    rc = bind(socketList[0]->socket, svInfo->ai_addr, (int)svInfo->ai_addrlen);
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

bool Server::acceptConnects() {
    SOCKET newClient = accept(socketList[0]->socket, nullptr, nullptr);
    if (newClient == INVALID_SOCKET) {
        cerr << "Client acception failed, error " << WSAGetLastError() << endl;
        return false;
    }
    if (socketList.size() == WSA_MAXIMUM_WAIT_EVENTS) {
        cerr << "Too many connections - closing new socket..." << endl;
        closesocket(newClient);
        return false;
    }
    if (!addClientSocket(newClient))
        return false;
    return true;
}

int Server::handleNetEvents() {
    //Wait for a socket to trigger an event
    int eventIndex = WSAWaitForMultipleEvents(eventList.size(), eventList.data(), false, WSA_INFINITE, false);
    if (eventIndex == WSA_WAIT_FAILED) {
        err = WSAGetLastError();
        cerr << "Waiting for multiple events failed, error " << err << endl;
        return err;
    }
    int iSock = eventIndex - WSA_WAIT_EVENT_0;
    WSANETWORKEVENTS netEvent;
    //Check the type of triggered event
    rc = WSAEnumNetworkEvents(socketList[iSock]->socket, eventList[iSock], &netEvent);
    if (rc == SOCKET_ERROR) {
        err = WSAGetLastError();
        cerr << "Can't enumerate network events, error" << err << endl;
        return err;
    }
    //Accept signal
    if (netEvent.lNetworkEvents & FD_ACCEPT && iSock == 0) {
        if (netEvent.iErrorCode[FD_ACCEPT_BIT] != 0) {
            cerr << "FD_ACCEPT failed, error " << netEvent.iErrorCode[FD_ACCEPT_BIT] << endl;
            return 1;
        }
        if (!acceptConnects()) {
            cerr << "Failed to accept new connection." << endl;
            return 1;
        }
        cout << "Client " << socketList.size() - 1 << " has connected." << endl;
    }
    DWORD bRecv = 0, bSend = 0;
    flag = 0;
    err = 0;
    //The client is sending something to the server
    if (netEvent.lNetworkEvents & FD_READ) {
        if (netEvent.lNetworkEvents & FD_READ && netEvent.iErrorCode[FD_READ_BIT] != 0) {
            cerr << "FD_READ failed, error " << netEvent.iErrorCode[FD_READ_BIT] << endl;
            return 1;
        }
        //TODO: MAKE CLIENT-SERVER COMMUNICATION SEQUENCE IN HERE
        //Testing: a multiclient chat server that will relay the message from one client to others
        socketList[iSock]->dataBuf.buf = buffer;
        socketList[iSock]->dataBuf.len = 2048;
        rc = WSARecv(socketList[iSock]->socket, &socketList[iSock]->dataBuf, 1, &bRecv, &flag, nullptr, nullptr);
        if (rc == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
            //If the receive error is not due to out of buffer space
            cerr << "Something went wrong while receiving data from client, error " << WSAGetLastError() << endl;
            removeSocket(iSock);
            return 1;
        }
        // if (bRecv == 0) {
        //     cerr << "Client " << iSock << " disconnected" << endl;
        //     removeSocket(iSock);
        //     return 1;
        // }
        cout << "Client " << iSock << " sent \"" << buffer << "\"" << endl;
        for (int i = 1; i < socketList.size(); ++i) {
            if (i == iSock) {
                continue;
            }
            socketList[i]->dataBuf.buf = buffer;
            socketList[i]->dataBuf.len = bRecv;
            rc = WSASend(socketList[i]->socket, &socketList[i]->dataBuf, 1, &bSend, 0, nullptr, nullptr);
            if (rc == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
                //If the receive error is not due to out of buffer space
                cerr << "Something went wrong while sending data to client " << i << ", error " << WSAGetLastError() << endl;
                removeSocket(i);
                err = 1;
            }
            cout << "Echo message back to client " << i << endl;
        }
    }

    //Close signal
    if (netEvent.lNetworkEvents & FD_CLOSE) {
        // if (netEvent.iErrorCode[FD_CLOSE_BIT] != 0) {
        //     cerr << "FD_CLOSE failed with error " << netEvent.iErrorCode[FD_CLOSE_BIT] << endl;
        //     return 1;
        // }
        shutdown(socketList[iSock]->socket, SD_BOTH);
        if (!removeSocket(iSock)) {
            cerr << "Can't remove socket " << iSock << endl;
            return 1;
        }
        cout << "Socket " << iSock << " disconnected" << endl;
    }
    return err;
    //The client is waiting for something from the server
}