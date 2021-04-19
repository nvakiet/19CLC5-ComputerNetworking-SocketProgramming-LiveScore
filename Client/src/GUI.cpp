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
    wxDELETE(lframe);
    wxDELETE(mframe);
    wxDELETE(df_admin);
    wxDELETE(df_client);
    delete t;
    close(true);
    return 0;
}

void MyApp::showMainFrame()
{
    mframe = new MainFrame(client, NULL);
    mframe->Show(true);
}

void displayNotif(const wxString &notif) {
    wxMessageBox(notif, wxT("Message"),
                 wxOK | wxICON_INFORMATION);
}

wxDEFINE_EVENT(LIST_RECV, wxThreadEvent);
wxDEFINE_EVENT(SOCK_CLOSE, wxThreadEvent);
wxDEFINE_EVENT(LOGIN_RESULT, wxThreadEvent);
wxDEFINE_EVENT(REGIS_RESULT, wxThreadEvent);
wxDEFINE_EVENT(DETAIL_RECV, wxThreadEvent);

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
                        wxThreadEvent e(LOGIN_RESULT);
                        e.SetInt(client->result);
                        currentWindow->GetEventHandler()->QueueEvent(e.Clone());
                        break;
                    }
                    case Client::Register: {
                        //The server send back login result
                        client->recvData((char*)&(client->result), sizeof(int));
                        client->setMsg(Client::Register);
                        wxThreadEvent e(REGIS_RESULT);
                        e.SetInt(client->result);
                        currentWindow->GetEventHandler()->QueueEvent(e.Clone());
                        break;
                    }
                    case Client::Matches: {
                        //The server send back list of matches
                        client->recvData((char *)&(client->extractSize), sizeof(size_t));
                        client->recvData(nullptr, client->extractSize);
                        cout << "Received match list from server" << endl;
                        wxThreadEvent e(LIST_RECV);
                        currentWindow->GetEventHandler()->QueueEvent(e.Clone());
                        client->setMsg(Client::Matches);
                        break;
                    }
                    case Client::Details: {
                        //The server send back list of event details of a match
                        //Receive match ID
                        string ID;
                        client->recvData((char *)&(client->extractSize), sizeof(size_t));
                        ID.resize(client->extractSize);
                        client->recvData(&ID[0], client->extractSize);
                        //Receive match size as byte stream
                        client->recvData((char *)&(client->extractSize), sizeof(size_t));
                        if (client->extractSize > 0) {
                            //If the match has events recorded
                            buftype temp;
                            temp.resize(client->extractSize);
                            client->recvData(&temp[0], temp.size());
                            //Store the byte stream into a detail queue
                            bool found = false;
                            for (int i = 0; i < client->detailQ.IDs.size(); ++i) {
                                if (client->detailQ.IDs[i] == ID) {
                                    client->detailQ.buffers[i] = temp;
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                client->detailQ.IDs.push_back(ID);
                                client->detailQ.buffers.emplace_back(temp);
                            }
                        }
                        wxThreadEvent e(DETAIL_RECV);
                        e.SetString(ID);
                        e.SetExtraLong(client->extractSize);
                        //If the current window is the main frame
                        auto parent = currentWindow->GetParent();
                        if (parent == nullptr) {
                            //Signal the event to all detail frames
                            auto childrenFrames = currentWindow->GetChildren();
                            for (auto frame : childrenFrames) {
                                frame->GetEventHandler()->QueueEvent(e.Clone());
                            }
                        }
                        else {
                            //If the current window is a detail frame => the main frame is parent window, then do the same as above
                            auto childrenFrames = parent->GetChildren();
                            for (auto frame : childrenFrames) {
                                frame->GetEventHandler()->QueueEvent(e.Clone());
                            }
                        }
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
            //HANDLE FRAME JUMPING BY THROWING AN EVENT HERE FOR EVENT HANDLERS TO RESOLVE
            wxThreadEvent e(SOCK_CLOSE);
            currentWindow->GetEventHandler()->QueueEvent(e.Clone());
        }
    }
}

