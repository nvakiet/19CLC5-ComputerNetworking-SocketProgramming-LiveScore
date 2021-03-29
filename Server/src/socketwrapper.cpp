#include "socketwrapper.h"

SocketInfo::SocketInfo(const SOCKET& s) {
    socket = s;
    buf = nullptr;
    len = 0;
    byteSend = 0;
    byteRecv = 0;
    lastMsg = '\0';
}

SocketInfo::SocketInfo(const SocketInfo &sInf) {
    socket = sInf.socket;
    buf = sInf.buf;
    len = sInf.len;
    byteSend = sInf.byteSend;
    byteRecv = sInf.byteRecv;
    lastMsg = sInf.lastMsg;
}

SocketInfo& SocketInfo::operator=(SocketInfo sInf) {
    swap(socket, sInf.socket);
    swap(buf, sInf.buf);
    swap(len, sInf.len);
    swap(byteSend, sInf.byteSend);
    swap(byteRecv, sInf.byteRecv);
    swap(lastMsg, sInf.lastMsg);
}

void SocketInfo::setBuffer(char *newBuf, size_t newLen) {
    shared_ptr<char> temp(newBuf);
    buf = temp;
    len = newLen;
}

SocketInfo::~SocketInfo() {
    if (closesocket(socket) == SOCKET_ERROR)
        throw NetworkException("Can't close socket", WSAGetLastError());
}

NetworkException::NetworkException(const string &err, int code) {
    errString = err;
    errString += " - Error code: " + to_string(code);
}

const char* NetworkException::what() const noexcept {
    return errString.c_str();
}