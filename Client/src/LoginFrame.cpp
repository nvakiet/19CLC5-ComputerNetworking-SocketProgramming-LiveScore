#include "GUI.h"
LoginFrame::LoginFrame(Client *&a, wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
    client = a;
    this->SetSizeHints(wxSize(-1, -1), wxDefaultSize);
    this->SetExtraStyle(wxWS_EX_PROCESS_IDLE);
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));

    wxBoxSizer *mainBox;
    mainBox = new wxBoxSizer(wxVERTICAL);

    TITLE1 = new wxStaticText(this, wxID_ANY, wxT("LIVE SCORE "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    TITLE1->Wrap(-1);
    TITLE1->SetFont(wxFont(26, 74, 90, 92, false, wxT("Arial")));
    TITLE1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    TITLE1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

    mainBox->Add(TITLE1, 0, wxALL | wxEXPAND, 5);

    wxBoxSizer *serveraddressBox;
    serveraddressBox = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *severLabelBox;
    severLabelBox = new wxBoxSizer(wxVERTICAL);

    serverLabel = new wxStaticText(this, wxID_ANY, wxT("Server Address: "), wxDefaultPosition, wxDefaultSize, 0);
    serverLabel->Wrap(-1);
    serverLabel->SetFont(wxFont(10, 74, 90, 92, false, wxT("Arial")));

    severLabelBox->Add(serverLabel, 0, wxALIGN_CENTER | wxALL, 5);

    serveraddressBox->Add(severLabelBox, 1, wxALIGN_CENTER, 5);

    wxBoxSizer *textServerBox;
    textServerBox = new wxBoxSizer(wxHORIZONTAL);

    inputServerText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
    textServerBox->Add(inputServerText, 0, wxALIGN_CENTER | wxALL, 5);

    serveraddressBox->Add(textServerBox, 1, wxALIGN_CENTER, 5);

    mainBox->Add(serveraddressBox, 1, wxEXPAND, 5);

    wxBoxSizer *usernameBox;
    usernameBox = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *userLabelBox;
    userLabelBox = new wxBoxSizer(wxVERTICAL);

    userLabel = new wxStaticText(this, wxID_ANY, wxT("Username: "), wxDefaultPosition, wxDefaultSize, 0);
    userLabel->Wrap(-1);
    userLabel->SetFont(wxFont(10, 74, 90, 92, false, wxT("Arial")));

    userLabelBox->Add(userLabel, 0, wxALIGN_CENTER | wxALL, 5);

    usernameBox->Add(userLabelBox, 1, wxALIGN_CENTER, 5);

    wxBoxSizer *textUserBox;
    textUserBox = new wxBoxSizer(wxVERTICAL);

    inputUserText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
    textUserBox->Add(inputUserText, 0, wxALL, 5);

    usernameBox->Add(textUserBox, 1, wxALIGN_CENTER, 5);

    mainBox->Add(usernameBox, 1, wxEXPAND, 5);

    wxBoxSizer *passwordBox;
    passwordBox = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *passLabelBox;
    passLabelBox = new wxBoxSizer(wxVERTICAL);

    passLabel = new wxStaticText(this, wxID_ANY, wxT("Password:"), wxDefaultPosition, wxDefaultSize, 0);
    passLabel->Wrap(-1);
    passLabel->SetFont(wxFont(10, 74, 90, 92, false, wxT("Arial")));

    passLabelBox->Add(passLabel, 0, wxALIGN_CENTER | wxALL, 5);

    passwordBox->Add(passLabelBox, 1, wxALIGN_CENTER, 5);

    wxBoxSizer *textPassBox;
    textPassBox = new wxBoxSizer(wxVERTICAL);

    inputPassText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1), wxTE_PASSWORD);
    textPassBox->Add(inputPassText, 0, wxALL, 5);

    passwordBox->Add(textPassBox, 1, wxALIGN_CENTER, 5);

    mainBox->Add(passwordBox, 1, wxEXPAND, 5);

    wxBoxSizer *button;
    button = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *loginBox;
    loginBox = new wxBoxSizer(wxVERTICAL);

    loginButton = new wxButton(this, wxID_ANY, wxT("LOG IN"), wxDefaultPosition, wxDefaultSize, 0);
    loginButton->SetFont(wxFont(9, 74, 90, 92, false, wxT("Arial")));

    loginBox->Add(loginButton, 0, wxALL | wxEXPAND, 5);

    button->Add(loginBox, 1, wxALIGN_CENTER, 5);

    wxBoxSizer *registerBox;
    registerBox = new wxBoxSizer(wxVERTICAL);

    registerButton = new wxButton(this, wxID_ANY, wxT("REGISTER"), wxDefaultPosition, wxDefaultSize, 0);
    registerButton->SetFont(wxFont(9, 74, 90, 92, false, wxT("Arial")));

    registerBox->Add(registerButton, 0, wxALL | wxEXPAND, 5);

    button->Add(registerBox, 1, wxALIGN_CENTER, 5);

    mainBox->Add(button, 1, wxEXPAND, 5);

    this->SetSizer(mainBox);
    this->Layout();

    this->Centre(wxBOTH);

    // Connect Events
    this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LoginFrame::OnExitFrame));
    loginButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LoginFrame::OnLoginClick), NULL, this);
    registerButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LoginFrame::OnRegisterClick), NULL, this);
}

LoginFrame::~LoginFrame()
{
    // Disconnect Events
    this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LoginFrame::OnExitFrame));
    loginButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LoginFrame::OnLoginClick), NULL, this);
    registerButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LoginFrame::OnRegisterClick), NULL, this);
    //delete client;
    delete TITLE1;
    delete serverLabel;
    delete inputServerText;
    delete userLabel;
    delete inputUserText;
    delete passLabel;
    delete inputPassText;
    delete loginButton;
    delete registerButton;
}

void LoginFrame::OnLoginClick(wxCommandEvent &event)
{
    // this->Close();
    // MainFrame *mframe = new MainFrame(client, NULL);
    // mframe->Show(true);
    if (client->connectTo(inputServerText->GetValue().ToStdString()))
    {
        if (client->login(inputUserText->GetValue().ToStdString(), inputPassText->GetValue().ToStdString()))
        {
            this->Close();
            MainFrame *mframe = new MainFrame(client, NULL);
            mframe->Show(true);
        }
        else
        {
            // exception window : Login Failed
            ErrorMsg("Failed to Login!!");
        }
    }
    else
    {
        ErrorMsg("Failed to connect to server!!");
    }
}
void LoginFrame::OnRegisterClick(wxCommandEvent &event)
{
    if (client->connectTo(inputServerText->GetValue().ToStdString()))
    {
        if (client->registerAcc(inputUserText->GetValue().ToStdString(), inputPassText->GetValue().ToStdString()))
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
