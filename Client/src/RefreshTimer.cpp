#include "GUI.h"

void MainRefreshTimer::Init(MainFrame* obj) {
    mframe = obj;
}

void MainRefreshTimer::Notify() {
    mframe->OnTimedRefresh();
}

void DetailRefreshTimer::Init(Client *ptr_client, const string &matchID) {
    client = ptr_client;
    ID = matchID;
}

void DetailRefreshTimer::Notify() {
    client->requestDetails(ID);
}