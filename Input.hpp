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
    shared_ptr<string> command_() { return (shared_ptr<string>)&command; }
    shared_ptr<vector<string>> value_() { return (shared_ptr<vector<string>>)&value; }
private:
    string command;
    vector<string> value;
    bool is_running = true;
};
