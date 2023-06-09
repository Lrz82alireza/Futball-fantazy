#include "User.hpp"

void User::sell_player(string &player_name)
{
    shared_ptr<Player> player = team->find_player(player_name);
    if (player == nullptr)
        throw runtime_error(ERR_NOT_FOUND);
    if (!is_new && trade.second <= 0)
        throw runtime_error(ERR_PERM);

    this->budget += player->get_price();
    trade.second--;
    team->erase_player(player);
}

bool User::buy_player(shared_ptr<Player> &player)
{
    if (!is_new && trade.first <= 0)
        return false;
    if (this->budget > player->get_price())
    {
        trade.first--;
        team->add_player(player);
        this->budget -= player->get_price();

        if (!is_new && this->team->get_players().size() == TEAM_SIZE)
            is_new = false;

        return true;
    }
    return false;
}

map<string, string> User::get_squad()
{
    return team->get_players_of_team();
}

void User::update()
{
    this->trade = {DEF_TRADE, DEF_TRADE};
}

User::User(string &username_, string &pass)
    : Account(username_, pass)
{
    this->team = make_shared<Team>(username_);
}

pair<string, float> User::rank()
{
    return RANK(this->username, team->players_score_sum());
}