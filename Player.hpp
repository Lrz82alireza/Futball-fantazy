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
    int get_role() {return role;};
    Week_info get_week_info() {return weeks_info.back();}
    void new_week(Week_info &new_info) { weeks_info.push_back(new_info); }
    float get_avg_scores();

    Player(const int &role_, const string &name_);

private:
    string name;
    int role;

    vector<Week_info> weeks_info;
};

string role_to_s(int role);