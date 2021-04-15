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
// MatchInfo::MatchInfo(const char* ID, const char* time,const char* nameA,const char* nameB,unsigned int score_A,unsigned score_B):
//             id(ID),timeMatch(time),teamA(nameA),teamB(nameB),scoreA(score_A),scoreB(score_B){}
ListMatch::ListMatch(vector<char> response){
    size_t expectedSize = 0;

    while(!response.empty()){
        extractBuffer((char*)&expectedSize,sizeof(size_t),response);
        vector<char> cache;
        cache.resize(expectedSize);
        extractBuffer((char*)&cache[0],expectedSize,response);
        MatchInfo *temp = new MatchInfo(cache);
        LstMatch.push_back(*temp);
    }
}
void ListMatch::toByteStream(vector<char>&result){
    if (!result.empty())
    {
        result.erase(result.begin(), result.end());
    }
    for(int index =0;index<LstMatch.size();index++){
        vector<char> cache; 
        LstMatch[index].toByteStream(cache);
        size_t sizeCache = cache.size();
        appendBuffer((char *)&sizeCache, sizeof(size_t), result);
        appendBuffer((char *)&cache[0], sizeCache, result);
    }
    
}
//FOR DEBUG ONLY: 
// ListMatch::ListMatch(){
//     MatchInfo a("VNTL","15:30","Viet Nam","Thai Land",2,1);
//     MatchInfo b("AS","20:33","Australia","Singarpore",4,4);
//     LstMatch.push_back(a);
//     LstMatch.push_back(b);
// }