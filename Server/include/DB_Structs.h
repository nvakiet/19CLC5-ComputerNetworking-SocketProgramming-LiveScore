//THIS HEADER FILE DEFINE ALL CLASSES TO REPRESENT DATA EXTRACTED FROM THE DATABASE, USED BY BOTH THE SERVER AND CLIENT
#ifndef DB_STRUCTS_H
#define DB_STRUCTS_H

#include <iostream>
#include <string>
#include <vector>
#include<time.h>

using namespace std;

struct User {
    string username;
    bool isAdmin;
};

struct MatchInfo{
    private:
        string id;
        string timeMatch;
        string teamA;
        string teamB;
        unsigned int scoreA;
        unsigned int scoreB;
    public: 
        MatchInfo( vector<char> response);
        void toByteStream(vector<char>&result);
};
struct ListMatch{
    private:
        vector<MatchInfo> lstMatch;
    public:
};
#endif