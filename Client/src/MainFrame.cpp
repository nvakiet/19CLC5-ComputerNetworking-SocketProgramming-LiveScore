#include "GUI.h"

wxDEFINE_EVENT(TIMED_REFRESH, wxTimerEvent);

MainFrame::MainFrame(Client *&a, wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	client = a;
	//FOR DEBUG ONLY:
	// init ListMatch
	//vector<char> temp;
	data = new ListMatch();

	this->SetSizeHints(wxSize(-1, -1), wxDefaultSize);
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

	wxBoxSizer *controlBox;
	controlBox = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer *refreshBox;
	refreshBox = new wxBoxSizer(wxVERTICAL);

	REFRESH_BUTTON = new wxButton(this, wxID_ANY, wxT("REFRESH(&F5)"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	refreshBox->Add(REFRESH_BUTTON, 0, wxALIGN_CENTER | wxALL, 5);

	controlBox->Add(refreshBox, 1, wxALIGN_CENTER, 5);

	wxBoxSizer *SearchByIDBox;
	SearchByIDBox = new wxBoxSizer(wxVERTICAL);

	SEARCH_TEXT = new wxStaticText(this, wxID_ANY, wxT("SEARCH BY ID"), wxDefaultPosition, wxDefaultSize, 0);
	SEARCH_TEXT->Wrap(-1);
	SEARCH_TEXT->SetFont(wxFont(9, 74, 90, 92, false, wxT("Arial")));

	SearchByIDBox->Add(SEARCH_TEXT, 0, wxALIGN_CENTER | wxALL, 5);

	controlBox->Add(SearchByIDBox, 1, wxALIGN_CENTER | wxALL, 5);

	wxBoxSizer *InputIDTextBox;
	InputIDTextBox = new wxBoxSizer(wxHORIZONTAL);

	InputIDText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, -1), 0);
	InputIDTextBox->Add(InputIDText, 0, wxALL | wxEXPAND, 5);

	controlBox->Add(InputIDTextBox, 1, wxALIGN_CENTER | wxALL, 5);

	wxBoxSizer *SearchButtonBox;
	SearchButtonBox = new wxBoxSizer(wxVERTICAL);

	SEARCH_BUTTON = new wxButton(this, wxID_ANY, wxT("SEARCH"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	SearchButtonBox->Add(SEARCH_BUTTON, 0, wxALIGN_CENTER | wxALL, 5);

	controlBox->Add(SearchButtonBox, 1, wxALIGN_CENTER | wxALL, 5);

	BodyBox->Add(controlBox, 1, wxALIGN_CENTER, 5);

	LIST_MATCH = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), 0);

	// Grid
	LIST_MATCH->CreateGrid(20, 5);
	LIST_MATCH->EnableEditing(false);
	LIST_MATCH->EnableGridLines(true);
	LIST_MATCH->SetGridLineColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNHIGHLIGHT));
	LIST_MATCH->EnableDragGridSize(false);
	LIST_MATCH->SetMargins(0, 0);

	// Columns
	LIST_MATCH->SetColSize(0, 55);
	LIST_MATCH->SetColSize(1, 81);
	LIST_MATCH->SetColSize(2, 130);
	LIST_MATCH->SetColSize(3, 108);
	LIST_MATCH->SetColSize(4, 136);
	LIST_MATCH->EnableDragColMove(false);
	LIST_MATCH->EnableDragColSize(false);
	LIST_MATCH->SetColLabelSize(0);
	LIST_MATCH->SetColLabelValue(0, wxT("ID"));
	LIST_MATCH->SetColLabelValue(1, wxT("TIME"));
	LIST_MATCH->SetColLabelValue(2, wxT("TEAM A"));
	LIST_MATCH->SetColLabelValue(3, wxT("SCORE"));
	LIST_MATCH->SetColLabelValue(4, wxT("TEAM B"));
	LIST_MATCH->SetColLabelValue(5, wxT("TIME"));
	LIST_MATCH->SetColLabelValue(6, wxEmptyString);
	LIST_MATCH->SetColLabelValue(7, wxEmptyString);
	LIST_MATCH->SetColLabelValue(8, wxEmptyString);
	LIST_MATCH->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

	// Rows
	LIST_MATCH->EnableDragRowSize(false);
	LIST_MATCH->SetRowLabelSize(35);
	LIST_MATCH->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

	// Label Appearance
	LIST_MATCH->SetLabelBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	// Cell Defaults
	LIST_MATCH->SetDefaultCellBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
	LIST_MATCH->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
	BodyBox->Add(LIST_MATCH, 0, wxALIGN_CENTER | wxALL, 5);

	mainBox->Add(BodyBox, 1, wxEXPAND, 5);

	this->SetSizer(mainBox);
	this->Layout();
	mainBox->Fit(this);

	//DisplayData
	//this->DisplayData();

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrame::OnExitFrame));
	REFRESH_BUTTON->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnRefreshClick), NULL, this);
	SEARCH_BUTTON->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnSearchByIDClick), NULL, this);
	LIST_MATCH->Connect(wxEVT_GRID_LABEL_LEFT_DCLICK, wxGridEventHandler(MainFrame::OnSearchDetailsDClick), NULL, this);
	//Bind THREAD EVENT
	Bind<>(LIST_RECV, MainFrame::OnReceiveList, this);
	Bind<>(SOCK_CLOSE, MainFrame::OnSocketClosed, this);
	client->requestMatches();
	//Start the refresh timer
	timer = new MainRefreshTimer;
	timer->Init(this);
	timer->Start(30000);
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrame::OnExitFrame));
	REFRESH_BUTTON->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnRefreshClick), NULL, this);
	SEARCH_BUTTON->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnSearchByIDClick), NULL, this);
	delete TITLE;
	delete REFRESH_BUTTON;
	delete SEARCH_TEXT;
	delete InputIDText;
	delete SEARCH_BUTTON;
	delete LIST_MATCH;
	delete timer;
}
void MainFrame::OnExitFrame(wxCloseEvent &event)
{
	if (event.CanVeto())
	{
		if (client->isInvalid())
			event.Skip();
		else if (wxMessageBox(wxT("Logout and quit program ?"), wxT("Confirm Quit"), wxICON_QUESTION | wxYES_NO) == wxYES)
			event.Skip(); //Destroy() also works here.
		else
			event.Veto();
	}
}

