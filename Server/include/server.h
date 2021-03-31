#ifndef SERVER_H
#define SERVER_H


#include "soci.h"
#include "odbc/soci-odbc.h"
#include "socketwrapper.h"
#include <mswsock.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

using namespace soci;
using namespace std;

#define PORT "10201"
#define BACKLOG 10

class Server {
private:
    char buffer[2048];
    //First socket is for listening
    vector<SocketInfo> socketList;
    //Event handler list
    vector<WSAEVENT> eventList;
    //Keeping info about whether a client should refresh or not, size = clientlist - 1
    vector<bool> shouldRefresh;
    WSADATA wsaData;
    addrinfo *svInfo;
    DWORD flag;
    int rc, err; //result code and error code
    //List of all messages the server can handle from clients
    enum class Msg {Idle = '\0', Listing = '1', Insert = '2'};
    //Add a new client socket to the server
    bool addClientSocket(SOCKET newClient);
    //Remove a socket from the server
    bool removeSocket(int index);
    //TODO: NEED A MEMBER CLASS TO HANDLE GRAPHIC INTERFACE
    //TODO: NEED A CLASS TO HANDLE DATABASE PROCESSES
public:
    //Start Winsock and get server address, construct LiveScore Database connector and GUI
    Server();
    //Shutdown server, free address list
    ~Server();
    //Create & bind listen socket, begin listening
    bool init();
    //Accept new client connections
    bool acceptConnects();
    //Record client messages/requests, get data inputs from client and modify the database
    int recvMsg(SocketInfo& client, char msg);
    //Handle client message, send query results/feedbacks/notifications back to clients
    int sendMsg(SocketInfo &client);
    //Handle network events
    //Return 0 = success, 1 = ignorable error, otherwise = heavy error
    int handleNetEvents();
    //TODO: Handle program inputs/events, NEED GUI
    //TODO: Display program window, NEED GUI
};

#endif