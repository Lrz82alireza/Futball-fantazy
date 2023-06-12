#pragma once

#include "Team.hpp"
#include "Functions.hpp"
#include <memory>
#include <map>

enum
{
    ARG_MATCH_WEEK,
    ARG_RESULT_WEEK,
    ARG_INJURED_WEEK,
    ARG_YELLOW_CARD_WEEK,
    ARG_RED_CARD_WEEK,
    ARG_GOAL_WITH_ASSIST_WEEK,
    ARG_TEAM_1,
    ARG_TEAM_2,
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
    vector<shared_ptr<Player>> injureds;
    vector<shared_ptr<Player>> yellow_cards;
    vector<shared_ptr<Player>> red_cards;
    vector<pair<shared_ptr<Player>, shared_ptr<Player>>> goal_assist;
    vector<shared_ptr<Player>> composition;
}Team_match;

typedef struct MATCH
{
    pair<shared_ptr<Team_match>, shared_ptr<Team_match>> teams_match;
    pair<int, int> result;

} Match;

typedef struct ARG_MATCH_INPUT
{
    pair<string, string> teams;
    pair<int, int> result;
    vector<string> injured;
    vector<string> yellow_cards;
    vector<string> red_cards;
    vector<pair<string, string>> goal_assist;
    vector<string> team_composition;
} Arg_match_input;

class Week
{
private:
    vector<shared_ptr<Match>> matches;

    Arg_match_input make_Arg_match_input(const vector<vector<string>> &match_input);
    void fill_team_match_field(shared_ptr<Team> team, vector<shared_ptr<Player>> &team_match_field, vector<string> &players_name);
    void fill_team_match_fields(shared_ptr<Team_match> team, Arg_match_input &arg);

    void set_players_score(shared_ptr<Team_match> t1, shared_ptr<Team_match> t2);
public:
    Week(const CSV_input &week_input, vector<shared_ptr<Team>> &teams);

    // accessories
    void update();
    void update_team(shared_ptr<Team_match> team_match, int goals_for_, int goals_against_);
    void update_player(shared_ptr<Team_match> team_match, shared_ptr<Player> player_, pair<int ,int> result);
    
    vector<shared_ptr<Match>> get_matches() { return matches; }

    map<string, shared_ptr<Player_score>> team_of_the_week();
};
