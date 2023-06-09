#pragma once

#include <stdexcept>

#include "Functions.hpp"
#include <memory>
#include <fstream>
#include <sstream>

using namespace std;

const string LEAGUE = "./data/premier_league.csv";
const string WEEKS_ADDRESS = "./data/weeks_stats/week_";

typedef vector<vector<vector<string>>> CSV_input;

class Input
{
public:
    Input() { init_csv_data(); };
    bool set();
    void init_csv_data();
    void clear();

    bool is_running_() { return is_running; }
    pair<string, string> &command_() { return command; }
    vector<string> &value_() { return value; }

    const CSV_input & get_league() {return *league;}
    const vector<shared_ptr<CSV_input>> & get_weeks() {return weeks;}

private:
    pair<string, string> command;
    vector<string> value;
    shared_ptr<CSV_input> league;
    vector<shared_ptr<CSV_input>> weeks;

    shared_ptr<CSV_input> read_info_from_csv(string file_name);
    bool is_running = true;
};
