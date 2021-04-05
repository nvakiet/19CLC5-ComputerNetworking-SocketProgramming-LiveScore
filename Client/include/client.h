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
#include "sha256.h" //For password enscription
using namespace std;

#define DEFAULT_BUFLEN 1024
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
    //Check if server is sending some message to the client
    bool hasMsgFromServer() const;
    //Send data to the server, input nullptr = using client's default buffer, return number of bytes sent
    bool sendData(char *buf, size_t dataSize, DWORD& bSent);
    //Receive data from server, input nullptr = using client's default buffer, return number of bytes received
    bool recvData(char *retBuf, size_t retSize, DWORD& bRecv);
    //If the server disconnected, close the socket and set it to invalid to prevent other functions from working
    //Return: 1 = Server or Client has shutdown connection (could be due to some errors), 0 = Connecting normally, -1 = Error when trying to close connection
    int closeConnection();
    //Log in to the server
    bool login(const string &username, const string &password);
    //Register a new account to the server
    bool registerAcc(const string &username, const string &password);
};

class NetworkException : public exception {
    private:
        string errString;
    public:
        NetworkException(const string &err, int code);
        const char* what() const noexcept override;
};

#endif