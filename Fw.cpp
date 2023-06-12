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
