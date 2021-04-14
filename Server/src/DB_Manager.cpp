#include "DB_Manager.h"

DB_Manager::DB_Manager(const string& connectString) : sql(odbc, connectString) {}

int DB_Manager::queryUser(const string &username, const string &password, User& user) {
    if (username.empty() || password.empty()) {
        cerr << "Query for user account failed because username and password can't be empty" << endl;
        return -1;
    }
    char loginStatus, admin;
    sql << "SELECT USR, ISLOGIN, ISADMIN FROM USERS WHERE USR = :username AND PWD = :password", into(user.username), into(loginStatus), into(admin), use(username), use(password);
    //If can't find the user with input password
    if (!sql.got_data()) {
        cerr << "User \"" << username << "\" login failed." << endl;
        return -1;
    }
    //If user already logged in on another client
    if (loginStatus == 'Y') {
        cerr << "Prevented user \"" << username << "\" from login twice on another client program." << endl;
        return 1;
    }
    else {
        //Change user status to logged in
        char value = 'Y';
        sql << "UPDATE USERS SET ISLOGIN = :value WHERE USR = :username", use(value), use(username);
    }

    cout << "User " << username << " is logging in." << endl;
    if (admin == 'Y') {
        cout << username << " is an admin." << endl;
        user.isAdmin = true;
    }
    else user.isAdmin = false;
    return 0;
}

int DB_Manager::insertUser(const string &username, const string &password) {
    if (username.empty() || password.empty()) {
        cerr << "Query for user account failed because username and password can't be empty" << endl;
        return -1;
    }
    string dbUsername;
    sql << "SELECT USR FROM USERS WHERE USR = :username", into(dbUsername), use(username);
    //If the user exists in database
    if (sql.got_data()) {
        cerr << "Can't register account " << username << " because it already exists." << endl;
        return 1;
    }
    char loginStatus = 'N', isAdmin = 'N';
    //Insert a new account into database
    sql << "INSERT INTO USERS VALUES(:username, :password, :loginStatus, :isAdmin)", use(username), use(password), use(loginStatus), use(isAdmin);
    cout << "Account " << username << " has been registered successfully." << endl;
    return 0;
}

void DB_Manager::logoutUser(const string &username) {
    if (username.empty())
        return;
    char value = 'N';
    sql << "UPDATE USERS SET ISLOGIN = :value WHERE USR = :username", use(value), use(username);
    cout << "User " << username << " has logged out." << endl;
}

void DB_Manager::logoutAll() {
    char value = 'N';
    sql << "UPDATE USERS SET ISLOGIN = :value", use(value);
}