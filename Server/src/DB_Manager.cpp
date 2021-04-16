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

void DB_Manager::queryMatches(ListMatch &list) {
    //Query for recent matches within 7 days and store them into a rowset for extracting data
    rowset<row> rs = (sql.prepare << "select top 20 m.ID, t1.NAME, t2.NAME, m.STARTTIME, m.BREAKTIME, m.OVERTIME, m.STATUS_MATCH from MATCH m join TEAM t1 on (m.ID_TEAMA = t1.IDTEAM) join TEAM t2 on (m.ID_TEAMB = t2.IDTEAM) where DATEDIFF(DAY, m.STARTTIME, GETDATE()) <= 20 order by m.STARTTIME desc");
    //Iterate each row to push a match into the list
    for (auto it = rs.begin(); it != rs.end(); ++it) {
        MatchInfo m;
        m.id = (*it).get<string>(0); //Match ID
        m.teamA = (*it).get<string>(1); //Team name A
        m.teamB = (*it).get<string>(2); //Team name B
        //If the match status is null, get the current playing time of the match
        if ((*it).get_indicator(6) == i_null) {
            tm tmStart = (*it).get<tm>(3);
            time_t startTime = mktime(&tmStart);
            int breakTime = (*it).get<int>(4), overTime = (*it).get<int>(5);
            double minute = (difftime(time(nullptr), startTime) / 60) - breakTime - overTime;
            //If the match hasn't started, get the start time as string
            if (minute < 0) {
                //HH:MM YYYY-MM-DD
                char timestr[17];
                strftime(timestr, 17, "%R %F", &tmStart);
                m.timeMatch = timestr;
            }
            else if (minute > 90) {
                //If match has ended but no FT is triggered
                //Set match time as FT
                m.timeMatch = "FT";
            }
            else {
                //Else get the number of minute currently playing
                m.timeMatch = to_string((int)minute) + '\'';
                if (overTime > 0) {
                    m.timeMatch += " + " + to_string(overTime) + '\'';
                }
            }
        }
        else {
            //If the match status if FT or HT, use those status as Match time
            m.timeMatch = (*it).get<string>(6);
        }
        list.LstMatch.emplace_back(m);
    }

    //Get score result for matches
    for (auto it = list.LstMatch.begin(); it != list.LstMatch.end(); ++it) {
        //Get score team A
        sql << "select top 1 dts1.SCORE_A from DETAILS_SCORE dts1 where dts1.IDMATCH = :id order by dts1.SCORE_A desc", into((*it).scoreA), use((*it).id, "id");
        if (!sql.got_data()) {
            (*it).scoreA = 0;
        }
        //Get score team B
        sql << "select top 1 dts1.SCORE_B from DETAILS_SCORE dts1 where dts1.IDMATCH = :id order by dts1.SCORE_B desc", into((*it).scoreB), use((*it).id, "id");
        if (!sql.got_data()) {
            (*it).scoreB = 0;
        }
    }
}