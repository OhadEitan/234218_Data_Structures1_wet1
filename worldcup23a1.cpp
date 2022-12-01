#include "worldcup23a1.h"

world_cup_t::world_cup_t() : wc_teams(), wc_players(), wc_pichichi(), wc_capable(),
                             wc_pichichi_out(nullptr) ,wc_total_players(0) {}




world_cup_t::~world_cup_t()
{
//    // TODO: Your code goes here
    this->wc_teams.AVLTree<Team, ConTId>::erase_data();
    this->wc_players.AVLTree<Player, ConPId>::erase_data();

}

StatusType world_cup_t::add_team(int teamId, int points)
{
    if (teamId <=0 || points<0)
        return StatusType::INVALID_INPUT;

    Team* t1 =  new Team(teamId,points);
    if (this->wc_teams.search(t1 ) != nullptr)
    {
        return StatusType::FAILURE;
    }
    try
    {
        this->wc_teams.insert(t1);
    }
    catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    // TODO: Your code goes here
    if (teamId <=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team* t2 =  new Team(teamId,0);
    AVLNode<Team>* t1;
    t1 =  this->wc_teams.search(t2);
    if (t1 == nullptr)
    {
        return StatusType::FAILURE;
    }
    if (t1->data->t_total_players >0) // hope this one is ok
    {
        return StatusType::FAILURE;
    }
    try
    {
        this->wc_teams.remove_and_erase(t2);
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if (playerId<=0 || cards< 0 || teamId<=0 || goals<0 || gamesPlayed<0 || (gamesPlayed==0 && (goals>0 || cards>0)))
    {
        return StatusType::INVALID_INPUT;
    }
    Team* t2 =  new Team(teamId,0);
    AVLNode<Team>* t1;
    t1 = this->wc_teams.search(t2);
    if (t1 == nullptr) // team isnt exist
    {
        return StatusType::FAILURE;
    }

    Player *p3 = new Player(playerId, teamId, goals, cards,
                                gamesPlayed - t1->data->t_games_played, goalKeeper);

    AVLNode<Player>* p1;
    p1 = this->wc_players.search(p3);
    if (p1 != nullptr) // player is already exist
    {
        return StatusType::FAILURE;
    }



    /// update for wc
    p3->p_pwc_players = this->wc_players.insert(p3); // adding player to players trees
    /// here should be a bool calc for pichichi
    p3->p_pwc_pichichi = this->wc_pichichi.insert(p3);
    this->wc_total_players++;
    this->wc_pichichi_out = this->wc_pichichi.get_max_node()->data; ///// here find wc pichichi out///


    /// update for the player team
    AVLNode<Team>* specificTeam;
    specificTeam = this->wc_teams.search(t2);
    p3->p_pteam = specificTeam;
    p3->p_pt_players = specificTeam->data->t_players.insert(p3);
    p3->p_pt_pichichi = specificTeam->data->t_pichichi.insert(p3);
    specificTeam->data->t_total_players++;
    specificTeam->data->t_score += (goals-cards);
    if(goalKeeper)
    {
        specificTeam->data->t_gk_counter++;
    }
    specificTeam->data->t_pichichi_out = specificTeam->data->t_pichichi.get_max_node()->data; ///// here find team pichichi out///

    if (specificTeam->data->t_total_players >= 11 && specificTeam->data->t_gk_counter>0)
    {
        specificTeam->data->t_is_capable = true;
        p3->p_pwc_capable = this->wc_capable.insert(specificTeam->data);
    }
    Player *p_left = nullptr;
    Player *p_right = nullptr;
    if (wc_pichichi.get_closest_left(p3) != nullptr) {
        p_left = wc_pichichi.get_closest_left(p3)->data;
    }
    if (wc_pichichi.get_closest_right(p3) != nullptr) {
         p_right = wc_pichichi.get_closest_right(p3)->data;
    }
    p3->p_pcloset_lower = p_left;
    p3->p_pcloset_greater = p_right;
    if (p_left != nullptr)
    {
        p_left->p_pcloset_lower = p_left->p_pcloset_greater;
        p_left->p_pcloset_greater =  p3;
    }
    if (p_right != nullptr)
    {
        p_right->p_pcloset_lower = p3;
        p_right->p_pcloset_greater = p_right->p_pcloset_greater;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    // TODO: Your code goes here
    if (playerId<=0 )
    {
        return StatusType::INVALID_INPUT;
    }
    AVLNode<Player>* p1;
    Player* p2 = new Player(playerId);
    p1 = this->wc_players.search(p2);
    if (p1 == nullptr) // team isnt exist
    {
        return StatusType::FAILURE;
    }
    Player* specific_player = p1->data;
    /// the player is exist !


    try
    {
        //// update closest


        Player *p_left = nullptr;
        Player *p_right = nullptr;
        if (wc_pichichi.get_closest_left(specific_player) != nullptr) {
            p_left = wc_pichichi.get_closest_left(specific_player)->data;
        }
        if (wc_pichichi.get_closest_right(specific_player) != nullptr)
        {
            p_right = wc_pichichi.get_closest_right(specific_player)->data;
        }
        specific_player->p_pcloset_lower = nullptr;
        specific_player->p_pcloset_greater = nullptr;
        if (p_left != nullptr)
        {
            p_left->p_pcloset_lower = p_left->p_pcloset_lower;
            p_left->p_pcloset_greater =  p_right;
        }
        if (p_right != nullptr)
        {
            p_right->p_pcloset_lower = p_left;
            p_right->p_pcloset_greater =  p_right->p_pcloset_greater;
        }
        /// update for the player team
        int player_team = specific_player->p_teamId;
        Team* t2 = new Team(player_team,0);

        AVLNode<Team> *t1 = this->wc_teams.search(t2);
        t1->data->t_total_players--;
        if (specific_player->p_goal_keeper) {
            t1->data->t_gk_counter--;
        }
        if (t1->data->t_total_players < 11 && t1->data->t_gk_counter <= 0) {
            t1->data->t_is_capable = false;
            this->wc_capable.remove(t2);

        }
        t1->data->t_score -= (specific_player->p_goals - p1->data->p_cards);
        t1->data->t_players.remove(specific_player);
        t1->data->t_pichichi.remove(specific_player);
        if (t1->data->t_pichichi.get_max_node() != nullptr) {
            t1->data->t_pichichi_out = t1->data->t_pichichi.get_max_node()->data; ///// here find team pichichi out///
        }


        /// update for wc
        this->wc_pichichi.remove(specific_player);
        this->wc_players.remove(specific_player);
        this->wc_total_players--;

        if (this->wc_pichichi.get_max_node() != nullptr) {
            this->wc_pichichi_out = this->wc_pichichi.get_max_node()->data; ///// here find wc pichichi out///
        }
        /// update closest for player 2 former neighbors


        specific_player->~Player();

    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived)
{
    if (playerId<=0 || scoredGoals< 0 || gamesPlayed<0 || cardsReceived<0)
    {
        return StatusType::INVALID_INPUT;
    }
    AVLNode<Player>* p1;
    Player* p2 = new Player(playerId);
    p1 = this->wc_players.search(p2);
    if (p1 == nullptr) // team isnt exist
    {
        return StatusType::FAILURE;
    }
    /// player exist lets update him
    AVLNode<Team>* t1 = p1->data->p_pteam;
    /// wc closest need to be update before updating the player


    Player *p_left = nullptr;
    Player *p_right = nullptr;
    if (wc_pichichi.get_closest_left(p2) != nullptr) {
        p_left = wc_pichichi.get_closest_left(p2)->data;
    }
    if (wc_pichichi.get_closest_right(p2) != nullptr)
    {
        p_right = wc_pichichi.get_closest_right(p2)->data;
    }
    p2->p_pcloset_lower = nullptr;
    p2->p_pcloset_greater = nullptr;
    if (p_left != nullptr)
    {
        p_left->p_pcloset_lower = p_left->p_pcloset_lower;
        p_left->p_pcloset_greater =  p_right;
    }
    if (p_right != nullptr)
    {
        p_right->p_pcloset_lower = p_left;
        p_right->p_pcloset_greater =  p_right->p_pcloset_greater;
    }



    /// we shold remove both fro, pichichi wc and team
    this->wc_pichichi.remove(p2);
    t1->data->t_pichichi.remove(p2);

    //// update player stats
    p1->data->p_cards += cardsReceived;
    p1->data->p_goals += scoredGoals;
    p1->data->p_games_played += gamesPlayed;
    t1->data->t_score += (scoredGoals -cardsReceived);


    //// add the updated player to pichichis
    this->wc_pichichi.insert(p1->data);
    t1->data->t_pichichi.insert(p1->data);
    /// updating pichichi out
    t1->data->t_pichichi_out = t1->data->t_pichichi.get_max_node()->data;
    this->wc_pichichi_out = this->wc_pichichi.get_max_node()->data;

    /// wc closest need to be update after player stats were update
    p_left = nullptr;
    p_right = nullptr;
    if (wc_pichichi.get_closest_left(p2) != nullptr) {
        p_left = wc_pichichi.get_closest_left(p2)->data;
    }
    if (wc_pichichi.get_closest_right(p2) != nullptr) {
        p_right = wc_pichichi.get_closest_right(p2)->data;
    }
    p2->p_pcloset_lower = p_left;
    p2->p_pcloset_greater = p_right;
    if (p_left != nullptr)
    {
        p_left->p_pcloset_lower = p_left->p_pcloset_greater;
        p_left->p_pcloset_greater =  p2;
    }
    if (p_right != nullptr)
    {
        p_right->p_pcloset_lower = p2;
        p_right->p_pcloset_greater = p_right->p_pcloset_greater;
    }


    /// team pichichi AVL need to be update
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if (teamId1<=0 || teamId2< 0 || teamId1==teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    Team t3 = Team(teamId1,0);
    Team t4 = Team(teamId2,0);
    AVLNode<Team>* t1 = this->wc_teams.search(&t3);
    AVLNode<Team>* t2 = this->wc_teams.search(&t4);
    if (t1 == nullptr || t2 == nullptr ) // team isnt exist
    {
        return StatusType::FAILURE;
    }
    if (!t1->data->t_is_capable || !t2->data->t_is_capable ) // team isnt exist
    {
        return StatusType::FAILURE;
    }
    int t1_tot_points = t1->data->t_score +t1->data->t_points;
    int t2_tot_points = t2->data->t_score +t2->data->t_points;
    if (t1_tot_points > t2_tot_points)
    {
        t1->data->t_points+3;
    }
    else
    {
        if (t2_tot_points > t1_tot_points)
        {
            t2->data->t_points+3;
        }
        else
        {
            t1->data->t_points++;
            t2->data->t_points++;
        }
    }
    t1->data->t_games_played++;
    t2->data->t_games_played++;

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if (playerId<=0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Player p2 = Player(playerId);
    AVLNode<Player>* p1 = this->wc_players.search(&p2);
    if (p1 == nullptr ) // player isnt exist
    {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(p1->data->p_games_played+ p1->data->p_pteam->data->t_games_played);
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if (teamId<=0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Team t2 = Team(teamId,0);
    AVLNode<Team>* t1 = this->wc_teams.search(&t2);
    if (t1 == nullptr) // team isnt exist
    {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(t1->data->t_points);
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if (teamId1<=0 || teamId2<= 0 || teamId1==teamId2 || newTeamId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team t_check = Team(newTeamId,0);
    AVLNode<Team>* node_check = this->wc_teams.search(&t_check);
    if (node_check != nullptr && newTeamId != teamId1 && newTeamId != teamId2 )
    {
        return StatusType::FAILURE;
    }
    Team t3 = Team(teamId1,0);
    Team t4 = Team(teamId2,0);

    AVLNode<Team>* t1 = this->wc_teams.search(&t3);
    AVLNode<Team>* t2 = this->wc_teams.search(&t4);
    if (t1 == nullptr || t2 == nullptr ) // team isnt exist
    {
        return StatusType::FAILURE;
    }
    try {
        // both team players get their gp stats update
        int size_t1 = t1->data->t_total_players;
        Player **pointer_array1_byId = t1->data->t_players.inorder();
        for (int i = 0; i < size_t1; i++) {
            pointer_array1_byId[i]->p_games_played += t1->data->t_games_played;
            pointer_array1_byId[i]->p_teamId = newTeamId;
        }
        int size_t2 = t2->data->t_total_players;
        Player **pointer_array2_byId = t2->data->t_players.inorder();
        for (int i = 0; i < size_t2; i++) {
            pointer_array2_byId[i]->p_games_played += t2->data->t_games_played;
            pointer_array2_byId[i]->p_teamId = newTeamId;

        }
        Team* t5 =  new Team(newTeamId,t1->data->t_points+t2->data->t_points);
        AVLNode<Team> *new_team = this->wc_teams.search(t5);
        if (teamId1 == newTeamId)
        {
             *t5 = Team(newTeamId, t1->data->t_points);
             new_team = t1;
        }
        else
        {
            if (teamId2 == newTeamId) {
                 *t5 = Team(newTeamId, t2->data->t_points);
                 new_team = t2;
            }
        }
        if (new_team == nullptr)
        {
            this->wc_teams.insert(t5);
            new_team = this->wc_teams.search(t5);
        }
        new_team = this->wc_teams.search(t5);
        new_team->data->t_score = t1->data->t_score + t2->data->t_score;
        new_team->data->t_total_players = t1->data->t_total_players + t2->data->t_total_players;
        new_team->data->t_gk_counter = t1->data->t_gk_counter + t2->data->t_gk_counter;
        if (t1->data->t_is_capable || t2->data->t_is_capable) {
            new_team->data->t_is_capable = true;
        }
        /// now we need to merege those two arrays by id
        Player **unite_array_byId = mergeArrays<ConPId>(pointer_array1_byId, pointer_array2_byId, size_t1,size_t2);
        /// now we need to merege those two arrays by pichichi
        Player **pointer_array1_by_pichichi = t1->data->t_pichichi.inorder();
        Player **pointer_array2_by_pichichi = t2->data->t_pichichi.inorder();
        Player **unite_array_by_pichichi = mergeArrays<ConPichichi>(pointer_array1_byId, pointer_array2_byId, size_t1,size_t2);
        /// creating AVLs from sorted array in O(n) like algorithm shown in tutorials
        new_team->data->t_players.build_from_array(unite_array_byId, size_t1+size_t2);
        new_team->data->t_pichichi.build_from_array(unite_array_by_pichichi,size_t1+size_t2);

        if (new_team->data->t_pichichi.get_max_node() != nullptr) {
                new_team->data->t_pichichi_out = new_team->data->t_pichichi.get_max_node()->data;
            }
        new_team->data->t_games_played = 0; /// isnt necessary think constructor will do it need to check this while debugging
        new_team->data->t_points = t1->data->t_points+t2->data->t_points;
        if (new_team->data->t_is_capable) {
            this->wc_capable.insert(new_team->data);
            //// for  eacch player update the pointer to capable team

        }
        if (teamId1 == newTeamId)
        {
            this->wc_teams.remove(&t4);
        }
        else {
            if (teamId2 == newTeamId)
            {
                this->wc_teams.remove(&t3);
            }
            else{
                this->wc_teams.remove(&t3);
                this->wc_teams.remove(&t4);
            }
        }
//        delete pointer_array1_byId;
//        delete pointer_array2_byId;
//        delete pointer_array1_by_pichichi;
//        delete pointer_array2_by_pichichi;
//        delete unite_array_byId;
//        delete unite_array_by_pichichi;

    }


    catch (...)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId) {
    ///havent write anything like allocation error should be changed////
    if (teamId == 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if (teamId>0)
    {
        Team t2 = Team (teamId,0);
        AVLNode<Team>* t1 = this->wc_teams.search(&t2);
        if (t1 == nullptr || t1->data->t_total_players==0)
        {
            return output_t<int>(StatusType::FAILURE);
        }

        return output_t<int>(t1->data->t_pichichi_out->p_id);
    }
    else
    {
        if (this->wc_total_players ==0)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        else
        {
            return output_t<int>(this->wc_pichichi_out->p_id);
        }
    }
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if (teamId==0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if (teamId>0)
    {
        Team t2 = Team (teamId, 0);
        AVLNode<Team>* t1 = this->wc_teams.search(&t2);
        if (t1 == nullptr)
        {

            return output_t<int>(StatusType::FAILURE);
        }
        return output_t<int>(t1->data->t_total_players);
    }
    else
    {
        return output_t<int>(this->wc_total_players);
    }
//    static int i = 0;
//    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output) {
    // TODO: Your code goes here
    if (teamId == 0 || output == nullptr) {
        return StatusType::INVALID_INPUT;
    }
    if (teamId > 0) {
        Team t2 = Team(teamId,0);
        AVLNode<Team> *t1 = this->wc_teams.search(&t2);
        if (t1 == nullptr || t1->data->t_total_players < 1 ) {
            return StatusType::FAILURE;
        }
        try {

            Player **pointer_array = t1->data->t_pichichi.inorder();
            int size = t1->data->t_total_players;



            for (int i = 0; i < size ; ++i) {
                output[i]  = pointer_array[i]->p_id;
            }

            delete[] pointer_array;
            return StatusType::SUCCESS;
        }
        catch (...) {
            return StatusType::FAILURE;
        }

    } else
    {
        try
        {
            Player **pointer_array = wc_pichichi.inorder();
            int size = wc_total_players;
            for (int i = 0; i < size ; ++i) {
                    output[i]  = pointer_array[i]->p_id;
            }
            ///// what should I do here?
            delete[] pointer_array;
            return StatusType::SUCCESS;

            //    output = &player_arr[0];
        }
        catch (...)
        {
            return StatusType::FAILURE;
        }
    }
}



output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if (teamId<=0 || playerId<=0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Player p2 = Player(playerId);
    Team t2 = Team(teamId,0);


    AVLNode<Player>* specif_player = this->wc_teams.search(&t2)->data->t_players.search(&p2);
    if (wc_total_players <=1 || specif_player == nullptr)
    {

        return output_t<int>(StatusType::FAILURE);
    }
    Player* p_lower = specif_player->data->p_pcloset_lower;
    Player* p_greater = specif_player->data->p_pcloset_lower;

    int player_closest = specif_player->data->calc_closest(p_lower,p_greater );
    return output_t<int>(player_closest);
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if (minTeamId < 0 || minTeamId > maxTeamId || maxTeamId<0) {
        return StatusType::INVALID_INPUT;
    }
   Team t2 = Team(minTeamId,0);
   AVLNode<Team> *t1 = this->wc_capable.search(&t2);
   if (t1 == nullptr)
   {
       t1 = this->wc_capable.insert(&t2);
   }

    // TODO: Your code goes here
    return 2;
}



