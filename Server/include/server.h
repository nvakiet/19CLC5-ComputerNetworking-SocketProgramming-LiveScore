#ifndef SERVER_H
#define SERVER_H


#include "soci.h"
#include "odbc/soci-odbc.h"
#include "socketwrapper.h"
#include <mswsock.h>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace soci;
using namespace std;

#define PORT "10201"
#define BACKLOG 10

class Server {
private:
    //First socket is for listening
    vector<SocketInfo> socketList;
    vector<bool> shouldRefresh; //Keeping info about whether a client should refresh or not, size = clientlist - 1
    WSADATA wsaData;
    addrinfo *svInfo;
    DWORD flag;
    int rc, err; //result code and error code
    //List of all messages the server can handle from clients
    enum class Msg {Idle = '\0', Listing = '1', Change = '2'};
    //Add a new client socket to the server
    bool addClientSocket(const SOCKET& newClient);
    //Remove a socket from the server
    bool removeSocket(int index);
    //TODO: NEED A MEMBER CLASS TO HANDLE GRAPHIC INTERFACE
public:
    //Start Winsock and get server address, construct LiveScore Database connector and GUI
    Server();
    //Shutdown server, free address list
    ~Server();
    //Create & bind listen socket, begin listening
    bool init();
    //Accept new client connections
    bool acceptConnects();
    //Handle network events
    int handleEvents();
    //Handle client messages
    int handleMsg(SocketInfo& client, char msg);
    //Execute client messages
    int executeMsg(SocketInfo &client);
    //TODO: Handle program input, NEED GUI
    //TODO: Display program window, NEED GUI
};

#endif