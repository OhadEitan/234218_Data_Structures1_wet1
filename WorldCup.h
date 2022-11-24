//
// Created by eitan on 23/11/2022.
//

#ifndef WET1_WORLDCUP_H
#define WET1_WORLDCUP_H
#include "BST.h"
#include "Player.h"
#include "Team.h"
#include "StatusType.h"
#include <memory>
using std::unique_ptr;


class world_cup_t {
public:



    world_cup_t();
    virtual ~world_cup_t();
    StatusType add_team(int teamId,int points);
    StatusType remove_team(int teamId);
    StatusType add_player(int playerId,int teamId,int gamesPlayed,int goals,int cards,bool goalKeeper);
    StatusType remove_player(int playerId);
    StatusType update_player_stats(int playerId,int gamesPlayed,int scoredGoals,int cardsReceived);
    StatusType play_match(int teamId1,int teamId2);
    output_t<int> get_num_played_games(int playerId);
};


#endif //WET1_WORLDCUP_H
