//
// Created by eitan on 23/11/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include "AVLTree.h"

class Team;

class Player {
public:
    int p_id;
    int p_teamId;
    int p_goals;
    int p_cards;
    int p_games_played;
    bool p_goal_keeper;
    AVLNode<Team>* p_pteam;
    AVLNode<Player>* p_pwc_players;
    AVLNode<Player>* p_pwc_pichichi;
    AVLNode<Team>* p_pwc_capable;
    AVLNode<Player>* p_pt_players;
    AVLNode<Player>* p_pt_pichichi;
    Player* p_pcloset_greater;
    Player* p_pcloset_lower;


    Player(int p_id, int p_teamId, int p_goals, int p_cards,  int p_games_played,bool p_goal_keeper);
    Player() =default;
    Player(int p_id);
    int calc_closest(Player*& p1, Player*& p2);
    ~Player() = default;

};

class ConPId {
public:
    Comparison operator()(Player* a, Player* b)
    {
            if (a->p_id < b->p_id)
            {
                return Comparison::LESS_THAN;
            }
        if (a->p_id > b->p_id)
        {
            return Comparison::GREATER_THAN;
        }
        return Comparison::EQUAL;
    }
};




#endif //WET1_PLAYER_H
