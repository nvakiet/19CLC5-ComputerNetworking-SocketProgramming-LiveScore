

#include "GUI.h"

DetailFrame_ForAdmin::DetailFrame_ForAdmin(Client* ptr_client, MatchInfo match, wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style), mInfo(match), client(ptr_client)
{
	//FOR DEBUG ONLY:
	//initialize data;
	//data = MatchDetails();
	//data->match = &match;
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));

	wxBoxSizer *mainBox;
	mainBox = new wxBoxSizer(wxVERTICAL);

	TITLE = new wxStaticText(this, wxID_ANY, wxT("LIVE SCORE "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	TITLE->Wrap(-1);
	TITLE->SetFont(wxFont(26, 74, 90, 92, false, wxT("Arial")));
	TITLE->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
	TITLE->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	mainBox->Add(TITLE, 0, wxEXPAND, 5);

	wxBoxSizer *BodyBox;
	BodyBox = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *ButtonBox;
	ButtonBox = new wxBoxSizer(wxHORIZONTAL);

	ButtonBox->SetMinSize(wxSize(10, -1));
//	wxBoxSizer *RefreshBox;
//	RefreshBox = new wxBoxSizer(wxVERTICAL);
//
//	REFRESH_BUTTON = new wxButton(this, wxID_ANY, wxT("REFRESH(&F5)"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
//	RefreshBox->Add(REFRESH_BUTTON, 0, wxALIGN_CENTER | wxALL, 5);
//
//	ButtonBox->Add(RefreshBox, 1, wxEXPAND, 5);

	wxBoxSizer *AddNewBox;
	AddNewBox = new wxBoxSizer(wxVERTICAL);

	AddBUTTON = new wxButton(this, wxID_ANY, wxT("ADD/NEW "), wxDefaultPosition, wxDefaultSize, 0);
	AddNewBox->Add(AddBUTTON, 0, wxALIGN_CENTER | wxALL, 5);

	ButtonBox->Add(AddNewBox, 1, wxEXPAND, 5);

	wxBoxSizer *UpdateBox;
	UpdateBox = new wxBoxSizer(wxVERTICAL);

	UPDATEBUTTON = new wxButton(this, wxID_ANY, wxT("UPDATE"), wxDefaultPosition, wxDefaultSize, 0);
	UpdateBox->Add(UPDATEBUTTON, 0, wxALIGN_CENTER | wxALL, 5);

	ButtonBox->Add(UpdateBox, 1, wxEXPAND, 5);

	wxBoxSizer *DeleteBox;
	DeleteBox = new wxBoxSizer(wxVERTICAL);

	DELETEBUTON = new wxButton(this, wxID_ANY, wxT("DELETE"), wxDefaultPosition, wxDefaultSize, 0);
	DeleteBox->Add(DELETEBUTON, 0, wxALIGN_CENTER | wxALL, 5);

	ButtonBox->Add(DeleteBox, 1, wxEXPAND, 5);

	BodyBox->Add(ButtonBox, 1, wxEXPAND, 5);

	// wxBoxSizer *Group_DateBox;
	// Group_DateBox = new wxBoxSizer(wxHORIZONTAL);

	// wxBoxSizer *GroupNameBox;
	// GroupNameBox = new wxBoxSizer(wxVERTICAL);

	// GroupNameLabel = new wxStaticText(this, wxID_ANY, wxT("GROUP NAME"), wxDefaultPosition, wxDefaultSize, 0);
	// GroupNameLabel->Wrap(-1);
	// GroupNameLabel->SetFont(wxFont(9, 74, 90, 92, false, wxT("Arial")));

	// GroupNameBox->Add(GroupNameLabel, 0, wxALL, 5);

	// Group_DateBox->Add(GroupNameBox, 1, wxEXPAND, 5);

	// wxBoxSizer *StartDateBox;
	// StartDateBox = new wxBoxSizer(wxVERTICAL);
	// wxString wxDate(match.timeMatch.c_str(), wxConvUTF8);
	// StartDateLabel = new wxStaticText(this, wxID_ANY, wxDate, wxDefaultPosition, wxDefaultSize, 0);
	// StartDateLabel->Wrap(-1);
	// StartDateLabel->SetFont(wxFont(9, 74, 90, 92, false, wxT("Arial")));

	// StartDateBox->Add(StartDateLabel, 0, wxALIGN_CENTER | wxALL, 5);

	// Group_DateBox->Add(StartDateBox, 1, 0, 5);

	// BodyBox->Add(Group_DateBox, 1, wxEXPAND, 5);

	wxBoxSizer *NameMatchBox;
	NameMatchBox = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer *TeamABox;
	TeamABox = new wxBoxSizer(wxVERTICAL);
	wxString wxTeamA(match.teamA.c_str(), wxConvUTF8);
	TeamALabel = new wxStaticText(this, wxID_ANY, wxTeamA, wxDefaultPosition, wxDefaultSize, 0);
	TeamALabel->Wrap(-1);
	TeamALabel->SetFont(wxFont(16, 74, 90, 92, false, wxT("Arial")));

	TeamABox->Add(TeamALabel, 0, wxALIGN_CENTER|wxALL, 5);

	NameMatchBox->Add(TeamABox, 1, wxEXPAND, 5);

	wxBoxSizer *ScoreBox;
	ScoreBox = new wxBoxSizer(wxVERTICAL);
	string score = to_string(match.scoreA) + " - " + to_string(match.scoreB);
	wxString wxScore(score.c_str(), wxConvUTF8);
	ScoreLabel = new wxStaticText(this, wxID_ANY, wxScore, wxDefaultPosition, wxDefaultSize, 0);
	ScoreLabel->Wrap(-1);
	ScoreLabel->SetFont(wxFont(16, 74, 90, 92, false, wxT("Arial")));

	ScoreBox->Add(ScoreLabel, 0, wxALIGN_CENTER|wxALL, 5);

	NameMatchBox->Add(ScoreBox, 1, wxEXPAND, 5);

	wxBoxSizer *TeamBBox;
	TeamBBox = new wxBoxSizer(wxVERTICAL);
	wxString wxTeamB(match.teamB.c_str(), wxConvUTF8);
	TeamBLabel = new wxStaticText(this, wxID_ANY, wxTeamB, wxDefaultPosition, wxDefaultSize, 0);
	TeamBLabel->Wrap(-1);
	TeamBLabel->SetFont(wxFont(16, 74, 90, 92, false, wxT("Arial")));

	TeamBBox->Add(TeamBLabel, 0, wxALIGN_CENTER|wxALL, 5);

	NameMatchBox->Add(TeamBBox, 1, wxEXPAND, 5);

	BodyBox->Add(NameMatchBox, 1, wxEXPAND, 5);

	DETAILS_MATCH_TABLE = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), 0);

	// Grid
	DETAILS_MATCH_TABLE->CreateGrid(15, 4);
	DETAILS_MATCH_TABLE->EnableEditing(false);
	DETAILS_MATCH_TABLE->EnableGridLines(true);
	DETAILS_MATCH_TABLE->SetGridLineColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNHIGHLIGHT));
	DETAILS_MATCH_TABLE->EnableDragGridSize(true);
	DETAILS_MATCH_TABLE->SetMargins(0, 0);

	// Columns
	DETAILS_MATCH_TABLE->SetColSize(0, 90);
	DETAILS_MATCH_TABLE->SetColSize(1, 193);
	DETAILS_MATCH_TABLE->SetColSize(2, 149);
	DETAILS_MATCH_TABLE->SetColSize(3, 215);
	DETAILS_MATCH_TABLE->EnableDragColMove(false);
	DETAILS_MATCH_TABLE->EnableDragColSize(false);
	DETAILS_MATCH_TABLE->SetColLabelSize(0);
	DETAILS_MATCH_TABLE->SetColLabelValue(0, wxT("TIME"));
	DETAILS_MATCH_TABLE->SetColLabelValue(1, wxT("PLAYER_A"));
	DETAILS_MATCH_TABLE->SetColLabelValue(2, wxT("EVENT"));
	DETAILS_MATCH_TABLE->SetColLabelValue(3, wxT("PLAYER_B"));
	DETAILS_MATCH_TABLE->SetColLabelValue(4, wxEmptyString);
	DETAILS_MATCH_TABLE->SetColLabelValue(5, wxEmptyString);
	DETAILS_MATCH_TABLE->SetColLabelValue(6, wxEmptyString);
	DETAILS_MATCH_TABLE->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

	// Rows
	DETAILS_MATCH_TABLE->EnableDragRowSize(false);
	DETAILS_MATCH_TABLE->SetRowLabelSize(0);
	DETAILS_MATCH_TABLE->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

	// Label Appearance
	DETAILS_MATCH_TABLE->SetLabelBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	// Cell Defaults
	DETAILS_MATCH_TABLE->SetDefaultCellBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
	DETAILS_MATCH_TABLE->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
	BodyBox->Add(DETAILS_MATCH_TABLE, 0, wxALIGN_CENTER | wxALL, 5);

	mainBox->Add(BodyBox, 1, wxEXPAND, 5);

	this->SetSizer(mainBox);
	this->Layout();
	mainBox->Fit(this);

	this->Centre(wxBOTH);

	// Connect Events
