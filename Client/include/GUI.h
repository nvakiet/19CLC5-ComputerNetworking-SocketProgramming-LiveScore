#ifndef GUI_H_
#define GUI_H_
#include <wx/wxprec.h>
#include <wx/grid.h>
#include <iostream>
#include <thread>
#include "client.h"
#include <wx/string.h>
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
	
	public:
		
		LoginFrame(Client*&, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LIVE SCORE APP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,500 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxFRAME_SHAPED|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE );
		
		~LoginFrame();
	
};


class MainFrame : public wxFrame 
{
	private:
		Client *client;
		void InitializeTableMATCH();
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
		virtual void InitiTableMatch();
	
	public:
		
		MainFrame(Client*&, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LIVE SCORE APP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 512,371 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxFRAME_SHAPED|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE );
		
		~MainFrame();
	
};
class DetailFrame_ForAdmin : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* TITLE;
		wxButton* REFRESH_BUTTON;
		wxButton* AddBUTTON;
		wxButton* UPDATEBUTTON;
		wxButton* DELETEBUTON;
		wxStaticText* GroupNameLabel;
		wxStaticText* StartDateLabel;
		wxStaticText* TeamALabel;
		wxStaticText* ScoreLabel;
		wxStaticText* TeamBLabel;
		wxGrid* DETAILS_MATCH_TABLE;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRefreshClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteCLick( wxCommandEvent& event ) { event.Skip(); }
		
	public:
		
		DetailFrame_ForAdmin( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LIVE SCORE APP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 830,580 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE );
		
		~DetailFrame_ForAdmin();
	
};

class DetailFrame_ForClient : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* TITLE;
		wxButton* REFRESH_BUTTON;
		wxStaticText* GroupNameLabel;
		wxStaticText* StartDateLabel;
		wxStaticText* TeamALabel;
		wxStaticText* ScoreLabel;
		wxStaticText* TeamBLabel;
		wxGrid* DETAILS_MATCH_TABLE;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRefreshClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DetailFrame_ForClient( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LIVE SCORE APP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxALWAYS_SHOW_SB );
		
		~DetailFrame_ForClient();
	
};

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
	void displayNotif(const wxString &notif);
};
DECLARE_APP(MyApp);

#endif

