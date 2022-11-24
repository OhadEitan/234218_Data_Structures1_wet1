//
// Created by eitan on 23/11/2022.
//

#include "Team.h"

Team::Team(int teamId, int points) : team_id(teamId), t_points(points)
{
    *this->t_players = BST<Player,int>();
    *this->t_pichichi = BST<Player,int>();
    this->t_total_players = 0;
    this->t_points = 0;
    this->t_games_played = 0 ;
    this->t_pichichi_out = nullptr;
    this->t_gk_counter = 0;
    this->t_is_capable = false;
}

