#include "Team.hpp"

float Team::get_scores()
{
    float sum = 0;
    for (auto i : weeks_info)
    {
        sum += i.score;
    }
    return sum;
}

shared_ptr<Player> Team::find_player(string player_name)
{
    return find_by_name<Player>(this->players, player_name);
}

Team::Team(vector<vector<string>> input)
{
    this->name = input[0][0];

    for (vector<vector<string>>::size_type i = 1; i < input.size(); i++)
    {
        for (vector<string>::size_type j = 0; j < input[i].size(); j++)
        {
            players.push_back(make_shared<Player>((int)i, input[i][j]));
        }
    }
}

Team::Team(string name_)
{
    this->name = name_;
}