void MainFrame::OnRefreshClick(wxCommandEvent &event)
{
	if (client->getMsg() == '\0')
	{
		timer->Start(30000);
		client->requestMatches();
	}
	// Client repeats sending the request to the server
}
void MainFrame::OnSearchByIDClick(wxCommandEvent &event)
{
	bool isValidID = false;
	// check data is null
	if (data == nullptr)
	{
		return;
	}
	// Check if the ID is valid
	for (int index = 0; index < data->LstMatch.size(); index++)
	{
		if (InputIDText->GetValue().ToStdString() == data->LstMatch[index].id)
		{
			// Check if the client is admin
			if (client->isAdminAccount())
			{
				// Show the corresponding detail frame
				DetailFrame_ForAdmin *dframe = new DetailFrame_ForAdmin(client, data->LstMatch[index], this);
				dframe->Show();
			}
			else
			{
				// Show the corresponding detail frame
				DetailFrame_ForClient *dframe = new DetailFrame_ForClient(client, data->LstMatch[index], this);
				dframe->Show();
			}
			isValidID = true;
		}
	}

	if (!isValidID)
	{
		wxMessageBox("Invalid ID, please try again", wxT("Message"),
					 wxOK | wxICON_INFORMATION, this);
		event.Skip();
	}
}
void MainFrame::OnSearchDetailsDClick(wxGridEvent &event)
{
	// check row clicked is valid
	if (event.GetRow() < data->LstMatch.size())
	{
		// Check if the client is admin
		if (client->isAdminAccount())
		{
			DetailFrame_ForAdmin *dframe = new DetailFrame_ForAdmin(client, data->LstMatch[event.GetRow()], this);
			dframe->Show();
		}
		else
		{
			DetailFrame_ForClient *dframe = new DetailFrame_ForClient(client, data->LstMatch[event.GetRow()], this);
			dframe->Show();
		}
	}
	else {
		event.Skip();
	}
}

void MainFrame::OnReceiveList(wxThreadEvent &event)
{
	cout << "Event triggered" << endl;
	client->extractMatches(data);
	// for (auto match : data->LstMatch) {
	// 	cout << match.id << ' ' << match.timeMatch << ' ' << match.teamA << ' ' << match.scoreA << " - " << match.scoreB << ' ' << match.teamB << endl;
	// }
	this->DisplayData();
	client->setMsg('\0');
}

void MainFrame::DisplayData(/*vector<MatchInfo> data->LstMatch*/)
{
	if (data->LstMatch.size() > LIST_MATCH->GetNumberRows())
	{
		LIST_MATCH->AppendRows(data->LstMatch.size() - LIST_MATCH->GetNumberRows());
	}
	LIST_MATCH->ClearGrid();
	for (int index = 0; index < data->LstMatch.size(); index++)
	{
		LIST_MATCH->SetCellValue(index, 0, data->LstMatch[index].id);
		LIST_MATCH->SetCellValue(index, 1, data->LstMatch[index].timeMatch);
		LIST_MATCH->SetCellValue(index, 2, data->LstMatch[index].teamA);
		LIST_MATCH->SetCellValue(index, 3, to_string(data->LstMatch[index].scoreA) + " - " + to_string(data->LstMatch[index].scoreB));
		LIST_MATCH->SetCellValue(index, 4, data->LstMatch[index].teamB);
	}
}

void MainFrame::OnSocketClosed(wxThreadEvent &event)
{
	displayNotif("Connection to the server has been closed. Please try again.");
	client->account.username.clear();
	client->account.isAdmin = false;
	LoginFrame *lframe = new LoginFrame(client, NULL, wxID_ANY, _("Live Score"), wxPoint(550, 250), wxSize(500, 300));
	this->Close();
	lframe->Show();
}

void MainFrame::OnTimedRefresh()
{
	if (client->getMsg() == '\0')
	{
		client->requestMatches();
	}
}