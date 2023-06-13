#include "Gk.hpp"

Gk::Gk(int &role, string &name)
    : Player(role, name)
{
}

void Gk::set_position(int pos)
{
    this->weeks_info.back().position = POS;
}

void Gk::set_score(vector<shared_ptr<Player>> against_composition , int goals_for , int goals_against)
{

    add_score(DEAFAULT_POINT);
    Player::set_score(against_composition , goals_for , goals_against);
    if (goals_against == 0)
        this->add_score(CLEAN_SHEET_POINT);
    else
    {
        for (auto i = 0 ; i < goals_against ; i++)
            this->add_score(DEMERIT_POINT);
    }
    this->score_algorithm();
}