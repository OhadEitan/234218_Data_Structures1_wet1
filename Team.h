//
// Created by eitan on 23/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "Player.h"
#include "AVLTree.h"
#pragma once

#include <memory>



class Team {
public:
    AVLTree<Player, ConPId > t_players; // this one belong to him
    AVLTree<Player, ConPichichi > t_pichichi; // this one belong to him
    int team_id;
    int t_total_players;
    int t_score;
    int t_points;
    int t_games_played;
    Player* t_pichichi_out;
    int t_gk_counter;
    bool t_is_capable;

    Team(int teamId,int points);
    ~Team() = default;


};

class ConTId {
public:
    Comparison operator()(Team* a, Team* b)
    {
        if (a->team_id < b->team_id)
        {
            return Comparison::LESS_THAN;
        }
        if (a->team_id > b->team_id)
        {
            return Comparison::GREATER_THAN;
        }
        return Comparison::EQUAL;
    }
};

#endif //WET1_TEAM_H
