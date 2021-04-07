#include "GUI.h"

bool MyApp::OnInit()
{
	client = new Client();
	lframe = new LoginFrame(client, NULL, wxID_ANY, _("Live Score"), wxPoint(550, 250), wxSize(500, 300));
	lframe->Show(true);
	return true;
}
int MyApp::OnExit()
{
	delete client;
	delete lframe;
	delete mframe;
	delete df_admin;
	delete df_client;
	close(true);
}


