#ifndef _SEARCHALGORITHM_H_
#define _SEARCHALGORITHM_H_

#include "Puzzle.h"
#include <queue>
#include <map>
#include <vector>
using namespace std;

// A struct to compare nodes based on total cost for priority queue
struct NodeComparison {
    bool operator()(const Node* first, const Node* second) const {
        return (first->f) > (second->f); // Priority_queue is max-heap by default, so I inverted the comparison to get a min-heap
    }
};

// This class contains the algorithms/heuristics for searching through states
class SearchAlgorithm {
    public:
        SearchAlgorithm();
        ~SearchAlgorithm();
        void solve(Puzzle* problem, int heuristic_type);
    private:
        priority_queue<Node*, vector<Node*>, NodeComparison> frontier; // Organizes nodes to be explored based on total cost
        map<string, bool> explored; // Previously explored states
        vector<Node*> all_nodes; // Keeps track of all created nodes for memory cleanup
        int max_queueSize = 0;
        int nodes_expanded = 0;
        void cleanup(); // Helper function to clean up memory
        void print_solution_path(Node* Node); // Prints final solution
        Node* child_node(Node* parent, Operand operand, Puzzle* problem, int heuristic_type); // Generates child nodes
};

#endif