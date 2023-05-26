#pragma once

#include "Team.hpp"
#include "Functions.hpp"
#include <memory>

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

typedef vector<vector<vector<string>>> CSV_input;

typedef struct PLAYER_SCORE
{
    shared_ptr<Player> player;
    float score;

    PLAYER_SCORE(shared_ptr<Player> player_, float score_)
    {
        player = player_;
        score = score_;
    }
} Player_score;

typedef struct TEAM_MATCH
{
    shared_ptr<Team> team;
    int goals;
    vector<shared_ptr<const Player>> injureds;
    vector<shared_ptr<const Player>> yellow_cards;
    vector<shared_ptr<const Player>> red_cards;
    vector<shared_ptr<const Player_score>> players_score;
}Team_match;

typedef struct MATCH
{
    pair<Team_match, Team_match> teams_match;
    pair<int, int> result;
} Match;

typedef struct ARG_MATCH_INPUT
{
    pair<string, string> teams;
    pair<int, int> result;
    vector<string> injured;
    vector<string> yellow_cards;
    vector<string> red_cards;
    vector<pair<string, float>> players_score;
} Arg_match_input;

class Week
{
private:
    vector<shared_ptr<Match>> matches;

    Arg_match_input make_Arg_match_input(const vector<vector<string>> &match_input);
    void fill_team_match_field(shared_ptr<Team> team, vector<shared_ptr<const Player>> &team_match_field, vector<string> &players_name);
    void fill_team_match_fields(shared_ptr<Team_match> team, Arg_match_input &arg);
public:
    Week(const CSV_input &week_input, vector<shared_ptr<Team>> &teams);
};
