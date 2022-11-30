//
// Created by eitan on 23/11/2022.
//

#include "Player.h"
#include "math.h"


Player::Player(int p_id,int p_teamId, int p_goals, int p_cards, int p_games_played, bool p_goal_keeper)
    : p_id(p_id),p_teamId(p_teamId), p_goals(p_goals), p_cards(p_cards),p_games_played(p_games_played),
      p_goal_keeper(p_goal_keeper)
{
    this->p_pteam = nullptr;
    this->p_pwc_players= nullptr;
    this->p_pwc_pichichi= nullptr;
    this->p_pwc_capable= nullptr;
    this->p_pt_players= nullptr;
    this->p_pt_pichichi= nullptr;
    this->p_pcloset_greater = nullptr;
    this->p_pcloset_lower = nullptr;

}

Player::Player(int p_id): p_id(p_id),p_teamId(0), p_goals(0),
    p_cards(0),p_games_played(0),p_goal_keeper(0), p_pteam(nullptr),
                          p_pwc_players(nullptr), p_pwc_pichichi(nullptr),
                          p_pwc_capable(nullptr), p_pt_players(nullptr),
                          p_pt_pichichi(nullptr),p_pcloset_greater(nullptr),
                          p_pcloset_lower(nullptr){}


int getClosest(int val1, int val2,int target)
{
    if (target - val1 > val2 - target)
        return val2;
    else
        return val1;

}

int Player::calc_closest(Player*& p1, Player*& p2) {
    if (this->p_goals- p1->p_goals < p2->p_goals-this->p_goals)
    {
        return  p1->p_id;
    }
    else
    {
        if (this->p_goals- p1->p_goals > p2->p_goals-this->p_goals)
        {
            return  p2->p_id;
        }
        else
        {
            if (this->p_cards- p1->p_cards < p2->p_cards-this->p_cards)
            {
                return  p1->p_id;
            }
            else
            {
                if (this->p_cards- p1->p_cards > p2->p_cards-this->p_cards)
                {
                    return  p2->p_id;
                }
                else
                {
                    if (this->p_id- p1->p_id < p2->p_id-this->p_id)
                    {
                        return p1->p_id;
                    }
                    return p2->p_id;
                }
            }
        }
    }
}

