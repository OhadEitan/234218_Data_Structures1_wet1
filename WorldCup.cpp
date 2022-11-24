//
// Created by eitan on 23/11/2022.
//

#include "WorldCup.h"

WorldCup::WorldCup() : wc_teams(nullptr), wc_players(nullptr), wc_pichichi(nullptr),
                       wc_capable(nullptr),wc_total_players(0), wc_pichichi_out(nullptr)
{
    *this->wc_teams = BST<Team>();
    *this->wc_players = BST<Player>();
    *this->wc_pichichi = BST<Player>();
    *this->wc_capable = BST<Team>();
    wc_total_players = 0;
    wc_pichichi_out = nullptr;

}
