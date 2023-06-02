#pragma once

#include <algorithm>

#include "Functions.hpp"
#include "Player.hpp"


class Team
{
private:
    string name;
    vector<float> score_in_week;
    vector<shared_ptr<Player>> players;

public:
    string get_name() { return this->name; }

    shared_ptr<Player> find_player(string player_name);
    Team(vector<vector<string>> input);
    Team(string name_);
};
