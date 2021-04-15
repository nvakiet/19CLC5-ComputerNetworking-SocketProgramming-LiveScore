#include "server.h"
#include <cstring>

bool isRunning = true;
Server *ptr = nullptr;

BOOL WINAPI OnExit(DWORD dwCtrlType) {
   if (CTRL_CLOSE_EVENT == dwCtrlType) {
      isRunning = false;
      ptr->OnExit();
      Sleep(500);
      return true;
   }
   return false;
}

int main(int argc, char** argv) {
   char *bindIP = nullptr;
   string dbString = "";
   if (argc > 3) {
      cerr << "Wrong command line arguments. Usage: [server.exe] [Ip address of server] [Database Connection String]" << endl;
      return 1;
   }
   if (argc >= 2) {
      bindIP = argv[1];
   }
   if (argc == 3) {
      int argvLen = strlen(argv[2]);
      dbString.assign(argv[2], argv[2] + argvLen);
   }
   if (FALSE == SetConsoleCtrlHandler(OnExit, TRUE)) {
      cerr << "Unable to setup exit routine for the program. Error: " << GetLastError() << endl;
      return 1;
   }
   try {
      Server server(dbString, bindIP);
      ptr = &server;
      server.init();
      while (isRunning) {
         int result = -100;
         int iSock = server.pollNetEvents();
         if (iSock == -1)
            break;
         if (server.acceptConnects() == -1)
            break;
         if (server.canRecv()) {
            char rCode = '0';
            try {
               server.recvData(iSock, &rCode, sizeof(char));
            } catch (const NetworkException& err) {
               cerr << err.what() << endl;
               cerr << "Received invalid request code." << endl;
               continue;
            }
            
            result = server.handleRequest(rCode, iSock);
            if (result == -1) {
               cerr << "Failed to execute request code " << rCode << " from client socket " << iSock << endl;
               continue;
            }   
         }
         if (result == 1) {
            if (!server.handleFeedback(iSock)) {
               cerr << "Failed to send feedback to client socket number " << iSock << endl;
               continue;
            }
         }
         if (server.canClose()) {
            if (!server.closeConnection(iSock)) {
               cerr << "Unable to close socket " << iSock << ". The program will be terminated." << endl;
               break;
            }
         }
      }
   }
   catch (const exception& e) {
      cerr << "Error: " << e.what() << endl;
   }
   return 0;
}
