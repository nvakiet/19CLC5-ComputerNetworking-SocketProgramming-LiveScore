// #include "client.h"

// int main() {
// 	//Init Winsock
// 	WSADATA wsaData;
// 	auto iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
// 	if (iResult != 0) {
// 		cerr << "Can't initialize Winsock: " << iResult << endl;
// 		return 1;
// 	}

// 	//Create a socket to connect to server
// 	SOCKET conSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
// 	if (conSocket == INVALID_SOCKET) {
// 		cerr << "Can't create socket: " << WSAGetLastError() << endl;
// 		WSACleanup();
// 		return 1;
// 	}

// 	//Set the target server to connect to
// 	string ipaddr;
// 	cout << "Enter server IP: ";
// 	cin >> ipaddr;
// 	SOCKADDR_IN svAddr;
// 	svAddr.sin_family = AF_INET;
// 	svAddr.sin_port = htons(DEFAULT_PORT);
// 	svAddr.sin_addr.S_un.S_addr = inet_addr(ipaddr.c_str());

// 	//Connect to the server
	

// 	return 0;
// }

//*******************************************************************************************

//TEST WINSOCK2

// #include <iostream>
// #include <WinSock2.h>
// #include <WS2tcpip.h>

// #define DEFAULT_BUFLEN 512
// #define DEFAULT_PORT 191420

// using namespace std;

// int main() {
// 	cout << "Hello!" << endl;
// 	return 0;
// }

// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".

//******************************************************************************************

//TEST WXWIDGETS

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
	MyFrame();

private:
	void OnHello(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);
};
enum
{
	ID_Hello = 1
};
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}
MyFrame::MyFrame()
	: wxFrame(NULL, wxID_ANY, "Hello World")
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
					 "Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
void MyFrame::OnExit(wxCommandEvent &event)
{
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox("This is a wxWidgets Hello World example",
				 "About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent &event)
{
	wxLogMessage("Hello world from wxWidgets!");
}