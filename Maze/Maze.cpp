#include "Maze.h"
#include <random>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

// Constructor: dynamically allocate the 2D array for the maze
Maze::Maze(int width, int height) : width(width), height(height) 
{
    cout << test;
    grid = new int*[height];
    for (int i = 0; i < height; ++i) 
    {
        grid[i] = new int[width];
    }

    // Initialize the maze with walls
    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width; ++j) 
        {
            grid[i][j] = 0; // 0 represents a wall
        }
    }
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
void Maze::shuffleDirections(vector<pair<int, int>>& directions) 
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
    grid[y][x] = 1; // Mark the current cell as a path

    // Define 4 directions {dx, dy}
    vector<pair<int, int>> directions = 
    {
        {0, -2}, {2, 0}, {0, 2}, {-2, 0}
    };

    // Shuffle directions randomly
    shuffleDirections(directions);

    for (const auto& dir : directions) 
    {
        int nx = x + dir.first;  // Next cell's x-coordinate
        int ny = y + dir.second; // Next cell's y-coordinate

        // Check if the next cell is within bounds and is a wall
        if (nx > 1 && nx < width - 1 && ny > 1 && ny < height - 1 && grid[ny][nx] == 0) 
        {
            // Remove the wall between the current cell and the next cell
            grid[y + dir.second / 2][x + dir.first / 2] = 1;
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
            if (grid[i][j] == 1) 
            {
                emptyCells.push_back(make_pair(i,j)); // Add path cell to the vector
            }
        }
    }
    cout<<"emptycell size: "<<emptyCells.size()<<endl;
    return emptyCells;
}


// Create a maze based on difficulty
Maze Maze::createMazeByDifficulty(const string& difficulty) 
{
    int width, height;

    if (difficulty == "easy") 
    {
        width = 15;  // Small size
        height = 15;
    } 
    else if (difficulty == "medium") 
    {
        width = 25;  // Medium size
        height = 25;
    } 
    else if (difficulty == "hard") 
    {
        width = 35;  // Large size
        height = 35;
    } 

    Maze maze(width, height);
    maze.generate();
    return maze;
}

int** Maze::getMaze()
{
    return grid;
}

// Select difficulty level
string Maze::selectDifficulty() 
{
    string difficulty;

    while (true) {
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

//return size of the maze
pair<int,int> Maze::getSize(){
    return make_pair(this->height,this->width);
}

void Maze::display()
{
    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width; ++j) 
        {
            if (grid[i][j] == 1) 
            {
                // Represent paths with narrow characters
                cout << "  ";
            } 
            else 
            {
                // Represent walls with continuous wide characters
                cout << "@@";
            }
        }
        cout << "\n";
    }
}