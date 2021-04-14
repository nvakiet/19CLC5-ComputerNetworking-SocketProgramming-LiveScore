#include"DB_Structs.h"
#include <windows.h>

void setBuffer(char *newBuf, size_t newLen, vector<char>&buf) {
    buf.resize(newLen);
    if (newBuf != nullptr)
        buf.assign(newBuf, newBuf + newLen);
}

void appendBuffer(char *data, size_t len, vector<char>&buf) {
    if (data != nullptr)
        buf.insert(buf.end(), data, data + len);
}
bool extractBuffer(char *extBuf, size_t extLen, vector<char>&buf) {
    if (extLen > buf.size())
        return false;
    if (extBuf != nullptr) {
        std::copy(buf.begin(), buf.begin() + extLen, extBuf);
    }
    buf.erase(buf.begin(), buf.begin() + extLen);
    return true;
}

MatchInfo::MatchInfo( vector<char> response){ 
        int expectedSize = 0;
        extractBuffer((char*)&expectedSize,sizeof(size_t), response);
        id.resize(expectedSize);
        extractBuffer((char*)&id[0],expectedSize, response);

        extractBuffer((char*)&expectedSize,sizeof(size_t), response);
        timeMatch.resize(expectedSize);
        extractBuffer((char*)&timeMatch[0],expectedSize, response);

        extractBuffer((char*)&expectedSize,sizeof(size_t), response);
        teamA.resize(expectedSize);
        extractBuffer((char*)&teamA[0],expectedSize,response);

        extractBuffer((char*)&expectedSize,sizeof(size_t), response);
        teamB.resize(expectedSize);
        extractBuffer((char*)&teamB[0],expectedSize,response);

        extractBuffer((char*)&scoreA,sizeof(unsigned int),response);
        extractBuffer((char*)&scoreB,sizeof(unsigned int),response);
}

void MatchInfo::toByteStream(vector<char>&result){
    if(!result.empty()){
        result.erase(result.begin(),result.end());
    }
	size_t sizeID = id.size();
    size_t sizeTime  = timeMatch.size();
    size_t sizenameA = teamA.size();
	size_t sizenameB = teamB.size();
    setBuffer((char*)&sizeID,sizeof(size_t),result);
    appendBuffer((char*)&id[0],sizeID,result);
    appendBuffer((char*)&sizeTime,sizeof(size_t),result);
    appendBuffer((char*)&timeMatch[0],sizeTime,result);
    appendBuffer((char*)&sizenameA,sizeof(size_t),result);
    appendBuffer((char*)&teamA[0],sizenameA,result);
    appendBuffer((char*)&sizenameB,sizeof(size_t),result);
    appendBuffer((char*)&teamB[0],sizenameB,result);
    appendBuffer((char*)&scoreA,sizeof(unsigned int),result);
    appendBuffer((char*)&scoreB,sizeof(unsigned int),result);
}
