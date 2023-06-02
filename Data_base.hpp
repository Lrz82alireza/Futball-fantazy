#pragma once

#include "Week.hpp"
#include "Team.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include "Functions.hpp"

#include <map>



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

enum
{
    ARG_T_NAME_REGISTER = 1,
    ARG_T_NAME_IN_REGISTER,
    ARG_PASS_REGISTER,
    ARG_PASS_IN_REGISTER,
};

const string ARG_CHAR = "?";
const string ERR_PERM = "Permission Denied";
const string ERR_BAD_REQ = "Bad Request";
const string ERR_NOT_FOUND = "Not Found";


class Data_base;

typedef void (Data_base::*Command_func_ptr)(vector<string> &);

typedef map<pair<int, int>, Command_func_ptr> Command_map;

typedef struct CURRENT
{
    int week = 0;
    int prem_state = DEFAULT;
    shared_ptr<Account> acc = nullptr;
} Current;

class Data_base
{
private:
    vector<shared_ptr<Week>> weeks;
    vector<shared_ptr<Team>> teams;
    vector<shared_ptr<User>> users;
    shared_ptr<Admin> admin;

    vector<Command_map> command_maps;
    void init_command_map();
    bool call_command_func(pair<int, int> &key, Command_map &command_map, vector<string> &arg);

    Current current;

    pair<int, int> make_command_code(pair<string, string> &command);

    // Commands
    void signup(vector<string> &arg);
    void check_signup_arg(vector<string> &arg);

    void login(vector<string> &arg);
    void check_login_arg(vector<string> &arg);

    void register_admin(vector<string> &arg);
    void check_register_admin_arg(vector<string> &arg);

    // Accessories


public:
    void manage_command(pair<string, string> &command, vector<string> &arg);

    Data_base(const CSV_input &league_input, const vector<shared_ptr<CSV_input>> &weeks_input);
};
