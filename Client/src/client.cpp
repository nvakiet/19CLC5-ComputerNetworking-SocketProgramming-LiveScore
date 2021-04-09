#include "client.h"

Client::Client() {
    int rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc != 0) {
        throw NetworkException("WSAStartup failed with error", rc);
    }
    conInfo = nullptr;
    connector = INVALID_SOCKET;
    handler = WSA_INVALID_EVENT;
    dataBuf.buf = buffer;
    dataBuf.len = DEFAULT_BUFLEN;
}

Client::~Client() {
    if (handler != WSA_INVALID_EVENT)
        WSACloseEvent(handler);
    if (connector != INVALID_SOCKET) {
        shutdown(connector, SD_BOTH);
        closesocket(connector);
    }
    WSACleanup();
}

bool Client::connectTo(const string& svIP) {
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
    for (ptr = conInfo; ptr != nullptr ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        connector = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (connector == INVALID_SOCKET) {
            cerr << "Socket failed with error: " << WSAGetLastError() << endl;
            return false;
        }
        rc = 0;
        // Connect to server.
        rc = connect(connector, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (rc == SOCKET_ERROR) {
            closesocket(connector);
            connector = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(conInfo);
    //If can't connect after trying all addresses
    if (connector == INVALID_SOCKET) {
        cerr << "Unable to connect to server! Error " << WSAGetLastError() << endl;
        return false;
    }
    //Create an event handler for the socket
    handler = WSACreateEvent();
    if (handler == WSA_INVALID_EVENT) {
        cerr << "Can't create event handle for connection, error " << WSAGetLastError() << endl;
        return false;
    }
    //Tell the handler to notify about read/write/close events
    rc = WSAEventSelect(connector, handler, FD_READ | FD_WRITE | FD_CLOSE);
    if (rc == SOCKET_ERROR) {
        cerr << "WSAEventSelect() failed, error " << WSAGetLastError() << endl;
        return false;
    }

    return true;
}

bool Client::pollNetworkEvents() {
    if (connector == INVALID_SOCKET || handler == WSA_INVALID_EVENT)
        return false;
    int rc = 0;
    rc = WSAEnumNetworkEvents(connector, handler, &netEvent);
    if (rc == SOCKET_ERROR) {
        cerr << "Can't enumerate network events, error " << WSAGetLastError() << endl;
        return false;
    }
    return true;
}

bool Client::hasMsgFromServer() const {
    return (netEvent.lNetworkEvents & FD_READ);
}

bool Client::sendData(char *buf, size_t dataSize, DWORD& bSent) {
    //Check whether the server is ready to receive data from client
    // if (!(netEvent.lNetworkEvents & FD_WRITE))
    //     return false;
    // if (netEvent.iErrorCode[FD_WRITE_BIT] != 0) {
    //     cerr << "FD_WRITE failed, error " << netEvent.iErrorCode[FD_WRITE_BIT] << endl;
    //     return false;
    // }
    //Set the buffer containing data to send
    if (dataSize == 0) {
        cerr << "There's nothing to send! Data size can't be 0!" << endl;
        return false;
    }
    if (buf == nullptr)
        dataBuf.buf = buffer;
    else
        dataBuf.buf = buf;
    dataBuf.len = dataSize;
    int rc = WSASend(connector, &dataBuf, 1, &bSent, 0, nullptr, nullptr);
    if (rc == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
        cerr << "Something went wrong while sending data to server, error " << WSAGetLastError() << endl;
        WSACloseEvent(handler);
        closesocket(connector);
        handler = WSA_INVALID_EVENT;
        connector = INVALID_SOCKET;
        return false;
    }
    return true;
}

bool Client::recvData(char *retBuf, size_t retSize, DWORD& bRecv) {
    //Check whether the client is ready to receive data from server
    if (!(netEvent.lNetworkEvents & FD_READ))
        return false;
    if (netEvent.iErrorCode[FD_READ_BIT] != 0) {
        cerr << "FD_READ failed, error " << netEvent.iErrorCode[FD_READ_BIT] << endl;
        return false;
    }
    //Set the buffer containing data to receive
    if (retSize == 0) {
        cerr << "There's nothing to receive! Data size can't be 0!" << endl;
        return false;
    }
    if (retBuf == nullptr)
        dataBuf.buf = buffer;
    else
        dataBuf.buf = retBuf;
    dataBuf.len = retSize;
    DWORD flag = 0;
    int rc = WSARecv(connector, &dataBuf, 1, &bRecv, &flag, nullptr, nullptr);
    if (rc == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
        cerr << "Something went wrong while receiving data from server, error " << WSAGetLastError() << endl;
        WSACloseEvent(handler);
        closesocket(connector);
        handler = WSA_INVALID_EVENT;
        connector = INVALID_SOCKET;
        return false;
    }
    return true;
}

int Client::closeConnection() {
    if (connector == INVALID_SOCKET)
        return 1;
    if (netEvent.lNetworkEvents & FD_CLOSE) {
        if (netEvent.iErrorCode[FD_CLOSE_BIT] != 0) {
            cerr << "Server has been shutdown incorrectly, error " << netEvent.iErrorCode[FD_CLOSE_BIT] << endl;
            return -1;
        }
        shutdown(connector, SD_BOTH);
        closesocket(connector);
        WSACloseEvent(handler);
        connector = INVALID_SOCKET;
        handler = WSA_INVALID_EVENT;
        return 1;
    }
    return 0;
}

bool Client::login(const string &username, const string &password) {
    char rCode = '1';
    DWORD bSend = 0;
    //Send command
    if (!sendData(&rCode, sizeof(char), bSend)) return false;
    //Send username
    size_t expectedSize = username.size();
    if (!sendData((char *)&expectedSize, sizeof(size_t), bSend)) return false;
    if (!sendData((char *)username.c_str(), expectedSize, bSend)) return false;
    //Send password
    expectedSize = password.size();
    if (!sendData((char *)&expectedSize, sizeof(size_t), bSend)) return false;
    if (!sendData((char *)password.c_str(), expectedSize, bSend)) return false;
    cout << username << endl;
    cout << password << endl;
    return true;
}

bool Client::registerAcc(const string &username, const string &password) {
    return true;
}

NetworkException::NetworkException(const string &err, int code) {
    errString = err;
    errString += " - Error code: " + to_string(code);
}

const char* NetworkException::what() const noexcept {
    return errString.c_str();
}

bool Client::isAdminAccount(){
    return isAdmin;
}