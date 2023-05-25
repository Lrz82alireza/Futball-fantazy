#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum
{
    GK = 1,
    DF,
    MD,
    FW
};

class Player
{
private:
    string name;
    int role;

public:
    Player(const int &role_, const string &name_);
    ~Player();
};

Player::~Player()
{
}
