#ifndef GUI_H_
#define GUI_H_
#include <wx/wxprec.h>
#include<iostream>
#include"client.h"
#include<wx/string.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#define X_TITLE 100
#define Y_TITLE 10
#define X_ServerAdd 85
#define Y_ServerAdd 80
#define Witdh_InputBox 20
#define Length_InputBox 200
#define X_LoginButton 100
#define Y_LoginButton 205
#define Witdh_LoginButton 30
#define Length_LoginButton 100
class MyApp:public wxApp{
private:
    // Client client;
public:
bool OnInit();
};
DECLARE_APP(MyApp);
class LoginFrame:public wxFrame{
    public:
    LoginFrame(wxWindow *parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize
            );
    private:
    void Login(wxCommandEvent&event);
    void Register(wxCommandEvent&event);
    wxString *serverAdd;
    wxString *username;
    wxString *password;
    DECLARE_EVENT_TABLE();
};
enum{
    ID_username,
    ID_password,
    ID_server,
    ID_Register,
    ID_Login,
};

wxBEGIN_EVENT_TABLE(LoginFrame,wxFrame)
EVT_BUTTON(ID_Login,LoginFrame::Login)
EVT_BUTTON(ID_Register,LoginFrame::Register)
wxEND_EVENT_TABLE()
class MainFrame: public wxFrame{
    public:
    MainFrame(
            wxWindow *parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize);
    private:
    DECLARE_EVENT_TABLE();
};
wxBEGIN_EVENT_TABLE(MainFrame,wxFrame)

wxEND_EVENT_TABLE()




#endif