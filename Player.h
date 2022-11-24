//
// Created by eitan on 23/11/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include "BST.h"
#include <memory>

class Team;
class Player {
public:
    int p_id;
    int p_goals;
    int p_cards;
    int p_games_played;
    bool p_goal_keeper;
    <BST<Team>> p_pteam;
    unique_ptr<BST<Team>> p_pwc_players;
    unique_ptr<BST<Team>> p_pwc_pichichi;
    unique_ptr<BST<Team,int>> p_pwc_capable;
    unique_ptr<BST<Player,int>> p_pt_players;
    unique_ptr<BST<Player,int>> p_pt_pichichi;
    unique_ptr<Player> p_pcloset;

    Player(int p_id, int p_goals, int p_cards,  int p_games_played,bool p_goal_keeper);
    ~Player();

};




#endif //WET1_PLAYER_H
