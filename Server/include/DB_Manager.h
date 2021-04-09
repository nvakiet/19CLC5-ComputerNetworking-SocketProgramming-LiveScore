#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "DB_Structs.h"
#include "soci.h"
#include "odbc/soci-odbc.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace soci;
using namespace std;

class DB_Manager {
private:
    session sql;
public:
    DB_Manager(const string& connectString);
    //Query for a user account that has valid username, correct password and isn't already logged in
    //Return code: -1 = invalid username or wrong password, 0 = login success, 1 = user already logged in
    int queryUser(const string &username, const string &password, User& user);
    //Change the login status of user in database to 'N' (logout)
    void logoutUser(const string &username);
    void logoutAll();
};

#endif