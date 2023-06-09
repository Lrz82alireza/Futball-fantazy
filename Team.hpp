#pragma once

#include <algorithm>

#include "Functions.hpp"
#include "Player.hpp"
#include <map>

const int TEAM_SIZE = 5;
const string EMPTY_ERR = "Empty";

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

    void new_week(Week_info &new_info) { weeks_info.push_back(new_info); }

    shared_ptr<Player> find_player(string player_name);

    Team(vector<vector<string>> input);
    Team(string name_);

    map<string, shared_ptr<Player>> get_players_of_team();

private:
    string name;
    vector<float> score_in_week;
    vector<shared_ptr<Player>> players;

    vector<Week_info> weeks_info;
    
};
