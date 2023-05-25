#pragma once

#include "Account.hpp"
#include "Team.hpp"

class User : public Account
{
private:
    Team *team;
public:
    User(/* args */);
    ~User();
};

User::User(/* args */)
{
}

User::~User()
{
}
