///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

DetailFrame_ForAdmin::DetailFrame_ForAdmin( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOBK ) );
	
	wxBoxSizer* mainBox;
	mainBox = new wxBoxSizer( wxVERTICAL );
	
	TITLE = new wxStaticText( this, wxID_ANY, wxT("LIVE SCORE "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	TITLE->Wrap( -1 );
	TITLE->SetFont( wxFont( 26, 74, 90, 92, false, wxT("Arial") ) );
	TITLE->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
	TITLE->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	
	mainBox->Add( TITLE, 0, wxEXPAND, 5 );
	
	wxBoxSizer* ContentBox;
	ContentBox = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* controlBox;
	controlBox = new wxBoxSizer( wxVERTICAL );
	
	REFRESH_BUTTON = new wxButton( this, wxID_ANY, wxT("REFRESH(&F5)"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	controlBox->Add( REFRESH_BUTTON, 0, wxALIGN_CENTER|wxALL, 5 );
	
	AddBUTTON = new wxButton( this, wxID_ANY, wxT("ADD/NEW "), wxDefaultPosition, wxDefaultSize, 0 );
	controlBox->Add( AddBUTTON, 0, wxALIGN_CENTER|wxALL, 5 );
	
	UPDATEBUTTON = new wxButton( this, wxID_ANY, wxT("UPDATE"), wxDefaultPosition, wxDefaultSize, 0 );
	controlBox->Add( UPDATEBUTTON, 0, wxALIGN_CENTER|wxALL, 5 );
	
	DELETEBUTON = new wxButton( this, wxID_ANY, wxT("DELETE"), wxDefaultPosition, wxDefaultSize, 0 );
	controlBox->Add( DELETEBUTON, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	ContentBox->Add( controlBox, 1, wxALIGN_CENTER, 5 );
	
	wxBoxSizer* Match_Details_Box;
	Match_Details_Box = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* matchBox;
	matchBox = new wxBoxSizer( wxHORIZONTAL );
	
	TeamALabel = new wxStaticText( this, wxID_ANY, wxT("TEAM_A"), wxDefaultPosition, wxDefaultSize, 0 );
	TeamALabel->Wrap( -1 );
	matchBox->Add( TeamALabel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	ScoreLabel = new wxStaticText( this, wxID_ANY, wxT("SCORE"), wxDefaultPosition, wxDefaultSize, 0 );
	ScoreLabel->Wrap( -1 );
	matchBox->Add( ScoreLabel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	TeamBLabel = new wxStaticText( this, wxID_ANY, wxT("TEAM_B"), wxDefaultPosition, wxDefaultSize, 0 );
	TeamBLabel->Wrap( -1 );
	matchBox->Add( TeamBLabel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	Match_Details_Box->Add( matchBox, 1, wxALIGN_CENTER, 5 );
	
	DETAILS_MATCH_TABLE = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	
	// Grid
	DETAILS_MATCH_TABLE->CreateGrid( 10, 4 );
	DETAILS_MATCH_TABLE->EnableEditing( false );
	DETAILS_MATCH_TABLE->EnableGridLines( true );
	DETAILS_MATCH_TABLE->SetGridLineColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	DETAILS_MATCH_TABLE->EnableDragGridSize( true );
	DETAILS_MATCH_TABLE->SetMargins( 0, 0 );
	
	// Columns
	DETAILS_MATCH_TABLE->SetColSize( 0, 90 );
	DETAILS_MATCH_TABLE->SetColSize( 1, 193 );
	DETAILS_MATCH_TABLE->SetColSize( 2, 149 );
	DETAILS_MATCH_TABLE->SetColSize( 3, 215 );
	DETAILS_MATCH_TABLE->AutoSizeColumns();
	DETAILS_MATCH_TABLE->EnableDragColMove( false );
	DETAILS_MATCH_TABLE->EnableDragColSize( false );
	DETAILS_MATCH_TABLE->SetColLabelSize( 0 );
	DETAILS_MATCH_TABLE->SetColLabelValue( 0, wxT("TIME") );
	DETAILS_MATCH_TABLE->SetColLabelValue( 1, wxT("PLAYER_A") );
	DETAILS_MATCH_TABLE->SetColLabelValue( 2, wxT("EVENT") );
	DETAILS_MATCH_TABLE->SetColLabelValue( 3, wxT("PLAYER_B") );
	DETAILS_MATCH_TABLE->SetColLabelValue( 4, wxEmptyString );
	DETAILS_MATCH_TABLE->SetColLabelValue( 5, wxEmptyString );
	DETAILS_MATCH_TABLE->SetColLabelValue( 6, wxEmptyString );
	DETAILS_MATCH_TABLE->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	DETAILS_MATCH_TABLE->AutoSizeRows();
	DETAILS_MATCH_TABLE->EnableDragRowSize( false );
	DETAILS_MATCH_TABLE->SetRowLabelSize( 0 );
	DETAILS_MATCH_TABLE->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	DETAILS_MATCH_TABLE->SetLabelBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	// Cell Defaults
	DETAILS_MATCH_TABLE->SetDefaultCellBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVEBORDER ) );
	DETAILS_MATCH_TABLE->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	Match_Details_Box->Add( DETAILS_MATCH_TABLE, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	ContentBox->Add( Match_Details_Box, 1, wxALIGN_CENTER, 5 );
	
	
	mainBox->Add( ContentBox, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainBox );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	REFRESH_BUTTON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DetailFrame_ForAdmin::OnRefreshClick ), NULL, this );
	AddBUTTON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DetailFrame_ForAdmin::OnAddClick ), NULL, this );
	UPDATEBUTTON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DetailFrame_ForAdmin::OnUpdateClick ), NULL, this );
	DELETEBUTON->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DetailFrame_ForAdmin::OnDeleteCLick ), NULL, this );
}

DetailFrame_ForAdmin::~DetailFrame_ForAdmin()
{
	// Disconnect Events
	REFRESH_BUTTON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DetailFrame_ForAdmin::OnRefreshClick ), NULL, this );
	AddBUTTON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DetailFrame_ForAdmin::OnAddClick ), NULL, this );
	UPDATEBUTTON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DetailFrame_ForAdmin::OnUpdateClick ), NULL, this );
	DELETEBUTON->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DetailFrame_ForAdmin::OnDeleteCLick ), NULL, this );
	
}
