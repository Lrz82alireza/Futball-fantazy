#include "Df.hpp"

Df::Df(int &role, string &name)
    : Player(role, name)
{
}

void Df::set_position(int pos)
{
    switch (pos)
    {
    case RIGHT_POS_DF:
        this->weeks_info.back().position = RIGHT_POS;
        break;
    case LEFT_POS_DF:
        this->weeks_info.back().position = LEFT_POS;
        break;

    default:
        this->weeks_info.back().position = MID_POS;
        break;
    }
}

void Df::set_score(vector<shared_ptr<Player>> against_composition, int goals_for, int goals_against)
{
    add_score(DEAFAULT_POINT);
    Player::set_score(against_composition, goals_for, goals_against);
    if (goals_against == 0)
        add_score(CLEAN_SHEET_POINT);
    int players_goal = this->weeks_info.back().goal;
    for (auto i = 0; i < players_goal; i++)
        add_score(GOAl_POINT);
    int players_assist = this->weeks_info.back().assist;
    for (auto i = 0; i < players_goal; i++)
        add_score(ASSIST_POINT);
    //calculate special scores
}

int calculate_special_point(vector<shared_ptr<Player>> against_composition)
{
    for (auto player : against_composition)
    {
        if (player->get_role() == DF || player->get_role() == FW)
        {
            if (player->get_pos == )
        }
    }
}
