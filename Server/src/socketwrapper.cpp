#include "socketwrapper.h"

SocketInfo::SocketInfo(SOCKET s) : buf(new char[BUFSIZE]), size(BUFSIZE), socket(s), byteRecv(0), byteSend(0), lastMsg('\0') {
    dataBuf.buf = nullptr;
    dataBuf.len = 0;
}

SocketInfo::SocketInfo(const SocketInfo &sInf) : size(sInf.size), socket(sInf.socket), byteRecv(sInf.byteRecv), byteSend(sInf.byteSend), lastMsg(sInf.lastMsg){
    buf = new char[size];
    for (int i = 0; i < size; ++i) {
        buf[i] = sInf.buf[i];
    }
    if (sInf.dataBuf.buf == sInf.buf) {
        dataBuf.buf = buf;
        dataBuf.len = size;
    }
    else
        dataBuf = sInf.dataBuf;
}

SocketInfo& SocketInfo::operator=(SocketInfo sInf) {
    swap(socket, sInf.socket);
    swap(buf, sInf.buf);
    swap(size, sInf.size);
    swap(dataBuf, sInf.dataBuf);
    swap(byteSend, sInf.byteSend);
    swap(byteRecv, sInf.byteRecv);
    swap(lastMsg, sInf.lastMsg);
    return *this;
}

void SocketInfo::setBuffer(char *newBuf, size_t newLen) {
    if (newBuf != buf) {
        delete[] buf;
        buf = new char[newLen];
        for (int i = 0; i < newLen; ++i)
            buf[i] = newBuf[i];
        size = newLen;
    }
}

SocketInfo::~SocketInfo() {
    delete[] buf;
    dataBuf.buf = nullptr;
    buf = nullptr;
    if (closesocket(socket) == SOCKET_ERROR)
        throw NetworkException("Can't close socket", WSAGetLastError());
}

// WSA_EVENT::WSA_EVENT() {
//     handler = WSACreateEvent();
// }

// WSA_EVENT::~WSA_EVENT() {
//     WSACloseEvent(handler);
// }

NetworkException::NetworkException(const string &err, int code) {
    errString = err;
    errString += " - Error code: " + to_string(code);
}

const char* NetworkException::what() const noexcept {
    return errString.c_str();
}