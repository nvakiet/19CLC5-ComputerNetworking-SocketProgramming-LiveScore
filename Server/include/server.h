#ifndef SERVER_H
#define SERVER_H

#include "DB_Manager.h"
#include "socketwrapper.h"
#include <mswsock.h>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

#define PORT "10201"
#define BACKLOG 10

class Server {
private:
    DB_Manager db;
    //First socket is for listening
    vector<SocketInfo*> socketList;
    //Event handler list
    vector<WSAEVENT> eventList;
    //Current network event
    WSANETWORKEVENTS netEvent;
    //Keeping info about whether a client should refresh or not, size = clientlist - 1
    vector<bool> shouldRefresh;
    //Keeping info about client accounts
    vector<User> accounts;
    WSADATA wsaData;
    addrinfo *svInfo;
    int rc, err; //result code and error code
    //Add a new client socket to the server
    bool addClientSocket(SOCKET newClient);
    //Remove a socket from the server
    bool removeSocket(int index, bool willLogout = true);
public:
    //List of all messages the server can handle from clients
    enum Msg {Login = '1', Register = '2'};
    //Start Winsock and get server address, construct LiveScore Database connector and GUI
    Server(const string& connectString, const char* ipAddr = nullptr);
    //Shutdown server, free address list
    ~Server();
    //Create & bind listen socket, begin listening
    bool init();
    //Poll network events
    //Return -1: error, >= 0: socket index
    int pollNetEvents();
    //Accept new client connections
    //Return -1: error, 0: no accept event, 1: success accept
    int acceptConnects();
    //Check if the FD_READ is triggered, -1 = error, 0 = not triggered, 1 = triggered
    int canRecv();
    //Check if the FD_WRITE is triggered, -1 = error, 0 = not triggered, 1 = triggered
    int canSend();
    //Receive message from client, if buf = null, function uses default buffer of socketwrapper
    int recvData(int sockIndex, char *buf = nullptr, size_t dataSize = BUFSIZE, bool isContinuous = false);
    //Send data to client, if buf = null, function uses default buffer of socketwrapper
    int sendData(int sockIndex, char *buf = nullptr, size_t dataSize = BUFSIZE);
    //Close client socket if the client closes its connection
    //Return 1: the socket is closed; 0: No signal to close; -1: Error while trying to close
    int closeConnection(int sockIndex);
    //Handle requests from client
    int handleRequest(char rCode, int iSock);
    //Handle sending feedback to clients
    bool handleFeedback(int iSock);
    //Perform login operation with a client socket
    //On success, will return the user info, server must send admin status info back to client
    bool loginClient(int iSock, User& user);
    //Perform register account
    //Return operation result to the client
    bool registerAccount(int iSock);
};

#endif