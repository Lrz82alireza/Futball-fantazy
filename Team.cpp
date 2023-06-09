#include "Team.hpp"

Team::Team_state Team::get_state()
{
    Team::Team_state state;

    state.name = this->name;
    state.score = get_scores_sum();
    for_each(weeks_info.begin(), weeks_info.end(), [&](Team::Week_info info)
             { state.goals_for += info.goals_for; });
    for_each(weeks_info.begin(), weeks_info.end(), [&](Team::Week_info info)
             { state.goals_against += info.goals_against; });

    return state;
}

vector<shared_ptr<Player>> Team::get_players(int role)
{
    if (role == 0)
        return players;

    vector<shared_ptr<Player>> players_;
    for (auto i : players)
    {
        if (i->get_role() == role)
            players_.push_back(i);
    }

    return players_;
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

void Team::erase_player(shared_ptr<Player> &player)
{
    players.erase(remove(players.begin(), players.end(), player), players.end());
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

bool compare_by_score(const shared_ptr<Player> &player1, const shared_ptr<Player> &player2)
{
    return player1->get_week_info().score > player2->get_week_info().score;
}

void sort_players_by_score(vector<shared_ptr<Player>> &players)
{
    sort(players.begin(), players.end(), compare_by_score);
}