#pragma once

#include <map>
#include <algorithm>
#include <memory>

#include "Functions.hpp"
#include "Gk.hpp"
#include "Md.hpp"
#include "Fw.hpp"
#include "Df.hpp"

const int TEAM_SIZE = 5;
const string EMPTY_ERR = "Empty";
const string ERR_PLAYER_NOT_AVAILABLE = "This player is not available for next week";
const string CAPTAIN = "(CAPTAIN)";

enum
{
    LOSE_POINT = 0,
    EQUAL_POINT = 1,
    WIN_POINT = 3,
};

class Team
{

public:
    struct Week_info
    {
        float score = 0;
        int goals_for = 0;
        int goals_against = 0;
    };

    struct Team_state
    {
        string name;
        float score = 0;
        int goals_for = 0;
        int goals_against = 0;
    };

    Team_state get_state();
    Week_info get_week_info(int weeknum) { return weeks_info[weeknum]; }
    string get_name() { return this->name; }
    vector<shared_ptr<Player>> get_players(int role = 0);
    float get_scores_sum();
    float get_costs_sum();

    float players_score_sum();

    void add_player(shared_ptr<Player> &player);

    void new_week(Week_info &new_info) { weeks_info.push_back(new_info); }

    shared_ptr<Player> find_player(string player_name);
    void erase_player(shared_ptr<Player> &player);

    void players_set_availability();

    bool set_captain(string name_);

    Team(vector<vector<string>> input);
    Team(string name_);

    map<string, string> get_players_of_team();

private:
    const vector<string> GET_PLAYERS_ORDER = {"GK", "DF1", "DF2", "MD", "FW"}; 

    string name;
    vector<float> score_in_week;
    vector<shared_ptr<Player>> players;
    shared_ptr<Player> captain;

    vector<Week_info> weeks_info;
    shared_ptr<Player> Player_creator(string &name_, int role = 0);
};