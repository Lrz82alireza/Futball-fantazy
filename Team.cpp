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
        {
            players_.push_back(i);
        }
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

float Team::get_costs_sum()
{
    float sum = 0;
    for (auto i : this->players)
    {
        sum += i->get_price();
    }
    return sum;
}

float Team::players_score_sum()
{
    float sum = 0;
    for (auto i : players)
    {
        sum += i->scores_sum();
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
    if (this->captain == player)
        this->captain = nullptr;
    players.erase(remove(players.begin(), players.end(), player), players.end());
}

void Team::players_set_availability()
{
    for (auto i : this->players)
    {
        i->set_availability();
    }
}

bool Team::set_captain(string name_)
{
    shared_ptr<Player> cap = find_by_name(this->players, name_);
    if (cap == nullptr)
        return false;
    this->captain = cap;
    return true;
}

Team::Team(vector<vector<string>> input)
{
    this->name = input[0][0];

    for (vector<vector<string>>::size_type i = 1; i < input.size(); i++)
    {
        for (vector<string>::size_type j = 0; j < input[i].size(); j++)
        {
            players.push_back(Player_creator(input[i][j], int(i)));
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
    int counter = 0;
    map<string, string> tmp;
    if (players.size() < TEAM_SIZE)
        throw runtime_error(EMPTY_ERR);

    for (int i = GK; i <= FW; i++)
    {
        vector<shared_ptr<Player>> players_ = get_players(i);
        sort_players_alphabetically(players_);
        for (auto i : players_)
        {
            string p_name = i->get_name();
            if (this->captain == i)
                p_name += " " + CAPTAIN;
            tmp[GET_PLAYERS_ORDER[counter]] = p_name;
        }
    }
    return tmp;
}

shared_ptr<Player> Team::Player_creator(string &name_, int role)
{
    switch (role)
    {
    case GK:
        return make_shared<Gk>(role, name_);
        break;
    case MD:
        return make_shared<Md>(role, name_);
        break;
    case DF:
        return make_shared<Df>(role, name_);
        break;
    case FW:
        return make_shared<Fw>(role, name_);
        break;
    default:
        return make_shared<Player>(role, name_);
        break;
    }
}
