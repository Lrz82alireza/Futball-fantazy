#include "Gk.hpp"

Gk::Gk(int &role, string &name)
    : Player(role, name)
{
}

void Gk::set_position(int pos)
{
    this->weeks_info.back().position = POS;
}
