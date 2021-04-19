#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "DB_Structs.h"
#include "soci.h"
#include "odbc/soci-odbc.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace soci;
using namespace std;

//A class for handling communication between the server program and the database
class DB_Manager {
private:
    session sql;
public:
    DB_Manager(const string& connectString);
    //Query for a user account that has valid username, correct password and isn't already logged in
    //Return code: -1 = invalid username or wrong password, 0 = login success, 1 = user already logged in
    int queryUser(const string &username, const string &password, User& user);
    //Insert an account into database
    //Return code: -1 = username or password is empty, 0 = register success, 1 = account already exists
    int insertUser(const string &username, const string &password);
    //Change the login status of user in database to 'N' (logout)
    void logoutUser(const string &username);
    void logoutAll();
    //Get match list from database
    void queryMatches(ListMatch &list);
    //Get detail event of a match
    void queryMatchDetail(const string &ID, MatchDetails& match);
};

#endif