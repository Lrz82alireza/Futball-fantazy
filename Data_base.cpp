#include "Data_base.hpp"

Data_base::Data_base(const CSS_input &league_input, const vector<CSS_input> &weeks_input)
{
    for (CSS_input::size_type i = 0; i < league_input.size(); i++)
    {
        teams.push_back(new Team(league_input[i]));
    }

    for (vector<CSS_input>::size_type i = 0; i < weeks_input.size(); i++)
    {
        ///////////
    }
}