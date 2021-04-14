#include "server.h"
#include <cstring>
int main(int argc, char** argv) {
   try {
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
      Server server(dbString, bindIP);
      server.init();
      while (true) {
         int result = -100;
         int iSock = server.pollNetEvents();
         if (iSock == -1)
            break;
         if (server.acceptConnects() == -1)
            break;
         if (server.canRecv()) {
            char rCode = '0';
            server.recvData(iSock, &rCode, sizeof(char));
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
         server.closeConnection(iSock);
      }
   }
   catch (const exception& e) {
      cerr << "Error: " << e.what() << endl;
   }
   return 0;
}
