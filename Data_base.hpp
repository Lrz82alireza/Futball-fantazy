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

Data_base::Data_base(const CSS_input &league_input, const vector<CSS_input> &weeks_input)
{
    for (int i = 0; i < league_input.size(); i++)
    {
        teams.push_back(new Team(league_input[i]));
    }

    for (int i = 0; i < weeks_input.size(); i++)
    {
        
    }
}

Data_base::~Data_base()
{
}
