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
#include "socketwrapper.h"
#include "DB_Structs.h"
using namespace std;

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "10201"

class Client
{
protected:
    WSAEVENT handler;
    
    WSANETWORKEVENTS netEvent;
    addrinfo *conInfo;
    WSADATA wsaData;

public:
    SocketInfo* connector;
    User account;
    int result;
    size_t extractSize;
    //List of all messages the server can handle from clients
    enum Msg {Pending = '0', Login = '1', Register = '2', Matches = '3'};
    //Start winsock
    Client();
    //Log out the account, close socket and clean up winsock, connection infos
    ~Client();
    //Connect to the server IP
    bool connectTo(const string &svIP);
    //Check for network events from the connection
    bool pollNetworkEvents();
    //Check if the FD_READ is triggered, -1 = error, 0 = not triggered, 1 = triggered
    int canRecv();
    //Check if the FD_WRITE is triggered, -1 = error, 0 = not triggered, 1 = triggered
    int canSend();
    //Receive message from client, if buf = null, function uses default buffer of socketwrapper
    void recvData(char *buf = nullptr, size_t dataSize = DEFAULT_BUFLEN, bool isContinuous = true);
    //Send data to client, if buf = null, function uses default buffer of socketwrapper
    void sendData(char *buf = nullptr, size_t dataSize = DEFAULT_BUFLEN, bool isContinuous = true);
    //Check if can close connection
    bool canClose();
    //Close connection
    void closeConnection();
    //Log in to the server
    bool login(const string &username, const string &password,string& notif);
    //Register a new account to the server
    bool registerAcc(const string &username, const string &password, string& notif);
    //Request a list of matches from the server
    bool requestMatches();
    //Extract the match list from the buffer
    void extractMatches(ListMatch *&list);
    // Check if client 
    bool isAdminAccount();
    //Check if the socket is valid
    bool isInvalid();
    // Set Msg received from server
    void setMsg(char c);
    // Get the recorded message
    char getMsg();
};

#endif