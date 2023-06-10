#include "Player.hpp"

void Player::new_week(Week_info &new_info)
{
    if (!this->available && counter_yellow_card == 3)
        counter_yellow_card = 0;

    if (new_info.yellow_card)
        this->counter_yellow_card++;

    weeks_info.push_back(new_info);
}

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
    if (counter == 0)
        counter = 1;
    return avg / counter;
}

float Player::scores_sum()
{
    float sum = 0;
    for (auto i : weeks_info)
    {
        sum += i.score;
    }
    return sum;
}

void Player::set_availability()
{
    if (weeks_info.back().red_card)
    {
        this->available = false;
        return;
    }

    for (vector<Player::Week_info>::size_type i = weeks_info.size() - 1; weeks_info.size() - 4 < i && i > 0; i--)
    {
        if (weeks_info[i].injured)
        {
            this->available = false;
            return;
        }
    }

    if (counter_yellow_card == 3)
    {
        this->available = false;
        return;
    }

    this->available = true;
}

Player::Player(const int &role_, const string &name_and_price)
{
    this->role = role_;
    vector<string> player_ = seperate_words(name_and_price, ":");

    this->name = player_[NAME];
    this->price = stof(player_[PRICE].substr(0, player_[PRICE].size() - 1));
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
