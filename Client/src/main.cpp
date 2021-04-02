#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
// #pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
// #pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(int argc, char **argv) 
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    const char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
            printf("Bytes received: %d\n", iResult);
        else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

//==========================================================================================================================
// #include "client.h"

// void showMsg(SOCKET s) {
//     char buffer[2048];
//     int bRecv = 0, flag = 0, ret = 0;
//     WSABUF databuf;
//     do {
//         //Receive reply
//         databuf.buf = buffer;
//         databuf.len = 2048;
//         ret = WSARecv(s, &databuf, 1, (LPDWORD)&bRecv, (LPDWORD)&flag, nullptr, nullptr);
//         if (ret != SOCKET_ERROR) {
//             cout << buffer << endl;
//         }
//         else {
//             cerr << "Error " << WSAGetLastError() << endl;
//             break;
//         }
//     } while (bRecv > 0);
// }
// int main(int argc, char **argv) 
// {
//     WSADATA wsaData;
//     SOCKET ConnectSocket = INVALID_SOCKET;
//     struct addrinfo *result = NULL,
//                     *ptr = NULL,
//                     hints;
//     char buf[DEFAULT_BUFLEN];
//     int iResult;
//     int buflen = DEFAULT_BUFLEN;
    
//     // Validate the parameters
//     if (argc != 2) {
//         printf("usage: %s server-name\n", argv[0]);
//         return 1;
//     }

//     // Initialize Winsock
//     iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
//     if (iResult != 0) {
//         printf("WSAStartup failed with error: %d\n", iResult);
//         return 1;
//     }

//     ZeroMemory( &hints, sizeof(hints) );
//     hints.ai_family = AF_INET;
//     hints.ai_socktype = SOCK_STREAM;
//     hints.ai_protocol = IPPROTO_TCP;

//     // Resolve the server address and port
//     iResult = getaddrinfo("192.168.0.105", DEFAULT_PORT, &hints, &result);
//     if ( iResult != 0 ) {
//         printf("getaddrinfo failed with error: %d\n", iResult);
//         WSACleanup();
//         return 1;
//     }

//     // Attempt to connect to an address until one succeeds
//     for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

//         // Create a SOCKET for connecting to server
//         ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
//             ptr->ai_protocol);
//         if (ConnectSocket == INVALID_SOCKET) {
//             printf("socket failed with error: %ld\n", WSAGetLastError());
//             WSACleanup();
//             return 1;
//         }

//         // Connect to server.
//         iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//         if (iResult == SOCKET_ERROR) {
//             closesocket(ConnectSocket);
//             ConnectSocket = INVALID_SOCKET;
//             cerr << "Connect failed, error " << WSAGetLastError() << endl;
//             continue;
//         }
//         break;
//     }

//     freeaddrinfo(result);
//     if (ConnectSocket == INVALID_SOCKET) {
//         printf("Unable to create socket!\n");
//         WSACleanup();
//         return 1;
//     }
//     WSABUF databuf;
//     DWORD bytesTransmit = 0;
//     DWORD flag = 0;
//     int ret = 0;
//     thread t(showMsg, ConnectSocket);
//     // Receive until the peer closes the connection
//     do {
//         string msg;
//         getline(cin, msg);
//         databuf.buf = (char *)msg.c_str();
//         databuf.len = msg.size() + 1;
//         // Send a message
//         iResult = WSASend(ConnectSocket, &databuf, 1, &bytesTransmit, 0, nullptr, nullptr);
//         if (iResult == SOCKET_ERROR) {
// 			printf("send failed with error: %d\n", WSAGetLastError());
// 			closesocket(ConnectSocket);
// 			WSACleanup();
// 			return 1;
// 		}
//     } while(true);
//     t.join();
//     // cleanup
//     shutdown(ConnectSocket, SD_BOTH);
//     closesocket(ConnectSocket);
//     WSACleanup();

//     return 0;
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

// #include <wx/wxprec.h>
// #ifndef WX_PRECOMP
// #include <wx/wx.h>
// #endif
// class MyApp : public wxApp
// {
// public:
// 	virtual bool OnInit();
// };
// class MyFrame : public wxFrame
// {
// public:
// 	MyFrame();

// private:
// 	void OnHello(wxCommandEvent &event);
// 	void OnExit(wxCommandEvent &event);
// 	void OnAbout(wxCommandEvent &event);
// };
// enum
// {
// 	ID_Hello = 1
// };
// wxIMPLEMENT_APP(MyApp);
// bool MyApp::OnInit()
// {
// 	MyFrame *frame = new MyFrame();
// 	frame->Show(true);
// 	return true;
// }
// MyFrame::MyFrame()
// 	: wxFrame(NULL, wxID_ANY, "Hello World")
// {
// 	wxMenu *menuFile = new wxMenu;
// 	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
// 					 "Help string shown in status bar for this menu item");
// 	menuFile->AppendSeparator();
// 	menuFile->Append(wxID_EXIT);
// 	wxMenu *menuHelp = new wxMenu;
// 	menuHelp->Append(wxID_ABOUT);
// 	wxMenuBar *menuBar = new wxMenuBar;
// 	menuBar->Append(menuFile, "&File");
// 	menuBar->Append(menuHelp, "&Help");
// 	SetMenuBar(menuBar);
// 	CreateStatusBar();
// 	SetStatusText("Welcome to wxWidgets!");
// 	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
// 	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
// 	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
// }
// void MyFrame::OnExit(wxCommandEvent &event)
// {
// 	Close(true);
// }
// void MyFrame::OnAbout(wxCommandEvent &event)
// {
// 	wxMessageBox("This is a wxWidgets Hello World example",
// 				 "About Hello World", wxOK | wxICON_INFORMATION);
// }
// void MyFrame::OnHello(wxCommandEvent &event)
// {
// 	wxLogMessage("Hello world from wxWidgets!");
// }
