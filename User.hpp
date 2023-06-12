#pragma once

#include "Account.hpp"
#include "Team.hpp"

#include <memory>
#include <map>

const int DEF_TRADE = 2;
const float USER_DEF_BUDGET = 2500;

class User : public Account
{
private:
    shared_ptr<Team> team;
    float budget = USER_DEF_BUDGET;
    pair<unsigned int, unsigned int> trade = {DEF_TRADE, DEF_TRADE};
    bool is_new = true;

public: 
    typedef pair<string, float> RANK;

    float get_budget() { return budget; }

    void sell_player(string &player_name);
    void buy_player(shared_ptr<Player> &player);

    map<string, string> get_squad();

    shared_ptr<Team> get_team() {return team;};

    User(string &username_, string &pass);

    RANK rank();
};

