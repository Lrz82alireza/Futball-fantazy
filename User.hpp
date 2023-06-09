#pragma once

#include "Account.hpp"
#include "Team.hpp"

#include <memory>
#include <map>

const int DEF_TRADE = 2;

const string ERR_PERM_USER = "Permission Denied";
const string ERR_NOT_FOUND_USER = "Not Found";

class User : public Account
{
private:
    shared_ptr<Team> team;
    pair<unsigned int, unsigned int> trade = {DEF_TRADE, DEF_TRADE};
    bool is_new = true;

public: 
    typedef pair<string, float> RANK;

    void sell_player(string &player_name);
    map<string, string> get_squad();

    User(string &username_, string &pass);

    RANK rank();
};

