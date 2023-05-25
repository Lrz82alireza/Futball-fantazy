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

typedef struct PLAYER_SCORE
{
    const Player *player;
    float score;
}Player_score;

typedef struct MATCH
{
    pair<Team *,Team *> team;
    pair<int, int> result;
    pair <vector<const Player *>, vector<const Player *>> injureds;
    pair <vector<const Player *>, vector<const Player *>> yellow_cards;
    pair <vector<const Player *>, vector<const Player *>> red_cards;
    pair <vector<const Player *>, vector<const Player *>> players_score; 
}Match;

typedef struct ARG_MATCH_INPUT
{
    pair<string, string> teams;
    pair<int, int> result;
    vector<string> injured;
    vector<string> yellow_cards;
    vector<string> red_cards;
    vector<pair<string, float>> players_score;
}Arg_match_input;


class Week
{
private:
    vector<Match *> matches;

    Arg_match_input make_Arg_match_input(const vector<vector<string>> &match_input);
public:

    Week(const CSS_input &week_input);
    ~Week();
};

Week::~Week()
{
}
