#include "Player.hpp"

float Player::get_avg_scores()
{
    float avg = 0.0;
    int counter = 0;

    for (auto i : weeks_info)
    {
        if (i.score != 0.0)
        {
            counter++;
            avg += i.score;
        }
    }
    return avg / counter;
}

Player::Player(const int &role_, const string &name_)
{
    this->role = role_;
    this->name = name_;
}

string role_to_s(int role)
{
    if (role == GK)
        return "gk";
    if (role == MD)
        return "md";
    if (role == DF)
        return "df";
    if (role == FW)
        return "fw";
    return NULL;
}
