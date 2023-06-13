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

int Player::get_goals()
{
    int sum = 0;
    for (auto i : weeks_info)
    {
        sum += i.goal;
    }
    return sum;
}

int Player::get_assists()
{
    int sum = 0;
    for (auto i : weeks_info)
    {
        sum += i.assist;
    }
    return sum;
}

int Player::get_clean_sheets()
{
    int sum = 0;
    for (auto i : weeks_info)
    {
        sum += i.clean_sheet;
    }
    return sum;
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

bool Player::is_clean_sheet()
{
    return true;
}

void Player::set_position(int pos)
{
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

void Player::set_score(vector<shared_ptr<Player>> against_composition , int goals_for , int goals_against)
{
    if (goals_for > goals_against)
        this->add_score(WIN_POINT);
    else if (goals_for < goals_against)
        this->add_score(LOSE_POINT);
    else
        this->add_score(EQUAL_POINT);
    if (this->get_week_info().own_goal != 0)
        this->add_score(OWN_GOAL);
}

void Player::score_algorithm()
{
    float score = weeks_info.back().score;
    float exponent = -(score / 6);
    float denominator = 1 + exp(exponent);
    float result = (1 / denominator) * 10;
    result = round(result * 10.0) / 10.0;
    weeks_info.back().score = result;
}