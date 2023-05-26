#pragma once

#include "Week.hpp"
#include "Team.hpp"
#include "Admin.hpp"
#include "User.hpp"


class Data_base
{
private:
    vector<shared_ptr<Week>> weeks;
    vector<shared_ptr<Team>> teams;
    vector<shared_ptr<Account>> accounts;
public:
    Data_base(const CSV_input &league_input, const vector<CSV_input> &weeks_input);
    ~Data_base();
};
