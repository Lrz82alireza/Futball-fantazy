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
    for (auto i = 0; i < players_assist; i++)
        add_score(ASSIST_POINT);
    set_special_point(against_composition);
    this->score_algorithm();
}

void Df::demerit_score(vector<shared_ptr<Player>> against_composition, int pos)
{
    for (int i = 0; i < against_composition[pos]->get_week_info().goal; i++)
        add_score(DEMERIT_POINT);
}

void Df::set_special_point(vector<shared_ptr<Player>> against_composition)
{
    enum
    {
        LEFT_DF = 1,
        LEFT_MID_DF,
        RIGHT_MID_DF,
        RIGHT_DF,
        LEFT_FW = 8,
        MID_FW,
        RIGHT_FW,
    };

    int pos = this->get_pos();
    switch (pos)
    {
    case LEFT_POS:
    {
        demerit_score(against_composition, RIGHT_FW);
        demerit_score(against_composition, RIGHT_DF);
        break;
    }
    case RIGHT_POS:
    {
        demerit_score(against_composition, LEFT_FW);
        demerit_score(against_composition, LEFT_DF);
        break;
    }
    case MID_POS:
    {
        demerit_score(against_composition, LEFT_MID_DF);
        demerit_score(against_composition, RIGHT_MID_DF);
        demerit_score(against_composition, MID_FW);
        break;
    }
    }
}
