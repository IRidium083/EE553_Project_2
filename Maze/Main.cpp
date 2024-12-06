#include "Maze.h"
#include "Maze.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
    // 使用 Maze 類中的靜態函數選擇難度
    string difficulty = Maze::selectDifficulty();

    // 根據難度生成迷宮
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