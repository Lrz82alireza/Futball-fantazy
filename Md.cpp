#include "Md.hpp"

Md::Md(int &role, string &name)
    : Player(role, name)
{
}

void Md::set_position(int pos)
{
    switch (pos)
    {
    case RIGHT_POS_MD:
        this->weeks_info.back().position = RIGHT_POS;
        break;
    case LEFT_POS_MD:
        this->weeks_info.back().position = LEFT_POS;
        break;

    default:
        this->weeks_info.back().position = MID_POS;
        break;
    }
}

void Md::set_score(vector<shared_ptr<Player>> against_composition, int goals_for, int goals_against)
{
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
}

void Md::demerit_score(vector<shared_ptr<Player>> against_composition, int pos)
{
    for (int i = 0; i < against_composition[pos]->get_week_info().goal; i++)
        add_score(DEMERIT_POINT);
}

void Md::set_special_point(vector<shared_ptr<Player>> against_composition)
{
    enum
    {
        LEFT_MD = 5,
        MID_MD,
        RIGHT_MD
    };
    demerit_score(against_composition , LEFT_MD);
    demerit_score(against_composition , MID_MD);
    demerit_score(against_composition , RIGHT_MD);
}