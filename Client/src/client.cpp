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
 bool Client::connectTo(const string &svIP)
 {
     
 }
 bool Client::login(const string &username, const string &password){
      
 }
bool Client::registerAcc(const string &username, const string &password)
{
    
}
NetworkException::NetworkException(const string &err, int code) {
    errString = err;
    errString += " - Error code: " + to_string(code);
}

const char* NetworkException::what() const noexcept {
    return errString.c_str();
}