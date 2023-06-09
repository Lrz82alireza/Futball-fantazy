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

    for (auto goal_assist : match_input[ARG_GOAL_WITH_ASSIST_WEEK])
    {
        vector<string> goal_assist_ = seperate_words(goal_assist, MATCH_SEPERATOR_CHAR);
        if (goal_assist_.size() != 2)
            continue;
        arg.goal_assist.push_back(pair<string, string>(goal_assist_[0], goal_assist_[1]));
    }

    arg.team_composition.insert(arg.team_composition.end(), match_input[ARG_TEAM_1].begin(), match_input[ARG_TEAM_1].end());
    arg.team_composition.insert(arg.team_composition.end(), match_input[ARG_TEAM_2].begin(), match_input[ARG_TEAM_2].end());

    return arg;
}

void Week::fill_team_match_field(shared_ptr<Team> team, vector<shared_ptr<Player>> &team_match_field, vector<string> &players_name)
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
    fill_team_match_field(team_match->team, team_match->composition, arg.team_composition);
    for (auto i : arg.goal_assist)
    {
        pair<shared_ptr<Player>, shared_ptr<Player>> goal_assist;
        goal_assist.first = team_match->team->find_player(i.first);
        goal_assist.second = team_match->team->find_player(i.second);

        team_match->goal_assist.push_back(goal_assist);
    }
}

// public

Week::Week(const CSV_input &week_input, vector<shared_ptr<Team>> &teams)
{
    for (CSV_input::size_type i = 0; i < week_input.size(); i++)
    {
        shared_ptr<Match> temp_match(new Match);
        Arg_match_input arg = make_Arg_match_input(week_input[i]);

        temp_match->teams_match.first = make_shared<Team_match>();
        temp_match->teams_match.second = make_shared<Team_match>();

        temp_match->result = arg.result;
        temp_match->teams_match.first->goals = arg.result.first;
        temp_match->teams_match.second->goals = arg.result.second;

        temp_match->teams_match.first->team = find_by_name<Team>(teams, arg.teams.first);
        temp_match->teams_match.second->team = find_by_name<Team>(teams, arg.teams.second);

        fill_team_match_fields(temp_match->teams_match.first, arg);
        fill_team_match_fields(temp_match->teams_match.second, arg);

        matches.push_back(temp_match);
    }
}

void Week::update_team(shared_ptr<Team_match> team_match, int goals_for_, int goals_against_)
{
    vector<shared_ptr<Player>> team_players = team_match->team->get_players();

    for (auto i : team_players)
    {
        update_player(team_match, i, pair<int, int>(goals_for_, goals_against_));
    }

    Team::Week_info team_week_info;

    if (goals_for_ > goals_against_)
        team_week_info.score = WIN_POINT;
    if (goals_for_ == goals_against_)
        team_week_info.score = EQUAL_POINT;
    if (goals_for_ < goals_against_)
        team_week_info.score = LOSE_POINT;

    team_week_info.goals_for = goals_for_;
    team_week_info.goals_against = goals_against_;

    team_match->team->new_week(team_week_info);
}

void Week::update_player(shared_ptr<Team_match> team_match, shared_ptr<Player> player_, pair<int, int> result)
{
    Player::Week_info player_week_info;
    if (result.second == 0)
        if (find(team_match->composition.begin(), team_match->composition.end(), player_) != team_match->composition.end())
            player_week_info.clean_sheet = player_->is_clean_sheet();

    if (find(team_match->injureds.begin(), team_match->injureds.end(), player_) != team_match->injureds.end())
        player_week_info.injured = true;

    if (find(team_match->yellow_cards.begin(), team_match->yellow_cards.end(), player_) != team_match->yellow_cards.end())
        player_week_info.yellow_card = true;

    if (find(team_match->red_cards.begin(), team_match->red_cards.end(), player_) != team_match->red_cards.end())
        player_week_info.red_card = true;

    for (auto i : team_match->goal_assist)
    {
        if (i.second == nullptr)
            player_week_info.own_goal++;
        else if (i.first == player_)
            player_week_info.goal++;
        else if (i.second == player_)
            player_week_info.assist++;
    }

    player_->new_week(player_week_info);

    for (vector<shared_ptr<Player>>::size_type i = 0; i < team_match->composition.size(); i++)
    {
        if (team_match->composition[i] == player_)
            player_->set_position(i);
    }
}

void Week::update_players_score(vector<shared_ptr<Player>> team_composition, vector<shared_ptr<Player>> against_composition, pair<int, int> match_result)
{
    for (auto i : team_composition)
    {
        i->set_score(against_composition, match_result.first, match_result.second);
    }
}

void Week::update()
{
    for (auto i : matches)
    {
        update_team(i->teams_match.first, i->result.first, i->result.second);
        update_team(i->teams_match.second, i->result.second, i->result.first);
    }

    for (auto i : matches)
    {
        update_players_score(i->teams_match.first->composition, i->teams_match.second->composition, i->result);
        update_players_score(i->teams_match.second->composition, i->teams_match.first->composition,
                             pair<int, int>(i->result.second, i->result.first));
    }
}

shared_ptr<Player> find_best_player_by_role(vector<shared_ptr<Player>> &players, int role)
{
    shared_ptr<Player> target_player = nullptr;
    float most_score = 0;
    for (vector<shared_ptr<Player>>::size_type i = 0; i < players.size(); i++)
    {
        if (players[i]->get_role() == role)
        {
            if (players[i]->get_week_info().score >= most_score)
            {
                most_score = players[i]->get_week_info().score;
                target_player = players[i];
            }
        }
    }
    for (vector<shared_ptr<PLAYER_SCORE>>::size_type i = 0; i < players.size(); i++)
        if (players[i] == target_player)
            players.erase(players.begin() + i);

    return target_player;
}

map<string, shared_ptr<Player>> Week::team_of_the_week()
{
    map<string, shared_ptr<Player>> tmp;
    vector<shared_ptr<Player>> players;

    for (auto x : matches)
    {
        players.insert(players.end(), x->teams_match.first->composition.begin(), x->teams_match.first->composition.end());
        players.insert(players.end(), x->teams_match.second->composition.begin(), x->teams_match.second->composition.end());
    }
    tmp["GK"] = find_best_player_by_role(players, GK);
    tmp["DF1"] = find_best_player_by_role(players, DF);
    tmp["DF2"] = find_best_player_by_role(players, DF);
    tmp["MD"] = find_best_player_by_role(players, MD);
    tmp["FW"] = find_best_player_by_role(players, FW);
    return tmp;
}

// accessories