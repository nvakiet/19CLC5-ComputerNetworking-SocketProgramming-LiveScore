//THIS HEADER FILE DEFINE ALL CLASSES TO REPRESENT DATA EXTRACTED FROM THE DATABASE, USED BY BOTH THE SERVER AND CLIENT
#ifndef DB_STRUCTS_H
#define DB_STRUCTS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct User {
    string username;
    bool isAdmin;
};
struct MatchInfo{
    private:
        string id;
        string time;
        string teamA;
        string teamB;
        string Score;
    public: 
        MatchInfo(string response);
        string createArequest();
        string getID();
        string getTime();
        string getNameTeamA();
        string getNameTeamB();
        string getScore();
};
#endif