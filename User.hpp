#pragma once

#include "Account.hpp"
#include "Team.hpp"
#include <memory>

class User : public Account
{
private:
    shared_ptr<Team> team;
public:
    User(string &username_, string &pass);
};

