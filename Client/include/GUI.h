#ifndef GUI_H_
#define GUI_H_
#include <wx/wxprec.h>
#include <wx/msgdlg.h>
#include <iostream>
#include "client.h"
#include <wx/string.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
const int X_TITLE = 100;
const int Y_TITLE = 10;
const int X_ServerAdd = 85;
const int Y_ServerAdd = 60;
const int Witdh_InputBox = 20;
const int Length_InputBox = 200;
const int X_LoginButton = 110;
const int Y_LoginButton = 200;
const int Witdh_LoginButton = 30;
const int Length_LoginButton = 100;

class LoginFrame : public wxFrame
{
public:
    LoginFrame( Client*&, wxWindow *parent,
               wxWindowID id,
               const wxString &title,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE);
    ~LoginFrame();

private:
    //client
    Client *client;
    //methods
    void Login(wxCommandEvent &event);
    void Register(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void ErrorMsg(wxString);
    // data member
    wxBoxSizer *Box;
    wxStaticText *Title_LS;
    wxStaticText *serverLabel;
    wxStaticText *usrnameLabel;
    wxStaticText *passwordLabel;
    wxButton *loginButton;
    wxButton *registerButton;
    wxTextCtrl *server;
    wxTextCtrl *user;
    wxTextCtrl *pwd; //OBJECT NÀO TỒN TẠI SUỐT CẢ FRAME THÌ PHẢI LÀ MEMBER CỦA CLASS
    //THIẾU DESTRUCTOR ĐỂ DELETE CÁC OBJECT ĐC GỌI NEW
    DECLARE_EVENT_TABLE();
};
enum
{
    ID_username,
    ID_password,
    ID_server,
    ID_Register,
    ID_Login,
};

class MainFrame : public wxFrame
{
public:
    MainFrame(
        wxWindow *parent,
        wxWindowID id,
        const wxString &title,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize);

private:
    DECLARE_EVENT_TABLE();
};

class MyApp : public wxApp
{
private:
    Client *client;
    LoginFrame *lframe;
    MainFrame *mframe;

public:
    bool OnInit();
    int OnExit();
    //CẦN HÀM ONEXIT ĐỂ KHI THOÁT CHƯƠNG TRÌNH THÌ HIỆN THÔNG BÁO CÓ MUỐN THOÁT VÀ TẮT CLASS CLIENT
};
DECLARE_APP(MyApp);

#endif