#include "server.h"

Server::Server() {
    svInfo = nullptr;
    flag = rc = err = 0;
    //Start winsock
    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
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
    freeaddrinfo(svInfo);
    WSACleanup();
}

bool Server::addClientSocket(const SOCKET& newClient) {
    socketList.push_back(SocketInfo(newClient));
    if (WSAEventSelect(socketList.back().socket, socketList.back().handler, FD_WRITE | FD_READ | FD_CLOSE) == SOCKET_ERROR) {
        cerr << "Unable to track client " << socketList.size() - 1 << " events. This connection will be closed. Error code: " << WSAGetLastError() << endl;
        
    }
    
}

bool Server::init() {
    //Reserve the server capacity
    //First socket is for accepting connections
    socketList.reserve(WSA_MAXIMUM_WAIT_EVENTS);
    shouldRefresh.reserve(WSA_MAXIMUM_WAIT_EVENTS - 1);
    //Construct a listen socket
    SOCKET temp = INVALID_SOCKET;
    temp = socket(svInfo->ai_family, svInfo->ai_socktype, svInfo->ai_protocol);
    if (temp == INVALID_SOCKET) {
        err = WSAGetLastError();
        throw NetworkException("Can't create listening socket", err);
        return false;
    }
    socketList.push_back(SocketInfo(temp));
    rc = WSAEventSelect(socketList[0].socket, socketList[0].handler, FD_ACCEPT | FD_CLOSE);
    if (rc == SOCKET_ERROR) {
        throw NetworkException("WSAEventSelect() failed", WSAGetLastError());
        return false;
    }
    //Bind the listening socket to the server address
    rc = bind(socketList[0].socket, svInfo->ai_addr, (int)svInfo->ai_addrlen);
    if (rc == SOCKET_ERROR) {
        throw NetworkException("Unable to bind server address", WSAGetLastError());
        return false;
    }
    //Begin listening
    rc = listen(socketList[0].socket, BACKLOG);
    if (rc == SOCKET_ERROR) {
        throw NetworkException("Can't listen to connections", WSAGetLastError());
        return false;
    }
    return true;
}

bool Server::acceptConnects() {

}