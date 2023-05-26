#include "Data_base.hpp"

Data_base::Data_base(const CSV_input &league_input, const vector<CSV_input> &weeks_input)
{
    for (CSV_input::size_type i = 0; i < league_input.size(); i++)
    {
        teams.push_back(make_shared<Team>(league_input[i]));
    }

    for (vector<CSV_input>::size_type i = 0; i < weeks_input.size(); i++)
    {
        this->weeks.push_back(make_shared<Week>(weeks_input[i], this->teams));
    }
}