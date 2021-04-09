// #include "client.h"
// int main() 
// {
//     Client client;
//     client.connectTo("192.168.1.5");
//     while (true) {
//         if (!client.pollNetworkEvents())
//             break;
//         // string username;
//         // getline(cin, username);
//         // string password;
//         // getline(cin, password);
//         if (!client.login("admin", "admin")) cerr << "Failed to login." << endl;
//         int rc = client.closeConnection();
//         if (rc != 0)
//             break;
//     }
//     return 0;
// }

#include"GUI.h"
wxIMPLEMENT_APP(MyApp);
