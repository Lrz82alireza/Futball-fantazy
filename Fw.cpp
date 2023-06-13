#include "Fw.hpp"

Fw::Fw(int &role, string &name)
    : Player(role, name)
{
}

void Fw::set_position(int pos)
{
    switch (pos)
    {
    case RIGHT_POS_FW:
        this->weeks_info.back().position = RIGHT_POS;
        break;
    case LEFT_POS_FW:
        this->weeks_info.back().position = LEFT_POS;
        break;

    default:
        this->weeks_info.back().position = MID_POS;
        break;
    }
}

void Fw::set_score(vector<shared_ptr<Player>> against_composition, int goals_for, int goals_against)
{
    Player::set_score(against_composition, goals_for, goals_against);
    int players_goal = this->weeks_info.back().goal;
    for (auto i = 0; i < players_goal; i++)
        add_score(GOAl_POINT);
    int players_assist = this->weeks_info.back().assist;
    for (auto i = 0; i < players_assist; i++)
        add_score(ASSIST_POINT);
    if (this->get_week_info().goal == 0)
        add_score(DEMERIT_POINT);
    this->score_algorithm();
}
