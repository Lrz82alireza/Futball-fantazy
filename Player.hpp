#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Functions.hpp"

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
        bool clean_sheet = false;
        int goal = 0;
        int assist = 0;
        int own_goal = 0;
        int position = 0;
    };

    float get_price() { return this->price; }
    float get_score(int week_num) { return weeks_info[week_num].score; }
    string get_name() { return this->name; }
    int get_role() {return role;};
    Week_info get_week_info() {return weeks_info.back();}
    void new_week(Week_info &new_info);
    float get_avg_scores();
    bool is_available() { return available; }
    int get_goals();
    int get_assists();
    int get_clean_sheets();

    float scores_sum();

    void set_availability();
    virtual bool is_clean_sheet();
    virtual void set_position(int pos);


    Player(const int &role_, const string &name_);

protected:
    enum
    {
        NAME,
        PRICE,
    };
    enum
    {
        RIGHT_POS,
        MID_POS,
        LEFT_POS,
    };

    string name;
    int role;
    bool available = true;
    int counter_yellow_card = 0;
    float price = 0;

    vector<Week_info> weeks_info;
};

string role_to_s(int role);