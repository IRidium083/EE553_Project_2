/* Author: David
Date: Dec 2024
Description: Declare functions needed in Maze.cpp
*/

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Maze 
{
private:
    int width, height;              // Logical width and height of the maze
    int** grid;                     // Dynamically allocated 2D array for the maze structure

    void generateMaze(int x, int y); // Recursive function to generate the maze
    void shuffleDirections(vector<pair<int, int>>& directions); // Shuffle directions randomly

public:
    Maze(int width, int height);    // Constructor
    ~Maze();                        // Destructor to free dynamic memory

    void generate();                // Entry function to generate the maze
    int** getMaze();                // Return the maze grid for external modifications
    void display();                 // Display the maze
    pair<int,int> getSize();       //return size of the maze
    vector<pair<int, int>> getEmptyCells(); // Get all path coordinates
    void addExtraConnections(int count); // Add extra connections (break additional walls) to increase the maze's complexity
    vector<pair<int, int>>getStartAndEndPoints(); //// Generate random start and end points

    static Maze createMazeBySize(int width, int height, int); // The temporary function is convenient for changing the maze size when needed
    static Maze createMazeByDifficulty(const string& difficulty); // Create a maze based on difficulty
    static string selectDifficulty(); // Select difficulty level
};

#endif
