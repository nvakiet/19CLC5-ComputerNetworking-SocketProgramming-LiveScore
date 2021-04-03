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
                //GỌI NEW OBJECT NÀO THÌ PHẢI NHỚ DELETE NÓ TRONG DESTRUCTOR, MỘT FRAME RẤT LÀ NẶNG, KO CẨN THẬN SẼ BỊ MEMORY LEAK NẾU CHUYỂN FRAME QUÁ NHIỀU
                serverAdd = new wxString();
                username = new wxString();
                password = new wxString();
                
                wxBoxSizer *Box = new wxBoxSizer(wxHORIZONTAL);
                //TRONG CONSTRUCTOR CỦA CÁC OBJECT CÓ PARAMETER CHO THIẾT LẬP GIÁ TRỊ STRING HIỂN THỊ MẶC ĐỊNH VÀ PARAMETER ĐẶT STYLE PHÍA SAU PARAMETER ĐẶT SIZE
                //VD KHI CẦN CĂN LỀ GIỮA 1 OBJECT NÀO, THÌ MÌNH CÓ THỂ ĐẶT TỌA ĐỘ X LÀ 0, ĐỘ RỘNG = ĐỘ RỘNG WINDOW, RỒI ĐẶT STYLE ALIGN CENTER
                wxStaticText *Title_LS = new wxStaticText(this, wxID_ANY, _("LIVE SCORE"), wxPoint(0, Y_TITLE), wxSize(size.GetWidth(), 50), wxALIGN_CENTRE_HORIZONTAL); 

                Box->Add(Title_LS);
                // create box
                wxStaticText *serverLabel = new wxStaticText(this,wxID_ANY,_("Server Address: "),wxPoint(X_ServerAdd,Y_ServerAdd));
                Box->Add(serverLabel);
                //ĐỂ SỬ DỤNG CÁC TEXTCTRL NÀY TRONG HÀM KHÁC THÌ PHẢI ĐẶT NÓ LÀM MEMBER CỦA CLASS
                /*wxTextCtrl * */server = new wxTextCtrl(this,wxID_ANY,"Enter server IP",wxPoint(X_ServerAdd +90,Y_ServerAdd),wxSize(Length_InputBox,Witdh_InputBox));
                Box->Add(server,2,0,10,NULL);
                *serverAdd = server->GetLineText(0);
                
                wxStaticText *usrnameLabel = new wxStaticText(this,wxID_ANY,_("Username: "),wxPoint(X_ServerAdd,Y_ServerAdd + Witdh_InputBox +20));
                Box->Add(usrnameLabel);
                //PARAMETER THỨ 3 LÀ GIÁ TRỊ STRING MẶC ĐỊNH (HOẶC TITLE CỦA OBJECT) CHỨ KO PHẢI LÀ BIẾN STRING NÓ SẼ TRUYỀN VÀO
                wxTextCtrl *user = new wxTextCtrl(this,wxID_ANY, "Enter username",wxPoint(X_ServerAdd +90,Y_ServerAdd + Witdh_InputBox +20),wxSize(Length_InputBox,Witdh_InputBox));
                Box->Add(user,2,0,10,NULL);

                wxStaticText *passwordLabel = new wxStaticText(this,wxID_ANY,_("Password: "),wxPoint(X_ServerAdd,Y_ServerAdd + 2*(Witdh_InputBox +20)));
                Box->Add(passwordLabel);
                //PARAMETER THỨ 6 CHÍNH LÀ PARAMETER ĐẶT STYLE CHO OBJECT
                wxTextCtrl *pwd = new wxTextCtrl(this,wxID_ANY, "Enter password",wxPoint(X_ServerAdd +90,Y_ServerAdd + 2*(Witdh_InputBox +20)),wxSize(Length_InputBox,Witdh_InputBox), wxTE_PASSWORD);
                Box->Add(pwd,2,0,10,NULL);
                
                //add button
                wxButton *loginButton = new wxButton(this,ID_Login,wxT("LOG IN"),wxPoint(X_LoginButton,Y_LoginButton),wxSize(Length_LoginButton,Witdh_LoginButton));
                Box->Add(loginButton);
                wxButton *registerButton = new wxButton(this,ID_Register,wxT("REGISTER"),wxPoint(X_LoginButton + 150 ,Y_LoginButton),wxSize(Length_LoginButton,Witdh_LoginButton));
                Box->Add(registerButton);
            }
void LoginFrame::Login(wxCommandEvent& event){
    //SAU KHI ĐẶT CÁC OBJECT TỒN TẠI SUỐT FRAME LÀM MEMBER CỦA CLASS THÌ CÓ THỂ DÙNG NÓ TRONG HÀM KHÁC
    //GỌI HÀM GETVALUE HOẶC GETLINETEXT ĐỂ LẤY STRING
    *serverAdd = server->GetValue();
    //CLASS WXSTRING CÓ THỂ DÙNG VỚI CLASS IOSTREAM CỦA C++, NHƯNG NẾU CẦN VẪN CÓ THỂ CHUYỂN NÓ THÀNH STD::STRING
    cout << *serverAdd << endl;
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

//ĐÂY LÀ NGUYÊN NHÂN GÂY RA LỖI COMPILE: CÁC LỆNH DECLARE PHẢI ĐỂ BÊN HEADER, CÒN LỆNH BEGIN-END ĐỂ BÊN SOURCE
wxBEGIN_EVENT_TABLE(LoginFrame, wxFrame)
EVT_BUTTON(ID_Login, LoginFrame::Login)
EVT_BUTTON(ID_Register, LoginFrame::Register)
wxEND_EVENT_TABLE()



MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size) : 
    wxFrame(parent,id,title,pos,size) {

}
wxBEGIN_EVENT_TABLE(MainFrame,wxFrame)

wxEND_EVENT_TABLE()


//wxIMPLEMENT_APP(MyApp);