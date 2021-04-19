#include "DB_Structs.h"

void setBuffer(char *newBuf, size_t newLen, vector<char> &buf)
{
    buf.resize(newLen);
    if (newBuf != nullptr)
        buf.assign(newBuf, newBuf + newLen);
}

void appendBuffer(char *data, size_t len, vector<char> &buf)
{
    if (data != nullptr)
        buf.insert(buf.end(), data, data + len);
}
bool extractBuffer(char *extBuf, size_t extLen, vector<char> &buf)
{
    if (extLen > buf.size())
        return false;
    if (extBuf != nullptr)
    {
        std::copy(buf.begin(), buf.begin() + extLen, extBuf);
    }
    buf.erase(buf.begin(), buf.begin() + extLen);
    return true;
}

MatchInfo::MatchInfo(vector<char> response)
{
    size_t expectedSize = 0;
    //Extract ID
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    id.resize(expectedSize);
    extractBuffer((char *)&id[0], expectedSize, response);
    //Extract match time
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    timeMatch.resize(expectedSize);
    extractBuffer((char *)&timeMatch[0], expectedSize, response);
    //Extract name team A
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    teamA.resize(expectedSize);
    extractBuffer((char *)&teamA[0], expectedSize, response);
    //Extract name team B
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    teamB.resize(expectedSize);
    extractBuffer((char *)&teamB[0], expectedSize, response);
    //Extract scores
    extractBuffer((char *)&scoreA, sizeof(unsigned int), response);
    extractBuffer((char *)&scoreB, sizeof(unsigned int), response);
}
void MatchInfo::updateData(vector<char> response)
{
    size_t expectedSize = 0;
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    id.resize(expectedSize);
    extractBuffer((char *)&id[0], expectedSize, response);

    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    timeMatch.resize(expectedSize);
    extractBuffer((char *)&timeMatch[0], expectedSize, response);

    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    teamA.resize(expectedSize);
    extractBuffer((char *)&teamA[0], expectedSize, response);

    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    teamB.resize(expectedSize);
    extractBuffer((char *)&teamB[0], expectedSize, response);

    extractBuffer((char *)&scoreA, sizeof(unsigned int), response);
    extractBuffer((char *)&scoreB, sizeof(unsigned int), response);
}

void MatchInfo::toByteStream(vector<char> &result)
{
    result.clear();
    size_t sizeID = id.size();
    size_t sizeTime = timeMatch.size();
    size_t sizenameA = teamA.size();
    size_t sizenameB = teamB.size();
    size_t totalSize = sizeID + sizeTime + sizenameA + sizenameB + 2 * sizeof(unsigned int);
    result.reserve(totalSize);
    //Put id to buffer
    appendBuffer((char *)&sizeID, sizeof(size_t), result);
    appendBuffer((char *)&id[0], sizeID, result);
    //Put match time to buffer
    appendBuffer((char *)&sizeTime, sizeof(size_t), result);
    appendBuffer((char *)&timeMatch[0], sizeTime, result);
    //Put name of team A to buffer
    appendBuffer((char *)&sizenameA, sizeof(size_t), result);
    appendBuffer((char *)&teamA[0], sizenameA, result);
    //Put name of team B to buffer
    appendBuffer((char *)&sizenameB, sizeof(size_t), result);
    appendBuffer((char *)&teamB[0], sizenameB, result);
    //Put the scores to buffer
    appendBuffer((char *)&scoreA, sizeof(unsigned int), result);
    appendBuffer((char *)&scoreB, sizeof(unsigned int), result);
}
// FOR DEBUG ONLY:
//MatchInfo::MatchInfo(const char *ID, const char *time, const char *nameA, const char *nameB, unsigned int score_A, unsigned score_B) : id(ID), timeMatch(time), teamA(nameA), teamB(nameB), scoreA(score_A), scoreB(score_B) {}
ListMatch::ListMatch(vector<char> response)
{
    size_t numMatch = 0;
    extractBuffer((char *)&numMatch, sizeof(size_t), response);
    LstMatch.reserve(numMatch);
    size_t expectedSize = 0;
    for (int index = 0; index < numMatch; index++)
    {
        extractBuffer((char *)&expectedSize, sizeof(size_t), response);
        vector<char> cache;
        cache.resize(expectedSize);
        extractBuffer((char *)&cache[0], expectedSize, response);
        LstMatch.emplace_back(cache);
    }
}
void ListMatch::updateData(vector<char> response)
{
    if (!LstMatch.empty())
    {
        LstMatch.clear();
    }
    size_t numMatch = 0;
    extractBuffer((char *)&numMatch, sizeof(size_t), response);
    size_t expectedSize = 0;
    for (int index = 0; index < numMatch; index++)
    {
        extractBuffer((char *)&expectedSize, sizeof(size_t), response);
        vector<char> cache;
        cache.resize(expectedSize);
        extractBuffer((char *)&cache[0], expectedSize, response);
        LstMatch.emplace_back(cache);
    }
}
void ListMatch::toByteStream(vector<char> &result)
{
    result.clear();
    result.reserve(2048);
    size_t sizeListMatch = LstMatch.size();
    appendBuffer((char *)&sizeListMatch, sizeof(size_t), result);
    for (int index = 0; index < sizeListMatch; index++)
    {
        vector<char> cache;
        LstMatch[index].toByteStream(cache);
        size_t sizeCache = cache.size();
        appendBuffer((char *)&sizeCache, sizeof(size_t), result);
        appendBuffer((char *)&cache[0], sizeCache, result);
    }
}
//FOR DEBUG ONLY:
// ListMatch::ListMatch()
// {
//     MatchInfo a("VNTL", "15:30", "Viet Nam", "Thai Land", 2, 1);
//     MatchInfo b("AS", "20:33", "Australia", "Singarpore", 4, 4);
//     LstMatch.push_back(a);
//     LstMatch.push_back(b);
// }

