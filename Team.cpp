//
// Created by eitan on 23/11/2022.
//

#include "Team.h"


Team::Team(int teamId, int points) : t_players(), t_pichichi(), p_twc_list_capable(nullptr),  team_id(teamId), t_total_players(0), t_score(0), t_points(points),
                                     t_games_played(0), t_pichichi_out(nullptr), t_gk_counter(0), t_is_capable(false) {}

Team::Team() : t_players(), t_pichichi(), p_twc_list_capable(nullptr),  team_id(0), t_total_players(0), t_score(0), t_points(0),
               t_games_played(0), t_pichichi_out(nullptr), t_gk_counter(0), t_is_capable(false) {}