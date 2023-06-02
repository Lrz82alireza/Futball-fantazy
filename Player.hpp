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

public:
    struct Week_info
    {
        float score = 0;
        bool injured = false;
        bool yellow_card = false;
        bool red_card = false;
    };

    string get_name() { return this->name; }
    void new_week(Week_info &new_info) { weeks_info.push_back(new_info); }

    Player(const int &role_, const string &name_);

private:
    string name;
    int role;

    vector<Week_info> weeks_info;
};