//	REFRESH_BUTTON->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailFrame_ForAdmin::OnRefreshClick), NULL, this);
	AddBUTTON->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailFrame_ForAdmin::OnAddClick), NULL, this);
	UPDATEBUTTON->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailFrame_ForAdmin::OnUpdateClick), NULL, this);
	DELETEBUTON->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailFrame_ForAdmin::OnDeleteCLick), NULL, this);
	Bind<>(DETAIL_RECV, OnRecvDetails, this);
	//Send the request for details and start the timer
	client->requestDetails(mInfo.id);
	timer = new DetailRefreshTimer;
	timer->Init(client, mInfo.id);
	timer->Start(30000);
}


void DetailFrame_ForAdmin::DisplayData()
{
	if (data.listEvent.size() > DETAILS_MATCH_TABLE->GetNumberRows())
	{
		DETAILS_MATCH_TABLE->AppendRows(data.listEvent.size() - DETAILS_MATCH_TABLE->GetNumberRows());
	}
	DETAILS_MATCH_TABLE->ClearGrid();
	for (int index = 0; index < data.listEvent.size(); index++)
	{
		DETAILS_MATCH_TABLE->SetCellValue(index, 0, data.listEvent[index].timeline);
		DETAILS_MATCH_TABLE->SetCellValue(index, 1, data.listEvent[index].namePlayerTeamA);
		if (data.listEvent[index].isGoal)
		{
			DETAILS_MATCH_TABLE->SetCellValue(index, 2, to_string(data.listEvent[index].scoreA) + " - " + to_string(data.listEvent[index].scoreB));
		}
		else
		{
			if(data.listEvent[index].card.size()==5){
                if(data.listEvent[index].card[0]=='R'){
                    DETAILS_MATCH_TABLE->SetCellBackgroundColour(index,1,wxColour( 255, 0, 0 ));
                }
                else if(data.listEvent[index].card[0]=='Y') {
                    DETAILS_MATCH_TABLE->SetCellBackgroundColour(index,1,wxColour( 255, 255, 0 ));
                }
                if(data.listEvent[index].card[4]=='R'){
                    DETAILS_MATCH_TABLE->SetCellBackgroundColour(index,3,wxColour( 255, 0, 0 ));
                }
                else if(data.listEvent[index].card[4]=='Y') {
                    DETAILS_MATCH_TABLE->SetCellBackgroundColour(index,3,wxColour( 255, 255, 0 ));
                }
            }
			DETAILS_MATCH_TABLE->SetCellValue(index, 2, data.listEvent[index].card);
		}
		DETAILS_MATCH_TABLE->SetCellValue(index, 3, data.listEvent[index].namePlayerTeamB);
	}
}
DetailFrame_ForAdmin::~DetailFrame_ForAdmin()
{
	// Disconnect Events
	//REFRESH_BUTTON->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailFrame_ForAdmin::OnRefreshClick), NULL, this);
	AddBUTTON->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailFrame_ForAdmin::OnAddClick), NULL, this);
	UPDATEBUTTON->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailFrame_ForAdmin::OnUpdateClick), NULL, this);
	DELETEBUTON->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailFrame_ForAdmin::OnDeleteCLick), NULL, this);
	for (int i = 0; i < client->detailQ.IDs.size(); ++i) {
		if (client->detailQ.IDs[i] == mInfo.id) {
			client->detailQ.IDs.erase(client->detailQ.IDs.begin() + i);
			client->detailQ.buffers.erase(client->detailQ.buffers.begin() + i);
			break;
		}
	}
	//delete data;
	delete timer;
	delete TITLE;
	//delete REFRESH_BUTTON;
	delete AddBUTTON;
	delete UPDATEBUTTON;
	delete DELETEBUTON;
	delete TeamALabel;
	delete ScoreLabel;
	delete TeamBLabel;
	delete DETAILS_MATCH_TABLE;
}

void DetailFrame_ForAdmin::OnRecvDetails(wxThreadEvent &event) {
	if (event.GetString() == mInfo.id) {
		if (event.GetExtraLong() > 0) {
			timer->Stop();
			client->extractDetails(mInfo.id, data);
			//Get new total score
            for (int i = data.listEvent.size() - 1; i >= 0; --i) {
                if (data.listEvent[i].isGoal) {
                    string score = to_string(data.listEvent[i].scoreA) + " - " + to_string(data.listEvent[i].scoreB);
	                wxString wxScore(score.c_str(), wxConvUTF8);
                    ScoreLabel->SetLabelText(wxScore);
                    break;
                }
            }
			DisplayData();
			timer->Start(30000);
		}
		client->setMsg('\0');
	}
}