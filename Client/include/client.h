#ifndef CLIENT_H
#define CLIENT_H
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <thread>

using namespace std;

#define DEFAULT_BUFLEN 2048
#define DEFAULT_PORT "10201"

class Client {
protected:
    SOCKET connector;
    WSAEVENT handler;
    WSANETWORKEVENTS netEvent;
    //Buffer for sending requests to server/receiving feedbacks from server
    char buffer[DEFAULT_BUFLEN];
    WSABUF dataBuf;
    addrinfo *conInfo;
    WSADATA wsaData;

public:
    //Start winsock
    Client();
    //Log out the account, close socket and clean up winsock, connection infos
    ~Client();
    //Connect to the server IP
    bool connectTo(const string &svIP);
    //Check for network events from the connection
    bool pollNetworkEvents();
    //Log in to the server
    bool login(const string &username, const string &password);
    //Register a new account to the server
    bool registerAcc(const string &username, const string &password);
    //If the server disconnected, close the socket and set it to invalid to prevent other functions from working
    bool closeConnection();
    //Send data to the server
    bool sendData(char *buf, size_t dataSize);
    //Receive data from server
    bool recvData(char *retBuf, size_t retSize);
    
};

class NetworkException : public exception {
    private:
        string errString;
    public:
        NetworkException(const string &err, int code);
        const char* what() const noexcept override;
};

#endif