Event::Event(vector<char> response)
{
    size_t expectedSize = 0;
    //Get timeline string
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    timeline.resize(expectedSize);
    extractBuffer((char *)&timeline[0], expectedSize, response);
    //Get player name of team A
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    namePlayerTeamA.resize(expectedSize);
    extractBuffer((char *)&namePlayerTeamA[0], expectedSize, response);
    //Get player name of team B
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    namePlayerTeamB.resize(expectedSize);
    extractBuffer((char *)&namePlayerTeamB[0], expectedSize, response);
    //Get card string
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    card.resize(expectedSize);
    extractBuffer((char *)&card[0], expectedSize, response);
    //Get score A and B
    extractBuffer((char *)&scoreA, sizeof(unsigned int), response);
    extractBuffer((char *)&scoreB, sizeof(unsigned int), response);
    //Get check value
    extractBuffer((char *)&isGoal, sizeof(bool), response);
}
void Event::updateData(vector<char> response)
{
    size_t expectedSize = 0;
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    timeline.resize(expectedSize);
    extractBuffer((char *)&timeline[0], expectedSize, response);
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    namePlayerTeamA.resize(expectedSize);
    extractBuffer((char *)&namePlayerTeamA[0], expectedSize, response);
    extractBuffer((char *)&expectedSize, sizeof(size_t), response);
    namePlayerTeamB.resize(expectedSize);
    extractBuffer((char *)&namePlayerTeamB[0], sizeof(size_t), response);
    extractBuffer((char *)&scoreA, sizeof(unsigned int), response);
    extractBuffer((char *)&scoreB, sizeof(unsigned int), response);
    extractBuffer((char *)&expectedSize, sizeof(unsigned int), response);
    card.resize(expectedSize);
    extractBuffer((char *)&card[0], expectedSize, response);
    extractBuffer((char *)&isGoal, sizeof(bool), response);
}

void Event::toByteStream(vector<char> &result)
{
    result.clear();
    size_t sizeTimeLine = timeline.size();
    size_t sizenameA = namePlayerTeamA.size();
    size_t sizenameB = namePlayerTeamB.size();
    size_t sizeCard = card.size(), sizeScore = sizeof(unsigned int), sizeBool = sizeof(bool);
    size_t totalSize = sizeTimeLine + sizenameA + sizenameB + sizeCard + sizeBool + sizeScore * 2;
    result.reserve(totalSize);
    //Put the timeline string to buffer
    appendBuffer((char *)&sizeTimeLine, sizeof(size_t), result);
    appendBuffer((char *)&timeline[0], sizeTimeLine, result);
    //Put player name of team A to buffer
    appendBuffer((char *)&sizenameA, sizeof(size_t), result);
    appendBuffer((char *)&namePlayerTeamA[0], sizenameA, result);
    //Put player name of team B to buffer
    appendBuffer((char *)&sizenameB, sizeof(size_t), result);
    appendBuffer((char *)&namePlayerTeamB[0], sizenameB, result);
    //Put card string to buffer
    appendBuffer((char *)&sizeCard, sizeof(size_t), result);
    appendBuffer((char *)&card[0], sizeCard, result);
    //Put score A and score B to buffer
    appendBuffer((char *)&scoreA, sizeof(unsigned int), result);
    appendBuffer((char *)&scoreB, sizeof(unsigned int), result);
    //Put check goal variable to buffer
    appendBuffer((char *)&isGoal, sizeof(bool), result);
}

