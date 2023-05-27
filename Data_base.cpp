#include "Data_base.hpp"

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

    //////////////
    // default commands
    //////////////
    if (in_acc)
    {
        // in_acc default
        switch (prem_state)
        {
        case ADMIN:
            /* code */
            break;
        case USER:
            // code
            break;
        }
    }
    else
    {
        // out of acc commands
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
}