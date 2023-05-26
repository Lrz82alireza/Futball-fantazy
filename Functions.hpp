#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include "Team.hpp"

using namespace std;

vector<string> seperate_words(const string line, string separate_char);

template <typename T>
shared_ptr<T> find_by_name(vector<shared_ptr<T>> ts, string name)
{
    auto it = find_if(ts.begin(), ts.end(), [&](shared_ptr<T> t)
            { return name == t->get_name(); });

    if (it != ts.end())
        return *it;
    return nullptr;
}