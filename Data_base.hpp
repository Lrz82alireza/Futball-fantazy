#pragma once

#include "Week.hpp"
#include "Team.hpp"
#include "Admin.hpp"
#include "User.hpp"

class Data_base
{
private:
    vector<Week *> weeks;
    vector<Team *> teams;
    vector<Account *> accounts;
public:
    Data_base(/* args */);
    ~Data_base();
};

Data_base::Data_base(/* args */)
{
}

Data_base::~Data_base()
{
}
