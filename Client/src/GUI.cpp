#include"GUI.h"

bool MyApp::OnInit(){
    LoginFrame* lframe = new LoginFrame(NULL,wxID_ANY,_("Live Score"),wxPoint(10,10),wxSize(500,300));
    lframe->Show(true);
    return true;
}
LoginFrame::LoginFrame(wxWindow *parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos,
            const wxSize& size):wxFrame(parent,id,title,pos,size)
            {
                serverAdd = new wxString();
                username = new wxString();
                password = new wxString();
                
                wxBoxSizer *Box = new wxBoxSizer(wxHORIZONTAL);
                
                

                wxStaticText* Title_LS = new wxStaticText(this,wxID_ANY,_("LIVE SCORE"),wxPoint(X_TITLE,Y_TITLE),wxSize(200,50));
                
                Box->Add(Title_LS);
                // create box
                wxStaticText *serverLabel = new wxStaticText(this,wxID_ANY,_("Server Address: "),wxPoint(X_ServerAdd,Y_ServerAdd));
                Box->Add(serverLabel);
                wxTextCtrl *server = new wxTextCtrl(this,wxID_ANY,*serverAdd,wxPoint(X_ServerAdd +90,Y_ServerAdd),wxSize(Length_InputBox,Witdh_InputBox));
                Box->Add(server,2,0,10,NULL);
                *serverAdd = server->GetLineText(0);
                
                wxStaticText *usrnameLabel = new wxStaticText(this,wxID_ANY,_("Username: "),wxPoint(X_ServerAdd,Y_ServerAdd + Witdh_InputBox +20));
                Box->Add(usrnameLabel);
                wxTextCtrl *user = new wxTextCtrl(this,wxID_ANY,*username,wxPoint(X_ServerAdd +90,Y_ServerAdd + Witdh_InputBox +20),wxSize(Length_InputBox,Witdh_InputBox));
                Box->Add(user,2,0,10,NULL);

                wxStaticText *passwordLabel = new wxStaticText(this,wxID_ANY,_("Password: "),wxPoint(X_ServerAdd,Y_ServerAdd + 2*(Witdh_InputBox +20)));
                Box->Add(passwordLabel);
                wxTextCtrl *pwd = new wxTextCtrl(this,wxID_ANY,*password,wxPoint(X_ServerAdd +90,Y_ServerAdd + 2*(Witdh_InputBox +20)),wxSize(Length_InputBox,Witdh_InputBox));
                Box->Add(pwd,2,0,10,NULL);
                
                //add button
                wxButton *loginButton = new wxButton(this,ID_Login,wxT("LOG IN"),wxPoint(X_LoginButton,Y_LoginButton),wxSize(Length_LoginButton,Witdh_LoginButton));
                Box->Add(loginButton);
                wxButton *registerButton = new wxButton(this,ID_Register,wxT("REGISTER"),wxPoint(X_LoginButton + 150 ,Y_LoginButton),wxSize(Length_LoginButton,Witdh_LoginButton));
                Box->Add(registerButton);
            }
void LoginFrame::Login(wxCommandEvent& event){

    // if(client->connectTo((*serverAdd).c_str()))
    // {
    //     if(client->login())
    //     {
    //         event.Skip();
    //     }
    //     else 
    //     {
    //         // exception window : Register Failed

    //     }
    // }
    // else 
    // {
    //     // exception: Connecting to Server: Failed
    // }
}
void LoginFrame::Register(wxCommandEvent& event){
    // if(client->connectTo(*serverAdd))
    // {
    //     if(client->registerAcc())
    //     {
    //         event.Skip();
    //     }
    //     else 
    //     {
    //         // exception window : Register Failed

    //     }
    // }
    // else{
    //     // exception: Connecting to Server: Failed
    // }
}




MainFrame::MainFrame(wxWindow *parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos,
            const wxSize& size ): wxFrame(parent,id,title,pos,size)
            {

            }

wxIMPLEMENT_APP(MyApp);