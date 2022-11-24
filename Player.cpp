//
// Created by eitan on 23/11/2022.
//

#include "Player.h"


Player::Player(int p_id, int p_goals, int p_cards, int p_games_played, bool p_goal_keeper)
    : p_id(p_id), p_goals(p_goals), p_cards(p_cards),p_games_played(p_games_played),
      p_goal_keeper(p_goal_keeper)
{
    this->p_pwc_players= nullptr;
    this->p_pwc_pichichi= nullptr;
    this->p_pwc_capable= nullptr;
    this->p_pt_players= nullptr;
    this->p_pt_pichichi= nullptr;
    this->p_pcloset= nullptr;
}
