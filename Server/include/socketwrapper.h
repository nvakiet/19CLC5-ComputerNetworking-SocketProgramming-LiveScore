#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <exception>
using namespace std;

const int BUFSIZE = 1024;

//Simple socket wrapper class for Event-based I/O Model
class SocketInfo {
public:
    char* buf;
    int size;
    //Data buffer either points to this object buffer or some externally managed object
    WSABUF dataBuf;
    SOCKET socket;
    DWORD byteSend;
    DWORD byteRecv;
    char lastMsg; //The most recent message from socket
    SocketInfo(SOCKET s);
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