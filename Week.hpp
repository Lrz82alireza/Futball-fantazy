#pragma once

#include "Team.hpp"
#include "Functions.hpp"

enum
{
    ARG_MATCH_WEEK,
    ARG_RESULT_WEEK,
    ARG_INJURED_WEEK,
    ARG_YELLOW_CARD_WEEK,
    ARG_RED_CARD_WEEK,
    ARG_SCORES_WEEK
};

const string MATCH_SEPERATOR_CHAR = ":";

typedef vector<vector<vector<string>>> CSS_input;

typedef struct MATCH_
{
    pair<Team *,Team *> team;
    pair<int, int> goal;
}MATCH;

typedef struct ARG_MATCH_INPUT
{
    pair<string, string> teams;
    pair<int, int> result;
    vector<string> injured;
    vector<string> yellow_cards;
    vector<string> red_cards;
    vector<pair<string, float>> players_score;
}Arg_MATCH_input;


class Week
{
private:
    vector<MATCH *> matches;
public:
    Arg_MATCH_input make_Arg_week_input(const vector<vector<string>> &match_input);

    Week(const CSS_input &week_input);
    ~Week();
};

Week::~Week()
{
}
