/* Author: David
Date: Dec 2024
Description: Functions help to create the maze
*/

#include "Maze.h"
#include <random>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include <utility>
#include <iostream>

// Constructor: dynamically allocate the 2D array for the maze
Maze::Maze(int width, int height) : width(width), height(height)
{
    grid = new int *[height];
    for (int i = 0; i < height; ++i)
    {
        grid[i] = new int[width];
    }

    // Initialize the maze with walls
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            grid[i][j] = 1; // 0 represents a wall
        }
    }
}

// The temporary function is convenient for changing the maze size when needed
Maze Maze::createMazeBySize(int width, int height, int extraPaths)
{
    Maze maze(width, height);             // Create a Maze object with the specified dimensions
    maze.generate();                      // Generate the maze
    maze.addExtraConnections(extraPaths); // Add extra connections based on difficulty
    maze.getStartAndEndPoints();
    return maze; // Return the generated maze
}

// Destructor: free the dynamically allocated memory
Maze::~Maze()
{
    for (int i = 0; i < height; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

// Shuffle the directions randomly
void Maze::shuffleDirections(vector<pair<int, int>> &directions)
{
    for (int i = 0; i < directions.size(); ++i)
    {
        int randomIndex = rand() % directions.size();
        swap(directions[i], directions[randomIndex]);
    }
}

// Entry function to generate the maze
void Maze::generate()
{
    srand(time(0)); // Seed the random number generator with the current time

    // Start generating the maze from (2, 2) to avoid breaking the outer boundary
    generateMaze(2, 2);
}

// Recursive function to generate the maze
void Maze::generateMaze(int x, int y)
{
    grid[y][x] = 2; // Mark the current cell as a path

    // Define 4 directions {dx, dy}
    vector<pair<int, int>> directions =
        {
            {0, -2}, {2, 0}, {0, 2}, {-2, 0}};

    // Shuffle directions randomly
    shuffleDirections(directions);

    for (const auto &dir : directions)
    {
        int nx = x + dir.first;  // Next cell's x-coordinate
        int ny = y + dir.second; // Next cell's y-coordinate

        // Check if the next cell is within bounds and is a wall
        if (nx > 1 && nx < width - 1 && ny > 1 && ny < height - 1 && grid[ny][nx] == 1)
        {
            // Remove the wall between the current cell and the next cell
            grid[y + dir.second / 2][x + dir.first / 2] = 2;
            // Recursively generate the maze from the next cell
            generateMaze(nx, ny);
        }
    }
}

// Get all path coordinates
vector<pair<int, int>> Maze::getEmptyCells()
{
    vector<pair<int, int>> emptyCells;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (grid[i][j] == 2)
            {
                emptyCells.push_back(make_pair(i, j)); // Add path cell to the vector
            }
        }
    }
    // cout << "emptycell size: " << emptyCells.size() << endl;
    return emptyCells;
}

// Create a maze based on difficulty
Maze Maze::createMazeByDifficulty(const string &difficulty)
{
    int width, height, extraPaths;

    if (difficulty == "easy")
    {
        width = 15; // Small size
        height = 15;
        extraPaths = 10; // Extra paths for easy
    }
    else if (difficulty == "medium")
    {
        width = 20; // Medium size
        height = 20;
        extraPaths = 30; // Extra paths for easy
    }
    else if (difficulty == "hard")
    {
        width = 30; // Large size
        height = 30;
        extraPaths = 50; // Extra paths for easy
    }

    Maze maze(width, height);
    maze.generate();
    maze.addExtraConnections(extraPaths); // Add extra connections based on difficulty
    maze.getStartAndEndPoints();
    return maze;
}

int **Maze::getMaze()
{
    return grid;
}

// Select difficulty level
string Maze::selectDifficulty()
{
    string difficulty;

    while (true)
    {
        cout << "Select difficulty (easy, medium, hard): ";
        cin >> difficulty;

        if (difficulty == "easy" || difficulty == "medium" || difficulty == "hard")
        {
            break;
        }
        else
        {
            cout << "Invalid difficulty level. Please enter 'easy', 'medium', or 'hard'.\n";
        }
    }

    return difficulty;
}

// return size of the maze
pair<int, int> Maze::getSize()
{
    return make_pair(this->height, this->width);
}

void Maze::display()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (grid[i][j] == 2)
            {
                // Represent paths with narrow characters
                cout << " ";
            }
            else if (grid[i][j] == 1)
            {
                // Represent walls with continuous wide characters
                cout << "@";
            }
            else if (grid[i][j] == -1)
            {
                // Represent the start point
                cout << "S";
            }
            else if (grid[i][j] == -2)
            {
                // Represent the end point
                cout << "E";
            }
        }
        cout << "\n";
    }
}

void Maze::addExtraConnections(int count)
{
    srand(time(0)); // Random seed
    for (int i = 0; i < count; ++i)
    {
        // Randomly choose a wall
        int x = rand() % width;
        int y = rand() % height;

        // Make sure it is not out of range
        if (x > 1 && x < width - 1 && y > 1 && y < height - 1 && grid[y][x] == 1)
        {
            // Make the wall become round
            grid[y][x] = 2;
        }
    }
}

// Generate random start and end points
vector<pair<int, int>> Maze::getStartAndEndPoints()
{
    pair<int, int> start, end;
    srand(time(0));

    // Generate a random start point
    while (true)
    {
        int x = rand() % width;
        int y = rand() % height;

        if (grid[y][x] == 2)
        {
            start = {x, y};
            //grid[y][x] = -1; // Mark the start cell as -1
            break;
        }
    }

    // Generate a random end point, ensuring it is far from the start and reachable
    while (true)
    {
        int x = rand() % width;
        int y = rand() % height;

        if (grid[y][x] == 2)
        {
            end = {x, y};
            int distance = abs(start.first - end.first) + abs(start.second - end.second);

            if (start != end && distance >= (width + height) / 3) // Ensure the end point is not the same as the start and is sufficiently far away.

            {
                //grid[y][x] = -2; // Mark the end cell as -2
                break;
            }
        }
    }

    return {start, end};
}
