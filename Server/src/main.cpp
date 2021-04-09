#include "server.h"

int main() {
   try {
      Server server("DRIVER=ODBC Driver 17 for SQL Server;DATABASE=DB_LIVESCORE;SERVER=localhost;Trusted_Connection=Yes");
      server.init();
      while (true) {
         int iSock = server.pollNetEvents();
         if (iSock == -1)
            break;
         else {
            if (server.acceptConnects() == -1)
               break;
            if (iSock > 0) {
               char rCode;
               if (server.recvData(iSock, &rCode, sizeof(char)))
                  cout << "Client sends " << rCode << endl;
               server.handleRequest(rCode, iSock);
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
