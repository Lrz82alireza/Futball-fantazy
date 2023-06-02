#include "Data_base.hpp"

void Data_base::init_command_map()
{
    Command_map temp;

    // ADMIN
    
    this->command_maps.push_back(temp);
    temp.clear();

    // USER

    this->command_maps.push_back(temp);
    temp.clear();

    // IN_ACC
    temp[pair<int, int> (POST, LOGOUT)] = &Data_base::logout;

    this->command_maps.push_back(temp);
    temp.clear();

    // NO_ACC
    temp[pair<int, int> (POST, SIGNUP)] = &Data_base::signup;
    temp[pair<int, int> (POST, LOGIN)] = &Data_base::login;
    temp[pair<int, int> (POST, REGISTER_ADMIN)] = &Data_base::register_admin;

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
    if (this->current.acc != nullptr)
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

// Commands

void Data_base::signup(vector<string> &arg)
{
    check_signup_arg(arg);

    this->users.push_back(make_shared<User>(arg[ARG_T_NAME_IN_REGISTER], arg[ARG_PASS_IN_REGISTER]));
    this->current.acc = users.back();
    this->current.prem_state = USER;
}

void Data_base::check_signup_arg(vector<string> &arg)
{
    if (this->current.acc != nullptr)
        throw runtime_error(ERR_PERM);
    if (arg[0] != ARG_CHAR)
        throw runtime_error(ERR_BAD_REQ);
    if (arg[ARG_T_NAME_REGISTER] != "team_name")
        throw runtime_error(ERR_BAD_REQ);
    if (arg[ARG_PASS_REGISTER] != "password")
        throw runtime_error(ERR_BAD_REQ);

    if (find_by_name<User>(this->users, arg[ARG_T_NAME_IN_REGISTER]) != nullptr)
        throw runtime_error(ERR_BAD_REQ);
}

void Data_base::login(vector<string> &arg)
{
    check_login_arg(arg);

    this->current.prem_state = USER;
    this->current.acc = find_by_name<User>(this->users, arg[ARG_T_NAME_IN_REGISTER]);
}

void Data_base::check_login_arg(vector<string> &arg)
{
    if (this->current.acc == nullptr)
        throw runtime_error(ERR_PERM);
    if (arg[0] != ARG_CHAR)
        throw runtime_error(ERR_BAD_REQ);
    if (arg[ARG_T_NAME_REGISTER] != "team_name")
        throw runtime_error(ERR_BAD_REQ);
    if (arg[ARG_PASS_REGISTER] != "password")
        throw runtime_error(ERR_BAD_REQ);

    shared_ptr<User> user_ = find_by_name<User>(this->users, arg[ARG_T_NAME_IN_REGISTER]);
    if (user_ == nullptr)
        throw runtime_error(ERR_NOT_FOUND);
    if (user_->check_pass(arg[ARG_PASS_IN_REGISTER]))
        throw runtime_error(ERR_PERM);
}

void Data_base::register_admin(vector<string> &arg)
{
    check_register_admin_arg(arg);

    this->current.acc = this->admin;
    this->current.prem_state = ADMIN;
}

void Data_base::check_register_admin_arg(vector<string> &arg)
{
    if (this->current.acc == nullptr)
        throw runtime_error(ERR_PERM);
    if (arg[0] != ARG_CHAR)
        throw runtime_error(ERR_BAD_REQ);
    if (arg[ARG_T_NAME_REGISTER] != "team_name")
        throw runtime_error(ERR_BAD_REQ);
    if (arg[ARG_PASS_REGISTER] != "password")
        throw runtime_error(ERR_BAD_REQ);

    if (admin->get_name() != arg[ARG_T_NAME_IN_REGISTER])
        throw runtime_error(ERR_BAD_REQ); 
    if (admin->check_pass(arg[ARG_PASS_IN_REGISTER]))
        throw runtime_error(ERR_BAD_REQ); 
}

void Data_base::logout(vector<string> &arg)
{
    check_logout_arg(arg);

    this->current.acc = nullptr;
    this->current.prem_state = NO_ACC;
}

void Data_base::check_logout_arg(vector<string> &arg)
{
    if (current.acc == nullptr)
        throw runtime_error(ERR_BAD_REQ);
}

Data_base::Data_base(const CSV_input &league_input, const vector<shared_ptr<CSV_input>> &weeks_input)
{
    for (CSV_input::size_type i = 0; i < league_input.size(); i++)
    {
        teams.push_back(make_shared<Team>(league_input[i]));
    }

    for (vector<shared_ptr<CSV_input>>::size_type i = 0; i < weeks_input.size(); i++)
    {
        this->weeks.push_back(make_shared<Week>(*weeks_input[i], this->teams));
    }

    this->admin = make_shared<Admin>(ADMIN_NAME, ADMIN_PASS); 

    init_command_map();
}
