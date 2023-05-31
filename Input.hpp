#pragma once

#include <stdexcept>

#include "Functions.hpp"
#include <memory>
#include <fstream>
#include <sstream>

using namespace std;

typedef vector<vector<vector<string>>> CSV_input;

class Input
{
public:

    Input() {init_csv_data();};
    void set();
    void init_csv_data();
    void clear();

    bool is_running_() { return is_running; }
    pair<string, string> command_() { return command; }
    vector<string> value_() { return value; }
    shared_ptr<CSV_input> read_info_from_scv(string file_name);

private:
    pair<string, string> command;
    vector<string> value;
    shared_ptr<CSV_input> league;
    vector<shared_ptr<CSV_input>> weeks;
    bool is_running = true;
};
