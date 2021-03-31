#include "server.h"

int main() {
   try {
      Server server;
      server.init(); 
      while (true) {
         int rc = server.handleNetEvents();
         if (rc != 0 && rc != 1) {
            cerr << "Something went wrong while handling network events!" << endl;
            break;
         }
      }
   }
   catch (const NetworkException& e) {
      cerr << e.what() << endl;
   }
   return 0;
}