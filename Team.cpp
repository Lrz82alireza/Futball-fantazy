#include "Team.hpp"

Team::Team_state Team::get_state()
{
    Team::Team_state state;

    state.name = this->name;
    state.score = get_scores_sum();
    for_each(weeks_info.begin(), weeks_info.end(), [&](Team::Week_info info){
        state.goals_for += info.goals_for;
    });
    for_each(weeks_info.begin(), weeks_info.end(), [&](Team::Week_info info){
        state.goals_against += info.goals_against;
    });

    return state;
}

float Team::get_scores_sum()
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
