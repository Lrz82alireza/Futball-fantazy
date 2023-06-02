#include "Data_base.hpp"

void Data_base::init_command_map()
{
    Command_map temp;

    // ADMIN
    // temp[pair<int, int> (2, 2)] = &Data_base::signup;
    this->command_maps.push_back(temp);
    temp.clear();


    // USER
    //
    this->command_maps.push_back(temp);
    temp.clear();

    // IN_ACC
    //
    this->command_maps.push_back(temp);
    temp.clear();

    // NO_ACC
    //
    this->command_maps.push_back(temp);
    temp.clear();

    // DEFAULT
    //
    this->command_maps.push_back(temp);
    temp.clear();
}

bool Data_base::call_command_func(pair<int, int> &key, Command_map &command_map, vector<string> &arg)
{
    auto it = command_map.find(key);
    if (it == command_map.end())
        return false;
    (*this.*command_map[key])(arg);
    return true;
}

pair<int, int> Data_base::make_command_code(pair<string, string> &command)
{
    pair<int, int> command_code = {-1, -1};

    // first command
    if (command.first == "POST")
        command_code.first = POST;
    else if (command.first == "GET")
        command_code.first = GET;
    else if (command.first == "PUT")
        command_code.first = PUT;
    else if (command.first == "DELETE")
        command_code.first = DELETE;
    else
        throw runtime_error("Bad Request");

    // second command
    // default
    if (command.second == "team_of_the_week")
        command_code.second = TEAM_OF_THE_WEEK;

    else if (command.second == "players")
        command_code.second = PLAYERS;

    else if (command.second == "league_standings")
        command_code.second = LEAGUE_STANDINGS;

    else if (command.second == "users_ranking")
        command_code.second = USERS_RANKING;

    else if (command.second == "matches_result_league")
        command_code.second = MATCHES_RESULT_LEAGUE;

    // NO ACC
    else if (command.second == "signup")
        command_code.second = SIGNUP;

    else if (command.second == "login")
        command_code.second = LOGIN;

    else if (command.second == "register_admin")
        command_code.second = REGISTER_ADMIN;

    // IN ACC
    if (command.second == "logout")
        command_code.second = LOGOUT;

    // user
    else if (command.second == "sell_player")
        command_code.second = SELL_PLAYER;

    else if (command.second == "buy_player")
        command_code.second = BUY_PLAYER;

    else if (command.second == "squad")
        command_code.second = SQUAD;

    // admin
    else if (command.second == "close_transfer_window")
        command_code.second = CLOSE_TRANSFER_WINDOW;

    else if (command.second == "open_transfer_window")
        command_code.second = OPEN_TRANSFER_WINDOW;

    else if (command.second == "pass_week")
        command_code.second = PASS_WEEK;

    if (command_code.second == -1)
        throw runtime_error("Not Found");

    return command_code;
}

void Data_base::manage_command(pair<string, string> &command, vector<string> &arg)
{
    pair<int, int> command_code = make_command_code(command);

    call_command_func(command_code, this->command_maps[DEFAULT], arg);
    if (this->current.in_acc)
    {
        call_command_func(command_code, this->command_maps[IN_ACC], arg);
        switch (this->current.prem_state)
        {
        case ADMIN:
            if (!call_command_func(command_code, this->command_maps[ADMIN], arg))
                throw runtime_error("Permission Denied");
            break;
        case USER:
            if (!call_command_func(command_code, this->command_maps[USER], arg))
                throw runtime_error("Permission Denied");
            break;
        }
    }
    else
    {
        if (!call_command_func(command_code, this->command_maps[NO_ACC], arg))
            throw runtime_error("Permission Denied");
    }
}

Data_base::Data_base(const CSV_input &league_input, const vector<CSV_input> &weeks_input)
{
    for (CSV_input::size_type i = 0; i < league_input.size(); i++)
    {
        teams.push_back(make_shared<Team>(league_input[i]));
    }

    for (vector<CSV_input>::size_type i = 0; i < weeks_input.size(); i++)
    {
        this->weeks.push_back(make_shared<Week>(weeks_input[i], this->teams));
    }

    init_command_map();
}
