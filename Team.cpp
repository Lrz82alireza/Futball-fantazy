#include "Team.hpp"

Player *Team::find_player(string player_name)
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
            players.push_back(new Player((int)i, input[i][j]));
        }
    }
}
