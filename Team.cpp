//
// Created by eitan on 23/11/2022.
//

#include "Team.h"


Team::Team(int teamId, int points) : t_players(), t_pichichi(),  team_id(teamId), t_points(points), t_total_players(0),
t_games_played(0), t_gk_counter(0), t_score(0),p_twc_list_capable(nullptr), t_is_capable(false), t_pichichi_out(nullptr) {}


