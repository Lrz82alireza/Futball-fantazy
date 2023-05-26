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
    Data_base(const CSS_input &league_input, const vector<CSS_input> &weeks_input);
    ~Data_base();
};
