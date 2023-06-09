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

void Team::add_player(shared_ptr<Player> &player)
{
    if (find_player(player->get_name()) != nullptr)
        throw runtime_error(ERR_BAD_REQ);

    vector<shared_ptr<Player>> players_ = this->get_players(player->get_role());

    if (player->get_role() == DF)
    {
        if (players_.size() == 2)
            throw runtime_error(ERR_BAD_REQ);
    }
    else if (players_.size() != 0)
        throw runtime_error(ERR_BAD_REQ);

    if (!player->is_available())
        throw runtime_error(ERR_PLAYER_NOT_AVAILABLE);

    this->players.push_back(player);
}

shared_ptr<Player> Team::find_player(string player_name)
{
    return find_by_name<Player>(this->players, player_name);
}

void Team::erase_player(shared_ptr<Player> &player)
{
    players.erase(remove(players.begin(), players.end(), player), players.end());
}

void Team::players_set_availability()
{
    for (auto i : this->players)
    {
        i->set_availability();
    }
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

bool compair_alphabetically(const shared_ptr<Player> &p1, const shared_ptr<Player> &p2)
{
    return p1->get_name() < p2->get_name();
}

void sort_players_alphabetically(vector<shared_ptr<Player>> &v)
{
    sort(v.begin(), v.end(), compair_alphabetically);
}

map<string, string> Team::get_players_of_team()
{
    map<string, string> tmp;
    if (players.size() < TEAM_SIZE)
        throw runtime_error(EMPTY_ERR);
    else
    {
        tmp["GK"] = get_players(GK).back()->get_name();
        vector<shared_ptr<Player>> df = get_players(DF);
        sort_players_alphabetically(df);
        tmp["DF1"] = df.front()->get_name();
        tmp["DF2"] = df.back()->get_name();
        tmp["MD"] = get_players(MD).back()->get_name();
        tmp["FW"] = get_players(FW).back()->get_name();
        return tmp;
    }
}
