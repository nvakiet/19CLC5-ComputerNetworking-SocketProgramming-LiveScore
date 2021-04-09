#include "client.h"
int main() 
{
    Client client;
    client.connectTo("localhost");
    while (true) {
        if (!client.pollNetworkEvents())
            break;
        string temp;
        getline(cin, temp);
        client.login("admin", "123");
        int rc = client.closeConnection();
        if (rc != 0)
            break;
    }
    return 0;
}

// #include"GUI.h"
// wxIMPLEMENT_APP(MyApp);
