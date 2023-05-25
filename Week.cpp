#include "Week.hpp"

Arg_match_input Week::make_Arg_match_input(const vector<vector<string>> &match_input)
{
    Arg_match_input arg;
    
    vector<string> teams_ = seperate_words(match_input[ARG_MATCH_WEEK][0], MATCH_SEPERATOR_CHAR); 
    arg.teams.first = teams_[0];
    arg.teams.second = teams_[1];

    vector<string> result_ = seperate_words(match_input[ARG_RESULT_WEEK][0], MATCH_SEPERATOR_CHAR); 
    arg.result.first = stoi(result_[0]);
    arg.result.second = stoi(result_[1]);

    for (auto player_name : match_input[ARG_INJURED_WEEK])
    {
        arg.injured.push_back(player_name);
    }   

    for (auto player_name : match_input[ARG_YELLOW_CARD_WEEK])
    {
        arg.yellow_cards.push_back(player_name);
    }

    for (auto player_name : match_input[ARG_RED_CARD_WEEK])
    {
        arg.red_cards.push_back(player_name);
    }   

    for (auto player_score : match_input[ARG_SCORES_WEEK])
    {
        vector<string> player_score_ = seperate_words(player_score, MATCH_SEPERATOR_CHAR);
        arg.players_score.push_back(pair<string, float> (player_score_[0], stof(player_score_[1])));
    }   
}

Week::Week(const CSS_input &week_input)
{
    for (int i = 0; i < week_input.size(); i++)
    {
        Match *temp = new Match;
        Arg_match_input arg = make_Arg_match_input(week_input[i]);

        temp->result = arg.result;

        // gharare pare sham.......

        matches.push_back(temp);
    }
}