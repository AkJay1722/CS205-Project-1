#include "Node.h"
#include "Puzzle.h"
#include "SearchAlgorithm.h"
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    cout << "8-puzzle solver with different heuristics" << endl;
    cout << "Enter '1' for the default puzzle or '2' to enter your own: ";
    int start_option; cin >> start_option;
    while (start_option != 1 && start_option != 2) {
        cout << "Invalid puzzle choice. Please try again:" << endl;
        cin >> start_option;
    }
    start_option = static_cast<int>(start_option);
    int myPuzzle[3][3];

    if (start_option == 1) { // Default puzzle
        int default_puzzle[3][3] = { {1, 2, 3}, {4, 5, 0}, {7, 8, 6} };
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                myPuzzle[i][j] = default_puzzle[i][j];
            }
        }
    }
    else if (start_option == 2) { // Custom puzzle
        cout << "Enter numbers 1-8 and use a zero to represent the blank. Enter them row by row, with spaces between numbers:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Enter row " << (i+1) << " (use space or tabs between numbers): ";
            cin >> myPuzzle[i][0] >> myPuzzle[i][1] >> myPuzzle[i][2];
        }
    }

    cout << "Enter the desired algorithm or heuristic:" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile heuristic" << endl;
    cout << "3. A* with the Manhattan Distance heuristic" << endl;
    int algorithm_choice;
    cin >> algorithm_choice;

    Puzzle* problem = new Puzzle(myPuzzle);
    SearchAlgorithm search;
    cout << endl << "Solving puzzle..." << endl;

    if (algorithm_choice == 1) { // Uniform Cost Search (1)
        search.solve(problem, 1);
    }
    else if (algorithm_choice == 2) { // A* with Misplaced Tile (2)
        search.solve(problem, 2);
    }
    else if (algorithm_choice == 3) { // A* with Manhattan Distance (3)
        search.solve(problem, 3);
    }

    delete problem; // Clean up dynamically allocated memory
    return 0;
}