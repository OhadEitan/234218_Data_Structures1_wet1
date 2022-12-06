#include "assert.h"
#include "wet1util.h"
#include "worldcup23a1.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void query_get_all_players(string cmd, world_cup_t *obj, int teamID);

// Helpers
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print(string cmd, StatusType res) {
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res) {
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_players(string cmd, world_cup_t *obj, int teamID)
{
    output_t<int> count = obj->get_all_players_count(teamID);
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS && (count.ans() > 0)) {
        out_mem = new int[count.ans()];
        for (int i = 0; i < count.ans(); ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_players(teamID, out_mem);
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < count.ans(); ++i) {
            cout << out_mem[i] << endl;
        }
    }
    delete[] out_mem;
}


#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>



int main()
{


    // Yonatan Leibovich Tests
    try {
        world_cup_t worldCup;
        StatusType sResult;
        if (sResult == StatusType::FAILURE) {}

        sResult = worldCup.add_team(10, 1);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(2, 0);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(3, 4);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(9, 1);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(4, 1);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(8, 3);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(6, 3);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(7, 2);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(1, 3);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(5, 3);
        assert(sResult == StatusType::SUCCESS);


        sResult = worldCup.add_player(1, 5, 3, 3, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(2, 6, 2, 4, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(3, 6, 3, 2, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(4, 6, 4, 2, 2, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(5, 4, 1, 0, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(6, 9, 3, 1, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(7, 1, 3, 1, 3, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(8, 8, 2, 1, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(9, 8, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(10, 8, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(11, 10, 4, 3, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(12, 10, 2, 4, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(13, 10, 0, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(14, 8, 2, 1, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(15, 6, 0, 2, 3, false);
        assert(sResult == StatusType::INVALID_INPUT);
        sResult = worldCup.add_player(15, 6, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(16, 2, 4, 2, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(17, 7, 0, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(18, 3, 1, 1, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(19, 2, 3, 2, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(20, 2, 4, 4, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(21, 5, 1, 3, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(22, 7, 4, 0, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(23, 6, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(24, 2, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(25, 9, 2, 1, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(26, 9, 4, 0, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(27, 5, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(28, 9, 1, 2, 1, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(29, 7, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(30, 7, 3, 3, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(31, 7, 2, 2, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(32, 7, 4, 1, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(33, 6, 2, 2, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(34, 2, 4, 3, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(35, 8, 3, 3, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(36, 9, 3, 0, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(37, 1, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(38, 3, 4, 4, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(39, 5, 2, 1, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(40, 10, 4, 4, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(41, 10, 1, 1, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(42, 6, 3, 1, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(43, 7, 1, 0, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(44, 1, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(45, 1, 4, 3, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(46, 7, 1, 1, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(47, 9, 1, 2, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(48, 7, 1, 0, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(49, 4, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(50, 3, 0, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(51, 2, 3, 4, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(52, 2, 2, 4, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(53, 5, 4, 4, 2, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(54, 5, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(55, 8, 3, 2, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(56, 7, 4, 4, 2, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(57, 10, 2, 1, 1, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(58, 3, 4, 4, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(59, 8, 2, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(60, 8, 2, 3, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(61, 2, 1, 3, 2, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(62, 3, 2, 1, 3, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(63, 8, 2, 4, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(64, 1, 2, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(65, 7, 1, 2, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(66, 2, 1, 1, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(67, 2, 2, 4, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(68, 4, 4, 1, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(69, 6, 3, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(70, 7, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(71, 8, 3, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(72, 6, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(73, 7, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(74, 10, 2, 0, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(75, 8, 3, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(76, 1, 2, 1, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(77, 7, 3, 0, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(78, 1, 2, 2, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(79, 10, 4, 0, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(80, 5, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(81, 2, 1, 0, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(82, 9, 4, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(83, 7, 10, 15, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(83, 7, 10, 15, 0, true);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.add_player(84, 10, 3, 0, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(85, 7, 4, 3, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(86, 6, 4, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(87, 3, 4, 0, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(88, 10, 4, 1, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(89, 6, 2, 3, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(90, 9, 2, 10, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(91, 4, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(92, 3, 1, 0, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(93, 7, 1, 1, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(94, 6, 4, 3, 3, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(95, 4, 1, 3, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(96, 4, 3, 4, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(97, 4, 2, 3, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(98, 3, 0, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(99, 5, 3, 0, 1, false);
        assert(sResult == StatusType::SUCCESS);

        assert(worldCup.get_top_scorer(-1).ans() == 83);
        assert(worldCup.get_top_scorer(7).ans() == 83);
        worldCup.update_player_stats(22, 5, 40, 3);
        assert(worldCup.get_top_scorer(-1).ans() == 22);
        assert(worldCup.get_top_scorer(7).ans() == 22);
        assert(worldCup.get_top_scorer(9).ans() == 90);
        assert(worldCup.get_closest_player(98, 3).ans() == 91);
        assert(worldCup.get_closest_player(49, 4).ans() == 50);
        worldCup.unite_teams(1, 9, 19);
        sResult = worldCup.remove_team(1);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_team(9);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_team(19);
        assert(sResult == StatusType::FAILURE);
        worldCup.knockout_winner(2, 20).ans(); //Only 2, 6, 7 and 19 are competing
        worldCup.play_match(2, 19);
        worldCup.unite_teams(2, 7, 2);
        assert(worldCup.get_num_played_games(16).ans() == 5);

        // Remove team 6
        sResult = worldCup.remove_player(2);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(3);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(4);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(15);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(23);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(33);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(42);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(69);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(72);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(86);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(89);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(94);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::SUCCESS);
        cout << "Test run successfully" << endl;
    } catch(...){
        return -1;
    }

       // Staff tests
          cin >> std::boolalpha;

          int d1, d2, d3, d4, d5;
          bool b1;

          // Init
          world_cup_t *obj = new world_cup_t();

          // Execute all commands in file
          string op;
          while (cin >> op) {
              if (!op.compare("add_team")) {
                  cin >> d1 >> d2;
                  print(op, obj->add_team(d1, d2));
              } else if (!op.compare("remove_team")) {
                  cin >> d1;
                  print(op, obj->remove_team(d1));
              } else if (!op.compare("add_player")) {
                  cin >> d1 >> d2 >> d3 >> d4 >> d5 >> b1;
                  print(op, obj->add_player(d1, d2, d3, d4, d5, b1));
              } else if (!op.compare("remove_player")) {
                  cin >> d1;
                  print(op, obj->remove_player(d1));
              } else if (!op.compare("update_player_stats")) {
                  cin >> d1 >> d2 >> d3 >> d4;
                  print(op, obj->update_player_stats(d1, d2, d3, d4));
              } else if (!op.compare("play_match")) {
                  cin >> d1 >> d2;
                  print(op, obj->play_match(d1, d2));
              } else if (!op.compare("get_num_played_games")) {
                  cin >> d1;
                  print(op, obj->get_num_played_games(d1));
              } else if (!op.compare("get_team_points")) {
                  cin >> d1;
                  print(op, obj->get_team_points(d1));
              } else if (!op.compare("unite_teams")) {
                  cin >> d1 >> d2 >> d3;
                  print(op, obj->unite_teams(d1, d2, d3));
              } else if (!op.compare("get_top_scorer")) {
                  cin >> d1;
                  print(op, obj->get_top_scorer(d1));
              } else if (!op.compare("get_all_players_count")) {
                  cin >> d1;
                  print(op, obj->get_all_players_count(d1));
              } else if (!op.compare("get_all_players")) {
                  cin >> d1;
                  query_get_all_players(op, obj, d1);
              } else if (!op.compare("get_closest_player")) {
                  cin >> d1 >> d2;
                  print(op, obj->get_closest_player(d1, d2));
              } else if (!op.compare("knockout_winner")) {
                  cin >> d1 >> d2;
                  print(op, obj->knockout_winner(d1, d2));
              } else {
                  cout << "Unknown command: " << op << endl;
                  return -1;
              }
              // Verify no faults
              if (cin.fail()) {
                  cout << "Invalid input format" << endl;
                  return -1;
              }
          }
          // Quit
          delete obj;


    // Liran tests
    cin >> std::boolalpha;

    // int d1, d2, d3, d4, d5;
    // bool b1;

    // Init
    world_cup_t *obj1 = new world_cup_t();

    // Execute all commands in file
    //string op;
    print("get top scorer expected invalid", obj1->get_top_scorer(0));
    print("get top scorer expected fail", obj1->get_top_scorer(2));
    print("get top scorer expected fail", obj1->get_top_scorer(-1));
    print("add team 0, points 2 expected invalid", obj1->add_team(0, 2));
    print("add team -1, points -2 expected invalid", obj1->add_team(-1, -2));
    print("add team 2, points -2 expected invalid", obj1->add_team(2, -2));
    print("add team 1, points 2 expected success", obj1->add_team(1, 2));
    print("get top scorer expected fail", obj1->get_top_scorer(1));
    int arr[7];
    print("get all players  for all teams expected FAIL ", obj1->get_all_players(1, arr));
    print("add team 1, points -2 expected invalid", obj1->add_team(1, -2));
    print("add team 1, player 1 expected success", obj1->add_player(1, 1, 2, 3, 4, false));
    print("add team 1, player 2 expected success", obj1->add_player(2, 1, 2, 3, 5, false));
    print("add team 1, player 3 expected success", obj1->add_player(3, 1, 2, 3, 4, false));
    print("add team 1, player 4 expected success", obj1->add_player(4, 1, 2, 3, 5, false));
    print("add team 1, player 5 expected success", obj1->add_player(5, 1, 2, 4, 5, false));
    print("add team 2, points 0 expected success", obj1->add_team(2, 0));
    print("add team 2, points 1 expected fail", obj1->add_team(2, 1));
    print("add team 2, player 6 expected success", obj1->add_player(6, 2, 2, 3, 1, true));
    print("add team 2, player 7 expected success", obj1->add_player(7, 2, 2, 3, 5, false));
    print("add team 3, player 7 expected fail", obj1->add_player(7, 3, 5, 7, 3, false));
    print("add team 1, player 7 expected fail", obj1->add_player(7, 1, 4, 3, 8, false));
    print("add team 1, player 0 expected invalid", obj1->add_player(0, 1, 4, 3, 8, false));
    print("add team 1, player -1 expected invalid", obj1->add_player(-1, 1, 4, 3, 8, false));
    print("add team 0, player 9 expected invalid", obj1->add_player(9, 0, 4, 3, 8, false));
    print("add team -1, player 7 expected invalid", obj1->add_player(9, -1, 4, 3, 8, false));
    print("add team 1, player 7 expected invalid", obj1->add_player(7, -1, 4, 3, 8, false));
    print("add team 0, player 7 expected invalid", obj1->add_player(7, 0, 4, 3, 8, false));
    print("add team 2, player 8 expected success", obj1->add_player(8, 2, 0, 0, 0, false));
    print("add team 2, player 8 expected invalid", obj1->add_player(8, 2, 1, -1, 0, false));
    print("add team 2, player 9 expected invalid", obj1->add_player(9, 2, 1, -1, 0, false));
    print("add team 2, player 8 expected invalid", obj1->add_player(8, 2, 1, 0, -1, false));
    print("add team 2, player 9 expected invalid", obj1->add_player(9, 2, 1, 0, -1, false));
    print("add team 2, player 8 expected invalid", obj1->add_player(8, 2, 0, 1, 0, false));
    print("add team 2, player 9 expected invalid", obj1->add_player(9, 2, 0, 1, 0, false));
    print("add team 2, player 8 expected invalid", obj1->add_player(8, 2, 0, 0, 1, false));
    print("add team 2, player 9 expected invalid", obj1->add_player(9, 2, 0, 0, 1, false));
    print("add team 0, player 7 expected invalid", obj1->add_player(8, 2, -1, 0, 0, false));
    print("add team 0, player 7 expected fail", obj1->add_player(8, 1, 4, 3, 8, false));
    print("add team 0, player 7 expected fail", obj1->add_player(9, 5, 2, 3, 8, false));
    print("remove player 0, team 0 expected invalid", obj1->remove_player(0));
    print("remove player -1, team 0 expected invalid", obj1->remove_player(-1));
    print("remove player 9, team 0 expected fail", obj1->remove_player(9));
    print("remove player 8, team 2 expected success", obj1->remove_player(8));
    print("get top scorer expected success 5", obj1->get_top_scorer(1));
    print("get top scorer expected success 6", obj1->get_top_scorer(2));
    print("get top scorer expected invalid", obj1->get_top_scorer(0));
    print("get top scorer expected success 5", obj1->get_top_scorer(-1));
    print("remove player 5, team 1 expected success", obj1->remove_player(5));
    print("remove player 6, team 2 expected success", obj1->remove_player(6));
    print("get top scorer expected success 3", obj1->get_top_scorer(1));
    print("get top scorer expected success 7", obj1->get_top_scorer(2));
    print("get top scorer expected success 3", obj1->get_top_scorer(-1));
    print("remove player 7, team 2 expected success", obj1->remove_player(7));
    print("get top scorer expected fail ", obj1->get_top_scorer(2));
    print("add team 2, player 7 expected success", obj1->add_player(7, 2, 2, 3, 5, false));
    print("get top scorer expected invalid", obj1->get_top_scorer(0));
    print("add team 1, player 5 expected success", obj1->add_player(5, 1, 2, 4, 5, false));
    print("add team 2, player 6 expected success", obj1->add_player(6, 2, 2, 3, 1, true));
    print("get all players count for team 1 expected success 5", obj1->get_all_players_count(1));
    print("get all players count for team 2 expected success 2", obj1->get_all_players_count(2));
    print("get all players count for all teams expected success 7", obj1->get_all_players_count(-1));
    print("get all players count expected invalid", obj1->get_all_players_count(0));
    print("get all players count for all teams expected success 7", obj1->get_all_players_count(-5));
    print("get all players count expected fail", obj1->get_all_players_count(5));
    print("get_team1_points expected success 2", obj1->get_team_points(1));
    print("get_team2_points expected success 0", obj1->get_team_points(2));
    print("expected invalid input ", obj1->get_team_points(0));
    print(" expected invalid input", obj1->get_team_points(-1));
    print("get all players  for team 1 expected success 2, 4, 1, 3, 5", obj1->get_all_players(1, arr));
    for (int i=0; i< 5;i++) {
        cout << arr[i] << ", " ;
    }
    cout << endl;
    print("get all players  for team 2 expected success 7, 6", obj1->get_all_players(2, arr));
    for (int i=0; i< 2;i++) {
        cout << arr[i] << ", " ;
    }
    cout << endl;
    print("get all players  for all teams expected success 2, 4, 7, 1, 3, 6, 5", obj1->get_all_players(-1, arr));
    for (int i=0; i< 7;i++) {
        cout << arr[i] << ", " ;
    }
    print("get all players  for team 1 expected invalid input ", obj1->get_all_players(1, NULL));
    print("get all players  for team 2 expected invalid input ", obj1->get_all_players(2, NULL));
    print("get all players  for team -1 expected invalid input ", obj1->get_all_players(-1, NULL));
    print("get all players  for all teams expected FAIL", obj1->get_all_players(5, arr));
    print("remove player 6, team 2 expected success", obj1->remove_player(6));
    print("remove team 2 expected fail", obj1->remove_team(2));
    print("remove player 7, team 2 expected success", obj1->remove_player(7));
    print("remove player 8, team 2 expected fail", obj1->remove_player(8));
    print("remove team 2 expected success", obj1->remove_team(2));
    print("remove team 0 expected invalid", obj1->remove_team(0));
    print("remove team -1 expected invalid", obj1->remove_team(-1));
    print("remove team 3 expected fail", obj1->remove_team(3));
    print("get_team2_points team 2 was removed expected fail", obj1->get_team_points(2));
    print("add team 2, points 0 expected success", obj1->add_team(2, 1));
    print("add team 2, player 6 expected success", obj1->add_player(6, 2, 2, 3, 1, true));
    print("add team 2, player 7 expected success", obj1->add_player(7, 2, 2, 3, 5, false));
    print("add team 2, player 8 expected success", obj1->add_player(8, 2, 2, 1, 0, false));
    print("unite team1 and team 2 expected success", obj1->unite_teams(1, 2, 3));
    print(" team1 and team 2 expected success points 3", obj1->get_team_points(3));
    print(" team1 and team 2 expected success players 8", obj1->get_all_players_count(3));
    print("remove player 8, team 3 expected success", obj1->remove_player(8));
    print("unite team3 and team 2 expected invalid", obj1->unite_teams(3, 3, 5));
    print("unite team3 and team 2 expected invalid", obj1->unite_teams(0, 3, 5));
    print("unite team3 and team 2 expected invalid", obj1->unite_teams(-1, 3, 5));
    print("unite team3 and team 2 expected invalid", obj1->unite_teams(3, 0, 5));
    print("unite team3 and team 2 expected invalid", obj1->unite_teams(3, -1, 5));
    print("unite team3 and team 2 expected invalid", obj1->unite_teams(3, 1, 0));
    print("unite team3 and team 2 expected invalid", obj1->unite_teams(3, 1, -1));
    print("unite team3 and team 2 expected fail", obj1->unite_teams(3, 2, 4));
    print("unite team3 and team 2 expected fail", obj1->unite_teams(2, 3, 4));
    print("add team 2, points 1 expected success", obj1->add_team(2, 1));
    print("add team 4, points 0 expected success", obj1->add_team(4, 5));
    print("unite team3 and team 2 expected fail", obj1->unite_teams(2, 3, 4));
    print("unite team4 and team 2 expected success", obj1->unite_teams(2, 4, 2));
    print(" team1 and team 2 expected success points 6", obj1->get_team_points(2));
    print("get all players count for team 1 expected fail", obj1->get_all_players_count(1));
    print("get all players count for team 2 expected success 0", obj1->get_all_players_count(2));
    print("get all players count for team 3 expected 7", obj1->get_all_players_count(3));
    print("get all players count for all teams expected 7", obj1->get_all_players_count(-1));
    print("get top scorer expected fail", obj1->get_top_scorer(2));
    print("get top scorer expected success 5", obj1->get_top_scorer(-1));
    print("get all players  for team 1 expected fail", obj1->get_all_players(1, arr));
    print("get all players  for team 3 expected 2, 4, 7, 1, 3, 6, 5", obj1->get_all_players(3, arr));
    for (int i=0; i< 7;i++) {
        cout << arr[i] << ", " ;
    }
    cout << endl;
    print("get all players  for all teams expected 2, 4, 7, 1, 3, 6, 5", obj1->get_all_players(-1, arr));
    for (int i=0; i< 7;i++) {
        cout << arr[i] << ", " ;
    }
    delete obj1;

}
