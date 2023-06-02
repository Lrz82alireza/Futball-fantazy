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
    struct Week_info
    {
        float score = 0;
        bool injured = false;
        bool yellow_card = false;
        bool red_card = false;
    };

private:
    string name;
    int role;

    vector<Week_info> weeks_info;

public:
    string get_name() { return this->name; }
    Player(const int &role_, const string &name_);
};
