#include "socketwrapper.h"

SocketInfo::SocketInfo(SOCKET s) : socket(s), byteRecv(0), byteSend(0), lastMsg('\0') {
    buf.reserve(BUFSIZE);
    dataBuf.buf = nullptr;
    dataBuf.len = 0;
}

void SocketInfo::setBuffer(char *newBuf, size_t newLen) {
    buf.resize(newLen);
    if (newBuf != nullptr)
        buf.assign(newBuf, newBuf + newLen);
    dataBuf.buf = &buf[0];
    dataBuf.len = buf.size();
}

void SocketInfo::appendBuffer(char *data, size_t len) {
    dataBuf.buf = (&buf[0]) + buf.size();
    dataBuf.len = len;
    buf.resize(buf.size() + len);
    if (data != nullptr)
        buf.insert(buf.end(), data, data + len);
}

bool SocketInfo::extractBuffer(char *extBuf, size_t extLen) {
    if (extLen > buf.size())
        return false;
    if (extBuf != nullptr) {
        std::copy(buf.begin(), buf.begin() + extLen, extBuf);
    }
    buf.erase(buf.begin(), buf.begin() + extLen);
    if (buf.empty()) {
        dataBuf.buf = nullptr;
        dataBuf.len = 0;
    }
    else {
        dataBuf.buf = &buf[0];
        dataBuf.len = buf.size();
    }
    return true;
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