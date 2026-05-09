#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Node.h"
using namespace std;

// Represents one possible move from the current state, contains state and move type
struct Operand {
    int new_puzzle[3][3];
    string move_name;
};

// This class contains all metadata for a given puzzle: initial, goal, and heuristic logic
class Puzzle {
    public:
        Puzzle(int initial_puzzle[3][3]);
        void get_init_state(int puzzle[3][3]); // Copies initial state to the puzzle array
        bool is_goal_state(int board[3][3]) const; // Checks if the current state is the goal state
        vector<Operand> get_operands(Node* node); // Retrieves all possible operands for next move from 'node
        int heuristic_value(int board[3][3], int heuristic_type); // Finds h(n)
    private:
        int initial_state[3][3];
        int goal_state[3][3] = { {1,2,3}, {4,5,6}, {7,8,0} };
        int calc_misplaced_tiles(int board[3][3]);
        int calc_manhattan_dist(int board[3][3]);
        map<int, pair<int, int>> goal_coordinates;
};

#endif