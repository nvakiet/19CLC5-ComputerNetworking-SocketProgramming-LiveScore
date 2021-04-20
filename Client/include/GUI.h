#ifndef GUI_H_
#define GUI_H_
#include <wx/wxprec.h>
#include <wx/grid.h>
#include <iostream>
#include <thread>
#include<vector>
#include "client.h"
#include"DB_Structs.h"
#include <wx/string.h>
#include <wx/timer.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif



class LoginFrame : public wxFrame 
{
	private:
		Client *client;
	protected:
		wxStaticText* TITLE1;
		wxStaticText* serverLabel;
		wxTextCtrl* inputServerText;
		wxStaticText* userLabel;
		wxTextCtrl* inputUserText;
		wxStaticText* passLabel;
		wxTextCtrl* inputPassText;
		wxButton* loginButton;
		wxButton* registerButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnExitFrame( wxCloseEvent& event ) {event.Skip();}
    	virtual void ErrorMsg(wxString);
		virtual void OnLoginClick( wxCommandEvent& event );
		virtual void OnRegisterClick( wxCommandEvent& event );
		void OnLoginResult(wxThreadEvent &event);
		void OnRegisterResult(wxThreadEvent &event);

	public:
		
		LoginFrame(Client*&, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LIVE SCORE APP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,500 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxFRAME_SHAPED|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE );
		
		~LoginFrame();
	
};

class MainRefreshTimer;
class DetailRefreshTimer;

class MainFrame : public wxFrame 
{
	private:
		Client *client;
		ListMatch* data;
		MainRefreshTimer* timer;

	protected:
		wxStaticText* TITLE;
		wxButton* REFRESH_BUTTON;
		wxStaticText* SEARCH_TEXT;
		wxTextCtrl* InputIDText;
		wxButton* SEARCH_BUTTON;
		wxGrid* LIST_MATCH;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnExitFrame( wxCloseEvent& event );
		virtual void OnRefreshClick( wxCommandEvent& event );
		virtual void OnSearchByIDClick( wxCommandEvent& event );
		virtual void OnSearchDetailsDClick( wxGridEvent& event );
		virtual void OnReceiveList(wxThreadEvent &event);
		virtual void OnSocketClosed(wxThreadEvent &event);
		
	public:
		MainFrame(Client*&, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LIVE SCORE APP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 512,371 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxFRAME_SHAPED|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE );
		virtual void DisplayData();
		~MainFrame();
		void OnTimedRefresh();
};

class DetailFrame_ForAdmin : public wxFrame 
{
	private:
		MatchDetails data;
		MatchInfo mInfo;
		Client *client;
		DetailRefreshTimer *timer;

	protected:
		wxStaticText* TITLE;
		//wxButton* REFRESH_BUTTON;
		wxButton* AddBUTTON;
		wxButton* UPDATEBUTTON;
		wxButton* DELETEBUTON;
		//wxStaticText* GroupNameLabel;
		//wxStaticText* StartDateLabel;
		wxStaticText* TeamALabel;
		wxStaticText* ScoreLabel;
		wxStaticText* TeamBLabel;
		wxGrid* DETAILS_MATCH_TABLE;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRefreshClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteCLick( wxCommandEvent& event ) { event.Skip(); }
		void OnRecvDetails(wxThreadEvent &event);
		virtual void DisplayData();
	public:
		
		DetailFrame_ForAdmin(Client* ptr_client, MatchInfo,wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LIVE SCORE APP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 830,580 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE );
		
		~DetailFrame_ForAdmin();
	
};

class DetailFrame_ForClient : public wxFrame 
{
	private:
		MatchDetails data;
		MatchInfo mInfo;
		Client *client;
		DetailRefreshTimer* timer;
	protected:
		wxStaticText* TITLE;
		//wxButton* REFRESH_BUTTON;
		//wxStaticText* GroupNameLabel;
		//wxStaticText* StartDateLabel;
		wxStaticText* TeamALabel;
		wxStaticText* ScoreLabel;
		wxStaticText* TeamBLabel;
		wxGrid* DETAILS_MATCH_TABLE;
		virtual void DisplayData();
		// Virtual event handlers, overide them in your derived class
		virtual void OnRefreshClick( wxCommandEvent& event ) { event.Skip(); }
		void OnRecvDetails(wxThreadEvent &event);
	
	public:
		
		DetailFrame_ForClient(Client* ptr_client, MatchInfo, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LIVE SCORE APP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxALWAYS_SHOW_SB );
		
		~DetailFrame_ForClient();
	
};

void displayNotif(const wxString &notif);

wxDECLARE_EVENT(LIST_RECV, wxThreadEvent);
wxDECLARE_EVENT(SOCK_CLOSE, wxThreadEvent);
wxDECLARE_EVENT(LOGIN_RESULT, wxThreadEvent);
wxDECLARE_EVENT(REGIS_RESULT, wxThreadEvent);
wxDECLARE_EVENT(DETAIL_RECV, wxThreadEvent);
wxDECLARE_EVENT(TIMED_REFRESH, wxTimerEvent);
class MyApp : public wxApp
{
private:
    Client *client;
    LoginFrame *lframe;
    MainFrame *mframe;
	DetailFrame_ForAdmin *df_admin;
	DetailFrame_ForClient *df_client;
	thread *t;
	void socketHandling();

public:
    bool OnInit();
	void showMainFrame();
    int OnExit();
	
};
DECLARE_APP(MyApp);


class MainRefreshTimer : public wxTimer {
    protected:
        MainFrame *mframe;
    public:
        void Init(MainFrame* obj);
        void Notify();
};

class DetailRefreshTimer : public wxTimer {
	protected:
		Client *client;
		string ID;
	public:
		void Init(Client *ptr_client, const string &matchID);
		void Notify();
};

#endif

