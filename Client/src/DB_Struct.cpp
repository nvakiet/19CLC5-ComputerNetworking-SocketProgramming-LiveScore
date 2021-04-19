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
    if (!result.empty())
    {
        result.erase(result.begin(), result.end());
    }
    size_t sizeID = id.size();
    size_t sizeTime = timeMatch.size();
    size_t sizenameA = teamA.size();
    size_t sizenameB = teamB.size();
    setBuffer((char *)&sizeID, sizeof(size_t), result);
    appendBuffer((char *)&id[0], sizeID, result);
    appendBuffer((char *)&sizeTime, sizeof(size_t), result);
    appendBuffer((char *)&timeMatch[0], sizeTime, result);
    appendBuffer((char *)&sizenameA, sizeof(size_t), result);
    appendBuffer((char *)&teamA[0], sizenameA, result);
    appendBuffer((char *)&sizenameB, sizeof(size_t), result);
    appendBuffer((char *)&teamB[0], sizenameB, result);
    appendBuffer((char *)&scoreA, sizeof(unsigned int), result);
    appendBuffer((char *)&scoreB, sizeof(unsigned int), result);
}
// FOR DEBUG ONLY:
//MatchInfo::MatchInfo(const char *ID, const char *time, const char *nameA, const char *nameB, unsigned int score_A, unsigned score_B) : id(ID), timeMatch(time), teamA(nameA), teamB(nameB), scoreA(score_A), scoreB(score_B) {}
ListMatch::ListMatch(vector<char> response)
{
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
    if (!result.empty())
    {
        result.erase(result.begin(), result.end());
    }
    size_t sizeListMatch = LstMatch.size();
    setBuffer((char *)&sizeListMatch, sizeof(size_t), result);
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

Event::Event(vector<char> response) : scoreA(0), scoreB(0), isGoal(true)
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
// //FOR DEBUG ONLY:
// Event::Event()
// {
//     timeline = "62'";
//     namePlayerTeamA = "bahuy";
//     namePlayerTeamB.clear();
//     scoreA = 1;
//     scoreB = 0;
//     isGoal = true;
// }
// //FOR DEBUG ONLY:
// Event::Event(const char *t) : timeline(t)
// {
//     namePlayerTeamB = "yenbinh";
//     scoreA = 1;
//     scoreB = 2;
//     card = "Yellow";
//     isGoal = false;
// }
void Event::toByteStream(vector<char> &result)
{

    if (!result.empty())
    {
        result.erase(result.begin(), result.end());
    }
    size_t sizeTimeLine = timeline.size();
    size_t sizenameA = namePlayerTeamA.size();
    size_t sizenameB = namePlayerTeamB.size();
    size_t sizeCard = card.size();
    setBuffer((char *)&sizeTimeLine, sizeof(size_t), result);
    appendBuffer((char *)&timeline[0], sizeTimeLine, result);
    appendBuffer((char *)&sizenameA, sizeof(size_t), result);
    appendBuffer((char *)&namePlayerTeamA[0], sizenameA, result);
    appendBuffer((char *)&sizenameB, sizeof(size_t), result);
    appendBuffer((char *)&namePlayerTeamB[0], sizenameB, result);
    appendBuffer((char *)&scoreA, sizeof(unsigned int), result);
    appendBuffer((char *)&scoreB, sizeof(unsigned int), result);
    appendBuffer((char *)&sizeCard, sizeof(size_t), result);
    appendBuffer((char *)&card[0], sizeCard, result);
    appendBuffer((char *)&isGoal, sizeof(bool), result);
}
//For DEBUG ONLY:
// MatchDetails::MatchDetails()
// {
//     Event a;
//     Event b("88'");
//     listEvent.push_back(a);
//     listEvent.push_back(b);
//     vector<char> v1;
//     Event c("93'");
//     c.toByteStream(v1);
//     Event d(v1);
//     listEvent.push_back(d);
// }

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
    if (!result.empty())
    {
        result.erase(result.begin(), result.end());
    }
    size_t sizeListEvent = listEvent.size();
    setBuffer((char *)&sizeListEvent, sizeof(size_t), result);
    for (int index = 0; index < sizeListEvent; index++)
    {
        vector<char> cache;
        listEvent[index].toByteStream(cache);
        size_t sizeCache = cache.size();
        appendBuffer((char *)&sizeCache, sizeof(size_t), result);
        appendBuffer((char *)&cache[0], sizeCache, result);
    }
}
