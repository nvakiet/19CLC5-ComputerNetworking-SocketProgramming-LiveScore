#include "server.h"

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
         dbString = argv[2];
      }
      Server server(dbString, bindIP);
      server.init();
      while (true) {
         int iSock = server.pollNetEvents();
         if (iSock == -1)
            break;
         else if (iSock == 0) {
            if (server.acceptConnects() == -1)
               break;
         }
         else {
            char rCode = '0';
            server.recvData(iSock, &rCode, sizeof(char));
            if (server.handleRequest(rCode, iSock) == -1) {
               cerr << "Failed to execute request code " << rCode << " from client socket " << iSock << endl;
            }
            server.closeConnection(iSock);
         }

      }
   }
   catch (const NetworkException& e) {
      cerr << e.what() << endl;
   }
   catch (const exception& e) {
      cerr << "Error: " << e.what() << endl;
   }
   return 0;
}
