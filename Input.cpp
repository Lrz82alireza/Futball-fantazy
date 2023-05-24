#include "Input.hpp"

void Input::set()
{
    string line;
    getline(cin, line);
    if (line == "")
        return;

    vector<string> temp = seperate_words(line, " ");
    if (temp.size() == 1)
        throw runtime_error("INVALID_ARGUMENTS");

    command = temp[0];

    for (vector<string>::size_type i = 1; i < temp.size(); i++)
        value.push_back(temp[i]);
}

void Input::clear()
{
    command.clear();
    value.clear();
}
