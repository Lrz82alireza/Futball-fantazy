#pragma once

#include "Account.hpp"
#include "Team.hpp"
#include <memory>

class User : public Account
{
private:
    shared_ptr<Team> team;
public: 
    typedef pair<string, float> RANK;

    User(string &username_, string &pass);

    RANK rank();
};

