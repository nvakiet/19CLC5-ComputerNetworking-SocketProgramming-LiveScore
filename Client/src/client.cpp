#include "client.h"




NetworkException::NetworkException(const string &err, int code) {
    errString = err;
    errString += " - Error code: " + to_string(code);
}

const char* NetworkException::what() const noexcept {
    return errString.c_str();
}