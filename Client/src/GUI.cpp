#include "GUI.h"

bool MyApp::OnInit()
{
	client = new Client();
	lframe = new LoginFrame(client, NULL, wxID_ANY, _("Live Score"), wxPoint(550, 250), wxSize(500, 300));
	lframe->Show(true);
	return true;
}
int MyApp::OnExit()
{
	delete client;
	delete lframe;
	delete mframe;
	delete df_admin;
	delete df_client;
	close(true);
}

LoginFrame::LoginFrame(Client *&cl, wxWindow *parent,
                       wxWindowID id,
                       const wxString &title,
                       const wxPoint &pos,
                       const wxSize &size,
                       long style) : wxFrame(parent, id, title, pos, size, style)
{
    client = cl;
    Box = new wxBoxSizer(wxHORIZONTAL);

    Title_LS = new wxStaticText(this, wxID_ANY, _("LIVE SCORE"), wxPoint(0, Y_TITLE), wxSize(size.GetWidth(), 50), wxALIGN_CENTRE_HORIZONTAL);
    // create box
    Box->Add(Title_LS);

    serverLabel = new wxStaticText(this, wxID_ANY, _("Server Address: "), wxPoint(X_ServerAdd, Y_ServerAdd), wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    Box->Add(serverLabel);
    server = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(X_ServerAdd + 90, Y_ServerAdd), wxSize(Length_InputBox, Witdh_InputBox));
    Box->Add(server, 2, 0, 10, NULL);

    usrnameLabel = new wxStaticText(this, wxID_ANY, _("Username: "), wxPoint(X_ServerAdd, Y_ServerAdd + Witdh_InputBox + 20));
    Box->Add(usrnameLabel);
    user = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(X_ServerAdd + 90, Y_ServerAdd + Witdh_InputBox + 20), wxSize(Length_InputBox, Witdh_InputBox));
    Box->Add(user, 2, 0, 10, NULL);

    wxStaticText *passwordLabel = new wxStaticText(this, wxID_ANY, _("Password: "), wxPoint(X_ServerAdd, Y_ServerAdd + 2 * (Witdh_InputBox + 20)));
    Box->Add(passwordLabel);
    pwd = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(X_ServerAdd + 90, Y_ServerAdd + 2 * (Witdh_InputBox + 20)), wxSize(Length_InputBox, Witdh_InputBox), wxTE_PASSWORD);
    Box->Add(pwd, 2, 0, 10, NULL);

    //add button
    wxButton *loginButton = new wxButton(this, ID_Login, wxT("LOG IN"), wxPoint(X_LoginButton, Y_LoginButton), wxSize(Length_LoginButton, Witdh_LoginButton));
    Box->Add(loginButton);
    registerButton = new wxButton(this, ID_Register, wxT("REGISTER"), wxPoint(X_LoginButton + 200, Y_LoginButton), wxSize(Length_LoginButton, Witdh_LoginButton));
    Box->Add(registerButton);

    client->pollNetworkEvents();
    client->closeConnection();
}
LoginFrame::~LoginFrame()
{
    delete Box;
    delete Title_LS;
    delete serverLabel;
    delete usrnameLabel;
    delete passwordLabel;
    delete loginButton;
    delete registerButton;

    delete server;
    delete user;
    delete pwd;
}
void LoginFrame::Login(wxCommandEvent &event)
{
    if (client->connectTo(server->GetValue().ToStdString()))
    {
        if (client->login(user->GetValue().ToStdString(), pwd->GetValue().ToStdString()))
        {
            
            event.Skip();
        }
        else
        {
            ErrorMsg("Failed to Login!!");
            // exception window : Login Failed
        }
    }
    else
    {
        ErrorMsg("Failed to connect to server!!");
    }
}
void LoginFrame::Register(wxCommandEvent &event)
{
    if (client->connectTo(server->GetValue().ToStdString()))
    {
        if (client->registerAcc(user->GetValue().ToStdString(), pwd->GetValue().ToStdString()))
        {
            event.Skip();
        }
        else
        {
            ErrorMsg("Failed to Register!!");
        }
    }
    else
    {
        ErrorMsg("Failed to connect to server!!");
    }
}
void LoginFrame::ErrorMsg(wxString msg)
{
    wxMessageBox(msg, wxT("Error Message"),
                 wxOK | wxICON_INFORMATION, this);
}
void LoginFrame::OnExit(wxCommandEvent &event){
     int answer = wxMessageBox("Quit program?", "Confirm",
                              wxYES_NO, NULL);
    if (answer == wxYES)
    {
        close(true);
    }
}
wxBEGIN_EVENT_TABLE(LoginFrame, wxFrame)
    EVT_BUTTON(ID_Login, LoginFrame::Login)
    EVT_BUTTON(ID_Register, LoginFrame::Register)
    EVT_MENU(wxID_EXIT,LoginFrame::OnExit)
wxEND_EVENT_TABLE();

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(parent, id, title, pos, size)
{
}
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)

