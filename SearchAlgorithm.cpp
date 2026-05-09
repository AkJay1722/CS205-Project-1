#include "SearchAlgorithm.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> // For reverse

using namespace std;

SearchAlgorithm::SearchAlgorithm() {
    max_queueSize = 0;
    nodes_expanded = 0;
}

SearchAlgorithm::~SearchAlgorithm() {
    cleanup();
}

// Delete all node pointers
void SearchAlgorithm::cleanup() {
    for (Node* node : all_nodes) {
        delete node;
    }
    all_nodes.clear();
}

// Generates a child node given a parent node and operand
Node* SearchAlgorithm::child_node(Node* parent, Operand operand, Puzzle* problem, int heuristic_type) {
    Node* child = new Node(operand.new_puzzle);
    child->parent = parent;
    // Set costs
    child->g = parent->g + 1; // g(n) = parent's g(n) + 1
    child->h = problem->heuristic_value(child->puzzle, heuristic_type); // h(n)
    child->f = child->g + child->h; // f(n) = g(n) + h(n)

    return child;
}

// Prints the solution path and statistics about the search
void SearchAlgorithm::print_solution_path(Node* goal_node) {
    stack<Node*> path; 
    Node* curr = goal_node;

    while (curr != nullptr) {
        path.push(curr);
        curr = curr->parent;
    }

    cout << "\n[[Goal!]]\n" << endl;
    cout << "Solution Path:" << endl;
    int depth = path.size() - 1;

    while (!path.empty()) {
        Node* node = path.top();
        path.pop();
        if (node->parent != nullptr) {
             cout << "Expanding node..." << endl; // shows expansion
        } else {
             cout << "Initial state:" << endl;
        }
        node->print_state();
        cout << endl;
    }

    // Print final statistics
    cout << "Overall, the search algorithm expanded a total of " << nodes_expanded << " nodes." << endl;
    cout << "The max amount of nodes queued at any time was " << max_queueSize << "." << endl;
    cout << "The goal node's depth is " << depth << "." << endl;
}

// Main function implementing A* search algorithm
void SearchAlgorithm::solve(Puzzle* problem, int heuristic_type) {
    // Initialize root node with initial stte
    int init_puzzle[3][3];
    problem->get_init_state(init_puzzle);
    Node* root = new Node(init_puzzle);

    // Calculate initial heuristic costs
    root->g = 0; // g(n)
    root->h = problem->heuristic_value(root->puzzle, heuristic_type); // h(n)
    root->f = root->g + root->h; // f(n)

    // Add root to frontier and explored list 
    frontier.push(root);
    all_nodes.push_back(root); // memory cleanup
    explored[root->get_state()] = true;
    max_queueSize = 1;

    // Begin search loop
    while (!frontier.empty()) {
        // Pop from priority queue
        Node* current_node = frontier.top();
        frontier.pop();

        // Check for goal state
        if (problem->is_goal_state(current_node->puzzle)) {
            print_solution_path(current_node);
            return;
        }

        nodes_expanded++;
        // Expand chosen node
        vector<Operand> operands = problem->get_operands(current_node);

        for (const Operand& op : operands) {
            Node* child = child_node(current_node, op, problem, heuristic_type);
            string child_state = child->get_state();

            // Add to priority queue only if not in explored set
            if (explored.find(child_state) == explored.end()) {
                explored[child_state] = true;
                frontier.push(child);
                all_nodes.push_back(child); // For memory cleanup

                // Update max queue size
                if (frontier.size() > max_queueSize) {
                    max_queueSize = frontier.size();
                }
            } else {
                // If already explored, delete the child for memory cleanup
                delete child;
            }
        }
    }

    // No solution found since the p-queue is empty
    cout << "Failure: No solution found." << endl;
    cout << "To solve this problem the search algorithm expanded a total of " << nodes_expanded << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time was " << max_queueSize << "." << endl;
}