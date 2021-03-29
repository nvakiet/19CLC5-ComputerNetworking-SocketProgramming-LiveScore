#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <exception>
#include <memory>
using namespace std;

const int BUFSIZE = 1024;

//Simple socket wrapper class for Overlapped I/O Model
class SocketInfo {
public:
    shared_ptr<char> buf;
    size_t len;
    SOCKET socket;
    int byteSend;
    int byteRecv;
    char lastMsg; //The most recent message from socket
    SocketInfo(const SOCKET& s);
    SocketInfo(const SocketInfo &sInf);
    SocketInfo &operator=(SocketInfo sInf);
    void setBuffer(char *newBuf, size_t newLen);
    ~SocketInfo();
};

class NetworkException : public exception {
    private:
        string errString;
    public:
        NetworkException(const string &err, int code);
        const char* what() const noexcept override;
};

#endif