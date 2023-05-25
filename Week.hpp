#pragma once

#include "Team.hpp"

typedef struct MATCH_
{
    pair<const Team *, const Team *> team;
    pair<int, int> goal;
}MATCH;


class Week
{
private:
    MATCH match;
public:
    Week(/* args */);
    ~Week();
};

Week::Week(/* args */)
{
}

Week::~Week()
{
}