MatchDetails::MatchDetails(vector<char> response)
{
    size_t numEvent = 0;
    extractBuffer((char *)&numEvent, sizeof(size_t), response);
    listEvent.reserve(numEvent);
    size_t expectedSize = 0;

    for(int index = 0; index < numEvent ; index++)
    {
        extractBuffer((char *)&expectedSize, sizeof(size_t), response);
        vector<char> cache;
        cache.resize(expectedSize);
        extractBuffer((char *)&cache[0], expectedSize, response);
        listEvent.emplace_back(cache);
    }
}
void MatchDetails::updateData(vector<char> response)
{
    if (!listEvent.empty())
    {
        listEvent.clear();
    }
    size_t expectedSize = 0;

    while (!response.empty())
    {
        extractBuffer((char *)&expectedSize, sizeof(size_t), response);
        vector<char> cache;
        cache.resize(expectedSize);
        extractBuffer((char *)&cache[0], expectedSize, response);
        listEvent.emplace_back(cache);
    }
}
void MatchDetails::toByteStream(vector<char> &result)
{
    result.clear();
    result.reserve(2048);
    size_t sizeListEvent = listEvent.size();
    appendBuffer((char *)&sizeListEvent, sizeof(size_t), result);
    for (int index = 0; index < sizeListEvent; index++)
    {
        vector<char> cache;
        listEvent[index].toByteStream(cache);
        size_t sizeCache = cache.size();
        appendBuffer((char *)&sizeCache, sizeof(size_t), result);
        appendBuffer((char *)&cache[0], sizeCache, result);
    }
}

bool goalcomeFirst(string timeline_Score, string timeline_Card)
{   
    int overtime_score = 0;
    int overtime_card = 0;
    int pos_first_score = timeline_Score.find_first_of(char(39));
    int pos_first_card = timeline_Card.find_first_of(char(39));
    int pos_last_score = timeline_Score.find_last_of(char(39));
    int pos_last_card = timeline_Card.find_last_of(char(39));
    int minute_score= stoi(timeline_Score.substr(0,pos_first_score));
    int minute_card = stoi(timeline_Card.substr(0,pos_first_card));
    if (pos_first_score < pos_last_score)
    {

        overtime_score = stoi(timeline_Score.substr(pos_first_score+4,pos_last_score - pos_first_score -4));
    }
    if (pos_first_card < pos_last_card)
    {
        overtime_card = stoi(timeline_Card.substr(pos_first_card+4,pos_last_card - pos_first_card -4));
    }
    if (minute_score < minute_card)
    {
        return true;
    }
    else if (minute_score > minute_card)
    {
        return false;
    }
    else
    {
        if (overtime_score < overtime_card){
            return true;
        }
        else {
            return false;
        }
    }
}
MatchDetails::MatchDetails(const vector<Event> &scores, const vector<Event> &cards)
{
    int index_score = 0;
    int index_card = 0;
    while (index_score < scores.size() && index_card < cards.size())
    {
        if (goalcomeFirst(scores[index_score].timeline,cards[index_card].timeline))
        {
            listEvent.push_back(scores[index_score]);
            index_score++;
        }
        else
        {
            listEvent.push_back(cards[index_card]);
            index_card++;
        }
    }
    if (!(index_card == cards.size() && index_score == scores.size()))
    {
        if (index_card == cards.size())
        {
            while (index_score < scores.size())
            {
                listEvent.push_back(scores[index_score]);
                index_score++;
            }
        }
        else
        {
            while (index_card < cards.size())
            {
                listEvent.push_back(cards[index_card]);
                index_card++;
            }
        }
    }
}