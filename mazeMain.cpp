#include "Maze/Maze.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
    string difficulty = Maze::selectDifficulty();
    
    // Chose how difiicult the maze is
    Maze maze = Maze::createMazeByDifficulty(difficulty); 
    maze.display(); 
    vector<pair<int, int>> emptyCells = maze.getEmptyCells();

    cout << "All path coordinates:\n";
    for (const auto& cell : emptyCells) 
    {
        cout << "(" << cell.first << ", " << cell.second << ")\n";
    }

    return 0;
}