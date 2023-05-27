#include "Input.hpp"

void Input::set()
{
    string line;
    getline(cin, line);
    if (line == "")
        return;

    vector<string> temp = seperate_words(line, " ");
    if (temp.size() <= 2)
        throw runtime_error("INVALID_ARGUMENTS");

    command.first = temp[0];
    command.second = temp[1];

    for (vector<string>::size_type i = 2; i < temp.size(); i++)
        value.push_back(temp[i]);
}

void Input::clear()
{
    command.first.clear();
    command.second.clear();
    value.clear();
}
