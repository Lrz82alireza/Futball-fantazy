#pragma once

#include "Week.hpp"
#include "Team.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include "Functions.hpp"

#include <map>
#include <algorithm>

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
    ARG_REGISTER_NUM = 5,
};

enum
{
    ARG_T_NAME_PLAYERS = 1,
    ARG_T_NAME_IN_PLAYERS,
    ARG_PLAYERS_NUM = 3,
};

enum
{
    ARG_WEEKNUM = 1,
    ARG_WEEKNUM_IN,
    ARG_WEEKNUM_SIZE = 1,
};

struct Arg_get_players
{
    string name;
    int role = 0;
    bool sort_by_rank = false;
};

struct Arg_weeknum
{
    bool has_weeknum = false;
    int weeknum;
};



const string ARG_CHAR = "?";
const string ERR_PERM = "Permission Denied";
const string ERR_BAD_REQ = "Bad Request";
const string ERR_NOT_FOUND = "Not Found";

const string ADMIN_NAME = "admin";
const string ADMIN_PASS = "123456";

class Data_base;

typedef void (Data_base::*Command_func_ptr)(vector<string> &);

typedef map<pair<int, int>, Command_func_ptr> Command_map;

typedef struct CURRENT
{
    int week = -1;
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

    bool transfer_window = true;

    vector<Command_map> command_maps;
    void init_command_map();
    bool call_command_func(pair<int, int> &key, Command_map &command_map, vector<string> &arg);

    Current current;

    pair<int, int> make_command_code(pair<string, string> &command);

    // Commands
    void sell_player(vector<string> &arg);
    void check_trade_player_arg(vector<string> &arg);
    string make_trade_player_name(vector<string> &arg);

    void signup(vector<string> &arg);
    void check_signup_arg(vector<string> &arg);

    void login(vector<string> &arg);
    void check_login_arg(vector<string> &arg);

    void register_admin(vector<string> &arg);
    void check_register_admin_arg(vector<string> &arg);

    void logout(vector<string> &arg);
    void check_logout_arg(vector<string> &arg);

    void team_of_the_week(vector<string> &arg);

    void users_ranking(vector<string> &arg);

    void league_standings(vector<string> &arg);

    void get_players(vector<string> &arg);
    Arg_get_players make_arg_get_players(vector<string> &arg);
    void check_get_players_arg(vector<string> &arg);

    void matches_result_league(vector<string> &arg);
    void check_matches_result_league_arg(vector<string> &arg);
    Arg_weeknum make_arg_weeknum(vector<string> &arg);


    // Admin
    void close_transfer_window(vector<string> &arg);
    void open_transfer_window(vector<string> &arg);
    void pass_week(vector<string> &arg);


    // Accessories

public:
    void manage_command(pair<string, string> &command, vector<string> &arg);

    void show()
    {
        vector<string> args;

        args.push_back("?");
        args.push_back("week_num");
        args.push_back("1");
        team_of_the_week(args);
    }

    void update_current_week();

    Data_base(const CSV_input &league_input, const vector<shared_ptr<CSV_input>> &weeks_input);
};
