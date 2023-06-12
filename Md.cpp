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
