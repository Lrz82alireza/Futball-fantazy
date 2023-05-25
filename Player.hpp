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

typedef struct PERFORMANCE
{
    bool injured;
    bool yellow_card;
    bool red_card;
    float score;
} Performance;

class Player
{
private:
    string name;
    vector<Performance> week_performance;
    int role;

public:
    Player(const int &role_, const string &name_);
    ~Player();
};

Player::~Player()
{
}
