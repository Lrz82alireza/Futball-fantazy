#pragma once

#include <algorithm>

#include "Functions.hpp"
#include "Player.hpp"

class Team
{
    struct Week_info
    {
        float score = 0;
        int goals_for = 0;
        int goals_against = 0;
    };

private:
    string name;
    vector<float> score_in_week;
    vector<shared_ptr<Player>> players;

    vector<Week_info> weeks_info;

public:
    string get_name() { return this->name; }

    shared_ptr<Player> find_player(string player_name);
    Team(vector<vector<string>> input);
    Team(string name_);
};
