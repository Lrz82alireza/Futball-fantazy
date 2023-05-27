#pragma once

#include <stdexcept>

#include "Functions.hpp"
#include <memory>

using namespace std;

class Input
{
public:
    void set();
    void clear();

    bool is_running_() { return is_running; }
    pair<string, string> command_() { return command; }
    vector<string> value_() { return value; }
private:
    pair<string, string> command;
    vector<string> value;
    bool is_running = true;
};
