#pragma once

#include "Account.hpp"
#include "Team.hpp"

#include <memory>
#include <map>

const int DEF_TRADE = 2;

class User : public Account
{
private:
    shared_ptr<Team> team;
    pair<unsigned int, unsigned int> trade = {DEF_TRADE, DEF_TRADE};
    bool is_new = true;

public: 
    typedef pair<string, float> RANK;

    void sell_player(string &player_name);
    void buy_player(shared_ptr<Player> &player);

    map<string, shared_ptr<Player>> get_squad();

    User(string &username_, string &pass);

    RANK rank();
};

