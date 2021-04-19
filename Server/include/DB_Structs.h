//THIS HEADER FILE DEFINE ALL CLASSES TO REPRESENT DATA EXTRACTED FROM THE DATABASE, USED BY BOTH THE SERVER AND CLIENT
#ifndef DB_STRUCTS_H
#define DB_STRUCTS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct User
{
    string username;
    bool isAdmin;
};

void setBuffer(char *newBuf, size_t newLen, vector<char> &buf);
void appendBuffer(char *data, size_t len, vector<char> &buf);
bool extractBuffer(char *extBuf, size_t extLen, vector<char> &buf);

struct MatchInfo
{
public:
    string id;
    string timeMatch;
    string teamA;
    string teamB;
    unsigned int scoreA;
    unsigned int scoreB;
    // FOR DEBUG ONLY:
    //MatchInfo(const char *ID, const char *time, const char *nameA, const char *nameB, unsigned int score_A, unsigned score_B);
    MatchInfo() = default;
    MatchInfo(vector<char> response);
    void updateData(vector<char> response);
    void toByteStream(vector<char> &result);
};
struct ListMatch
{
    vector<MatchInfo> LstMatch;
    //FOR DEBUG ONLY:
    //ListMatch();
    ListMatch() = default;
    ListMatch(vector<char> response);
    void updateData(vector<char> response);
    void toByteStream(vector<char> &result);
};
struct Event
{
    string timeline = "-";
    string namePlayerTeamA = "-";
    string namePlayerTeamB = "-";
    unsigned int scoreA = 0;
    unsigned int scoreB = 0;
    string card = "-";
    bool isGoal = true;
    //FOR DEBUG ONLY:
    //Event();
    //Event(const char*);
    Event() = default;
    Event(vector<char> response);
    void updateData(vector<char> response);
    void toByteStream(vector<char> &result);
};
struct MatchDetails
{
    //string nameGroup;
    //string startDate;
    //MatchInfo *match;
    vector<Event> listEvent;
    //FOR DEBUG ONLY:
    //MatchDetails();
    MatchDetails() = default;
    MatchDetails(vector<char> response);
    MatchDetails(const vector<Event> &scores, const vector<Event> &cards);
    void updateData(vector<char> response);
    void toByteStream(vector<char> &result);
};

typedef vector<char> buftype;

//This struct is for thread communication between sockhandling thread and main thread
//USED FOR EXTRACTING DETAIL INFORMATIONS FOR EACH DETAIL FRAME
struct DetailQueue {
    vector<string> IDs;
    vector<buftype> buffers;
};
#endif