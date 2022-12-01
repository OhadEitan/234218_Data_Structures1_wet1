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

template<class condition>
Player** mergeArrays(Player* array1[], Player* array2[], int size1, int size2)
{
    if (array1 == nullptr || array2 == nullptr || size1 < 1 || size2 < 1)
    {
        return nullptr;
    }
    int i=0, j=0, k=0, t=0;
    Player** united_array = new Player*[size1 + size2];
    for (t=0; t<(size1+size2); t++)
    {
        united_array[t] = nullptr;
    }
    condition cond;
    while (i < size1 && j < size2)
    {
        if (cond(array1[i], array2[j]) == Comparison::LESS_THAN)
        {
            united_array[k++] = array1[i++];
        }
        else
        {
            united_array[k++] = array2[j++];
        }
    }
    while (i < size1)
    {
        united_array[k++] = array1[i++];
    }
    while (j < size2)
    {
        united_array[k++] = array2[j++];
    }
    return united_array;
}

class ConPId{
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


class ConPichichi{
public:
    Comparison operator()(Player* a, Player* b)
    {
        if (a->p_goals < b->p_goals)
        {
            return Comparison::LESS_THAN;
        }
        if (a->p_goals > b->p_goals)
        {
            return Comparison::GREATER_THAN;
        }
        if (a->p_cards < b->p_cards)
        {
            return Comparison::GREATER_THAN;

        }
        if (a->p_cards > b->p_cards)
        {
            return Comparison::LESS_THAN;
        }
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
