#include "User.hpp"

void User::sell_player(string &player_name)
{
    shared_ptr<Player> player = team->find_player(player_name);
    if (player == nullptr)
        throw runtime_error(ERR_NOT_FOUND_USER);
    if (!is_new && trade.second <= 0)
        throw runtime_error(ERR_PERM_USER);

    team->erase_player(player);
}

map<string, string> User::get_squad()
{
    return team->get_players_of_team();
}

User::User(string &username_, string &pass)
    : Account(username_, pass)
{
    this->team = make_shared<Team>(username_);
}

pair<string, float> User::rank()
{
    return RANK(this->username, team->get_scores_sum());
}
