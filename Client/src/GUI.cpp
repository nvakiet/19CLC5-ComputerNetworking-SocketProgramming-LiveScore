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
    cout << "EXIT APP";
    t->join();
    client->closeConnection();
    delete client;
    lframe->Close();
    mframe->Destroy();
    df_admin->Destroy();
    df_client->Destroy();
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

wxDEFINE_EVENT(LIST_RECV, wxThreadEvent);

void MyApp::socketHandling() {
    wxWindow *currentWindow = nullptr;
    //While the app is still opening
    while ((currentWindow = GetTopWindow()) != nullptr) {
        //Poll event returns false when there are connection error
        if (!client->pollNetworkEvents())
            continue;
        //If there's data to read from server
        try {
            if (client->canRecv() == 1) {
                char rCode = '0';
                client->result = -100;
                client->recvData(&rCode, sizeof(char));
                switch (rCode) {
                    case Client::Login: {
                        //The server send back login result
                        client->recvData((char*)&(client->result), sizeof(int));
                        if (client->result == 0) {
                            client->recvData((char*)&(client->account.isAdmin), sizeof(bool));
                        }
                        client->setMsg(Client::Login);
                        break;
                    }
                    case Client::Register: {
                        //The server send back login result
                        client->recvData((char*)&(client->result), sizeof(int));
                        client->setMsg(Client::Register);
                        break;
                    }
                    case Client::Matches: {
                        //The server send back list of matches
                        client->recvData((char *)&(client->extractSize), sizeof(size_t));
                        //cout << "Expected " << client->extractSize << endl;
                        client->recvData(nullptr, client->extractSize);
                        //cout << "Receive " << client->connector->buf.size() << endl;
                        cout << "Received match list from server" << endl;
                        wxThreadEvent e(LIST_RECV);
                        currentWindow->GetEventHandler()->QueueEvent(e.Clone());
                        client->setMsg(Client::Matches);
                        break;
                    }
                    default:
                        cerr << "Invalid request code." << endl;
                        client->setMsg('\0');
                }
            }
        } catch (const NetworkException& e) {
            displayNotif(e.what());
            client->closeConnection();
            continue;
        }
        //Handle connection close event
        if (client->canClose()) {
            client->closeConnection();;
        }
        if (client->isInvalid() && !client->account.username.empty()) {
            displayNotif("Server disconnected.");
            //HANDLE FRAME JUMPING BY THROWING AN EVENT HERE FOR EVENT HANDLERS TO RESOLVE
        }
    }
}

