#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum
{
    GK,
    DF,
    MD,
    FW
};

class Player
{
private:
    string name;
    vector<float> score_in_week;
    int role;
public:
    Player(/* args */);
    ~Player();
};

Player::Player(/* args */)
{
}

Player::~Player()
{
}
