#include "GUI.h"

void MainRefreshTimer::Init(MainFrame* obj) {
    mframe = obj;
}

void MainRefreshTimer::Notify() {
    mframe->OnTimedRefresh();
}