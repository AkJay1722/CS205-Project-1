#include "Node.h"
#include <iostream>

using namespace std;


// Constructor for Node class
Node::Node(int init_puzzle[3][3]) { // takes a 3x3 puzzle array
    for (int i = 0; i < 3; i++) { // for each ith row
        for (int j = 0; j < 3; j++) { // for each jth column
            puzzle[i][j] = init_puzzle[i][j]; // copy value from input to puzzle
            // Check if this spot is the blank (0)
            if (puzzle[i][j] == 0) { // if value is 0
                blank_row = i; // save row of blank
                blank_col = j; // save column of blank
            }
        }
    }
    g = 0; // cost so far 
    h = 0; // heuristic
    f = 0; // total cost (g+h)
    parent = nullptr; // no parent node yet
}


// Returns the puzzle as a string
string Node::get_state() const {
    string state = ""; // make empty string
    for (int i = 0; i < 3; ++i) { // for each row
        for (int j = 0; j < 3; ++j) { // for each column
            state += to_string(puzzle[i][j]); // add number to string
        }
    }
    return state; // return the string
}


// Prints the puzzle to the CLI
void Node::print_state() const {
    //printing the puzzle string states
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (puzzle[i][j] == 0) {
                cout << "* "; // print * for blank 
            } else {
                cout << puzzle[i][j] << " "; // print the number
            }
        }
        cout << endl; // new line after each row
    }
}