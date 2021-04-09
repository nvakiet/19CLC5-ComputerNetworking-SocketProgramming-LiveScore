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
    bool removeSocket(int index);
public:
    //List of all messages the server can handle from clients
    //enum class Msg {Idle = '0', Login = '1', Register = '2'};
    //Start Winsock and get server address, construct LiveScore Database connector and GUI
    Server(const string& connectString);
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
    //Receive message from client, if buf = null, function uses default buffer of socketwrapper
    bool recvData(int sockIndex, char *buf = nullptr, size_t dataSize = BUFSIZE);
    //Send data to client, if buf = null, function uses default buffer of socketwrapper
    bool sendData(int sockIndex, char *buf = nullptr, size_t dataSize = BUFSIZE);
    //Close client socket if the client closes its connection
    //Return 1: the socket is closed; 0: No signal to close; -1: Error while trying to close
    int closeConnection(int sockIndex);
    //Handle requests from client
    //Return: -1: Error while handling request/invalid request; 0: Request is done successfully; 1: Request is done and makes change to server data/requires feedbacks to client
    int handleRequest(char rCode, int iSock);
    //Perform login operation with a client socket
    //On success, will return the user info, server must send this info back to client
    int loginClient(int iSock, User& user);
};

#endif