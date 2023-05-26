#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Team.hpp"

using namespace std;

vector<string> seperate_words(const string line, string separate_char);

template <typename T>
T *find_by_name(vector<T *> ts, string name)
{
    auto it = find_if(ts.begin(), ts.end(), [&](T *t)
            { return name == t->get_name(); });

    if (it != ts.end())
        return *it;
    return nullptr;
}