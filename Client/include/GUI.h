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
//CẦN HÀM ONEXIT ĐỂ KHI THOÁT CHƯƠNG TRÌNH THÌ HIỆN THÔNG BÁO CÓ MUỐN THOÁT VÀ TẮT CLASS CLIENT
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
    wxTextCtrl *server; //OBJECT NÀO TỒN TẠI SUỐT CẢ FRAME THÌ PHẢI LÀ MEMBER CỦA CLASS
    //THIẾU DESTRUCTOR ĐỂ DELETE CÁC OBJECT ĐC GỌI NEW
    DECLARE_EVENT_TABLE();
};
enum{
    ID_username,
    ID_password,
    ID_server,
    ID_Register,
    ID_Login,
};


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



#endif