#pragma once

#include "Week.hpp"
#include "Team.hpp"
#include "Admin.hpp"
#include "User.hpp"

enum
{
    POST,
    GET,
    PUT,
    DELETE
};

enum
{
    // DEFAULT
    TEAM_OF_THE_WEEK,
    PLAYERS,
    LEAGUE_STANDINGS,
    USERS_RANKING,
    MATCHES_RESULT_LEAGUE,
    // NO ACC
    SIGNUP,
    REGISTER_ADMIN,
    LOGIN,
    // USER
    SELL_PLAYER,
    BUY_PLAYER,
    SQUAD,
    // ADMIN
    CLOSE_TRANSFER_WINDOW,
    OPEN_TRANSFER_WINDOW,
    PASS_WEEK,
    // IN ACC
    LOGOUT
};

enum
{
    ADMIN,
    USER,
    IN_ACC,
    NO_ACC,
    DEFAULT,
};

class Data_base
{
private:
    vector<shared_ptr<Week>> weeks;
    vector<shared_ptr<Team>> teams;
    vector<shared_ptr<Account>> accounts;

    int prem_state = DEFAULT;

    pair<int, int> make_command_code(pair<string, string> &command);
public:
    void manage_command(pair<string, string> &command, vector<string> &arg);

    Data_base(const CSV_input &league_input, const vector<CSV_input> &weeks_input);
    ~Data_base();
};
