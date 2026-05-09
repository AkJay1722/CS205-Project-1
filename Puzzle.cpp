#include "Puzzle.h"
#include <cmath>

// Sets up initial state and goal coordinates for Manhattan and Euclidean
Puzzle::Puzzle(int initial_puzzle[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            initial_state[i][j] = initial_puzzle[i][j];
            goal_coordinates[goal_state[i][j]] = {i, j};
        }
    }
}

// Copying initial state to the output
void Puzzle::get_init_state(int puzzle[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            puzzle[i][j] = initial_state[i][j];
        }
    }
}

bool Puzzle::is_goal_state(int board[3][3]) const{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != goal_state[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Get all possible moves we can perform on the current state
vector<Operand> Puzzle::get_operands(Node* node) {
    vector<Operand> operands;
    int row_moves[] = {-1, 1, 0, 0}; // Up, Down
    int col_moves[] = {0, 0, -1, 1}; // Left, Right
    string moves[] = {"UP", "DOWN", "LEFT", "RIGHT"};
    const int NUM_DIRECTIONS = 4;

    int blank_row = node->blank_row; 
    int blank_col = node->blank_col;
    for (int i = 0; i < NUM_DIRECTIONS; i++) {
        int new_row = blank_row + row_moves[i];
        int new_col = blank_col + col_moves[i];

        // Check if the new position is within the 3x3 grid
        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            // If it's valid, make a new operand
            Operand op;
            op.move_name = moves[i];
            for(int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    op.new_puzzle[r][c] = node->puzzle[r][c]; // copy the parent's puzzle state

                }
            }

            op.new_puzzle[blank_row][blank_col] = op.new_puzzle[new_row][new_col]; // Swap blank with the adjacent tile
            op.new_puzzle[new_row][new_col] = 0;

            operands.push_back(op); // add the new valid move to the list
        }
    }
    return operands;
}

//calculates the heuristic value based on the selected heuristic type
int Puzzle::heuristic_value(int board[3][3], int heuristic_type) {
    if (heuristic_type == 2) { // misplaced tiles heuristic
        return calc_misplaced_tiles(board);
    } else if (heuristic_type == 3) { // euclidean distance heuristic
        return calc_euclidean_dist(board);
    }
    return 0;
}

//calculates the misplaced tiles heuristic for the board
int Puzzle::calc_misplaced_tiles(int board[3][3]) {
    int misplaced_sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0 && board[i][j] != goal_state[i][j]) { //if the config isn't empty and config isn't in the goal state
                misplaced_sum++; //increment misplaced tile count
            }
        }
    }
    return misplaced_sum;
}

//calculates the euclidean distance heuristic for the board
int Puzzle::calc_euclidean_dist(int board[3][3]) {
    double total_distance = 0.0;
    int current_tileVal = 0;
    
    // iterate through each tile in the board
    for (int i = 0; i < 3; i++) { //for each row
        for (int j = 0; j < 3; j++) { //for each column
            current_tileVal = board[i][j];
            if (current_tileVal != 0) { //skip blank tile
                // get coordinates where this tile *should* be
                pair<int, int> goal_position = goal_coordinates[current_tileVal];
                int goal_row = goal_position.first;  // use .first of tuple
                int goal_col = goal_position.second; // use .second of tuple

                // calculate euclidean distance, add to total
                total_distance += sqrt(pow(i - goal_row, 2) + pow(j - goal_col, 2));
            }
        }
    }
    // Return the value h(n)
    return static_cast<int>(round(total_distance)); 
}