#include "GUI.h"

bool MyApp::OnInit()
{
    client = new Client();
    lframe = new LoginFrame(client, NULL, wxID_ANY, _("Live Score"), wxPoint(550, 250), wxSize(500, 300));
    lframe->Show(true);
    t = new thread(socketHandling, this);
    return true;
}
int MyApp::OnExit()
{
    t->join();
    client->closeConnection();
    delete client;
    lframe->Close();
    mframe->Close();
    df_admin->Close();
    df_client->Close();
    delete t;
    close(true);
    return 0;
}

void MyApp::showMainFrame()
{
    mframe = new MainFrame(client, NULL);
    mframe->Show(true);
}


void MyApp::displayNotif(const wxString &notif) {
    wxMessageBox(notif, wxT("Message"),
                 wxOK | wxICON_INFORMATION);
}

void MyApp::socketHandling() {
    wxWindow *currentWindow = nullptr;
    //While the app is still opening
    while ((currentWindow = GetTopWindow()) != nullptr) {
        //Poll event returns false when there are connection error
        if (!client->pollNetworkEvents())
            continue;
        //If there's data to read from server
        if (client->canRecv()) {
            char rCode = '0';
            int step = 0;
            while (step == 0)
                step += client->recvData(&rCode, sizeof(char), true);
            switch (rCode) {
                case Client::Login:
                    //The server send back login result
                    client->result = -100;
                    while (step == 1)
                        step += client->recvData((char*)&(client->result), sizeof(int), true);
                    if (client->result == 0) {
                        while (step == 2)
                            step += client->recvData((char*)&(client->account.isAdmin), sizeof(bool), true);
                    }
                    if ((client->result == 0 && step != 3) || ((client->result == -1 || client->result == 1) && step != 2)) {
                        cerr << "Failed to receive login result" << endl;
                    }
                    client->setMsg(Client::Login);
                    break;
                case Client::Register:
                    //The server send back login result
                    client->result = -100;
                    while (step == 1)
                        step += client->recvData((char*)&(client->result), sizeof(int), false);
                    if (step != 2) {
                        cerr << "Failed to receive register result" << endl;
                    }
                    client->setMsg(Client::Register);
                    break;
                default:
                    cerr << "Invalid request code." << endl;
                    client->setMsg('\0');
                    client->closeConnection();
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
            //THEN FORCE CLOSE PROGRAM OR RETURN TO LOGIN FRAME OR ALLOW USER VIEW MATCHES, WITHOUT REFRESH
        }
    }
}

