//
// Created by eitan on 23/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "BST.h"
#include <memory>

using std::unique_ptr<T>;
class Player;

class Team {
public:
    unique_ptr<BST<Player,int>> t_players;
    unique_ptr<BST<Player,int>> t_pichichi;
    Team team_id;
    int t_total_players;
    int t_score;
    int t_points;
    int t_games_played;
    unique_ptr<Player> t_pichichi_out;
    int t_gk_counter;
    bool t_is_capable;

    Team(int teamId,int points);


};


#endif //WET1_TEAM_H
