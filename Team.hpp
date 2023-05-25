#pragma once

#include "Player.hpp"

class Team
{
private:
    string name;
    vector<float> score_in_week;
    vector<Player *> players;
public:
    Team(vector<vector<string>> input);
    ~Team();
};

Team::Team(vector<vector<string>> input)
{
    this->name = input[0][0];

    for (int i = 1; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            players.push_back(new Player(i, input[i][j]));
        }
    }
}

Team::~Team()
{
}
