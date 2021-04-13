#include "GUI.h"

bool MyApp::OnInit()
{
    client = new Client();
    lframe = new LoginFrame(client, NULL, wxID_ANY, _("Live Score"), wxPoint(550, 250), wxSize(500, 300));
    lframe->Show(true);
    t = new thread(socketHandling, this);
    return true;
}
int MyApp::OnExit(wxCloseEvent& event)
{
    t->join();
    client->closeConnection();
    delete client;
    delete lframe;
    delete mframe;
    delete df_admin;
    delete df_client;
    delete t;
    close(true);
}

void MyApp::showMainFrame()
{
    mframe = new MainFrame(client, NULL);
    mframe->Show(true);
}

void MyApp::socketHandling() {
    //While the app is still opening
    while (GetTopWindow() != nullptr) {
        //Poll event returns false when there are connection error
        if (!client->pollNetworkEvents())
            continue;
        //If there's data to read from server
        if (client->canRecv()) {
            char rCode = '0';
            int step = 0;
            while (step == 0)
                step += client->recvData(&rCode, sizeof(char));
            switch (rCode) {
                case '1':
                    //The server send back login result
                    while (step == 1)
                        step += client->recvData((char*)&client->result, 4);
                    if (client->result == 0) {
                        while (step == 2)
                            step += client->recvData((char*)&(client->account.isAdmin), sizeof(bool));
                    }
                    if ((client->result == 0 && step != 3) || ((client->result == -1 || client->result == 1) && step != 2)) {
                        cerr << "Failed to receive login result" << endl;
                        client->setMsg('0');
                    }
                    else client->setMsg('1');
                    break;
                default:
                    cerr << rCode << " is invalid request code." << endl;
                    client->setMsg(rCode);
            }
            if (step < 0) {
                client->closeConnection();
                continue;
            }
        }
        //Handle connection close event
        if (client->canClose()) {
            client->closeConnection();
            //DISPLAY A WINDOW SAYING CONNECTION TO SERVER HAS BEEN CLOSED
            //THEN FORCE CLOSE PROGRAM OR RETURN TO LOGIN FRAME
        }
    }
}