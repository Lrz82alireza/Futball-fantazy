#pragma once

#include <stdexcept>

#include "Functions.hpp"

using namespace std;

class Input
{
public:
    void set();
    void clear();

    bool is_running_() { return is_running; }
    string* command_() { return &command; }
    vector<string>* value_() { return &value; }
private:
    string command;
    vector<string> value;
    bool is_running = true;
};
