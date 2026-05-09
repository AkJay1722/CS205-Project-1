#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <vector>
using namespace std;

// This class represents one state, storing the cost and path to reach that state.
class Node {
    public: 
        Node(int init_puzzle[3][3]);
        int puzzle[3][3];
        int g; // Cost from start to current
        int h; // Estimated cost from current to goal
        int f; // g + h
        int blank_row, blank_col; // Position of the blank tile (0)
        Node* parent; // Points to parent node

        string get_state() const; // Returns puzzle states as a string
        void print_state() const; // Prints the puzzle state
};

#endif