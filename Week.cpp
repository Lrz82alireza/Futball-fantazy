#include "Week.hpp"

// private

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
        arg.players_score.push_back(pair<string, float>(player_score_[0], stof(player_score_[1])));
    }

    return arg;
}

void Week::fill_team_match_field(shared_ptr<Team> team, vector<shared_ptr<const Player>> &team_match_field, vector<string> &players_name)
{
    for_each(players_name.begin(), players_name.end(), [&](string player_name)
             {
        shared_ptr<Player> temp_player = team->find_player(player_name);
        if (temp_player != nullptr)
            team_match_field.push_back(temp_player); });
}

void Week::fill_team_match_fields(shared_ptr<Team_match> team_match, Arg_match_input &arg)
{
    fill_team_match_field(team_match->team, team_match->injureds, arg.injured);
    fill_team_match_field(team_match->team, team_match->yellow_cards, arg.yellow_cards);
    fill_team_match_field(team_match->team, team_match->red_cards, arg.red_cards);
    for_each(arg.players_score.begin(), arg.players_score.end(),
             [&](pair<string, float> player_score_) {
                shared_ptr<Player> temp_player = team_match->team->find_player(player_score_.first);
                if (temp_player != nullptr)
                {
                    shared_ptr<Player_score> temp (new Player_score(temp_player, player_score_.second));
                    team_match->players_score.push_back(temp);
                }
             });
}

// public

Week::Week(const CSV_input &week_input, vector<shared_ptr<Team>> &teams)
{
    for (CSV_input::size_type i = 0; i < week_input.size(); i++)
    {
        shared_ptr<Match> temp_match (new Match);
        Arg_match_input arg = make_Arg_match_input(week_input[i]);

        temp_match->result = arg.result;
        temp_match->teams_match.first.goals = arg.result.first;
        temp_match->teams_match.second.goals = arg.result.second;

        temp_match->teams_match.first.team = find_by_name<Team>(teams, arg.teams.first);
        temp_match->teams_match.second.team = find_by_name<Team>(teams, arg.teams.second);

        fill_team_match_fields((shared_ptr<Team_match>)&temp_match->teams_match.first, arg);
        fill_team_match_fields((shared_ptr<Team_match>)&temp_match->teams_match.second, arg);

        matches.push_back(temp_match);
    }
}