#pragma once

#include "Player.hpp"

class Team
{
private:
    string name;
    vector<float> score_in_week;
    vector<Player *> players;
public:
    Team(/* args */);
    ~Team();
};

Team::Team(/* args */)
{
}

Team::~Team()
{
}
