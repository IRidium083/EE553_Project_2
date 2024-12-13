/* Author: Yihan Huang, David
Date: Dec.11 2024
Description: Main function for running the game.
*/

#include "World/World.h"
#include "Maze/Maze.h"
#include "Animation/AnimationManager.h"
// #include <chrono>
// #include <thread>

int main()
{
    // Play the opening animation
    OpeningAnimation opening;
    opening.play();

    // Generate maze
    string difficulty = Maze::selectDifficulty();
    Maze maze = Maze::createMazeByDifficulty(difficulty);

    // Initialize the world
    int height = maze.getSize().first;
    int width = maze.getSize().second;
    World world(height, width);
    world.makeMist();
    world.loadEmpty(maze.getEmptyCells());
    world.loadEndCell(maze.getStartAndEndPoints()[1]);
    world.loadMaze(maze.getMaze());
    
    //config monsters
    int monster_quantity = 0;
    if (difficulty == "easy")
        monster_quantity = 3;
    else if (difficulty == "medium")
        monster_quantity = 6;
    else if (difficulty == "hard")
        monster_quantity = 9;

    // populate maze with monsters
    for (int i = 1; i <= monster_quantity; i++)
    {
        // cratrue ID starts from 100
        int id = 100 + i;
        Creature *newCreature = new Monster("Monster" + to_string(i), id);
        newCreature->setVisual('M', i % 4 + 2);
        newCreature->setHipPoint(10);
        newCreature->setAttack(2);
        newCreature->setDefence(2);
        world.addCreature(newCreature);
    }
    //cout << "World created" << endl;

    // add player
    Player *newPlayer = new Player();
    newPlayer->setPos(maze.getStartAndEndPoints()[0]);
    newPlayer->setVisual('P', 1);
    if (difficulty == "easy")
    {
        newPlayer->setHipPoint(10);
        newPlayer->setMaxHP(10);
    }
    else if (difficulty == "medium")
    {
        newPlayer->setHipPoint(20);
        newPlayer->setMaxHP(20);
    }
    else if (difficulty == "hard")
    {
        newPlayer->setHipPoint(30);
        newPlayer->setMaxHP(30);
    }
    newPlayer->setAttack(4);
    newPlayer->setDefence(5);
    world.addPlayer(newPlayer);
    world.display(newPlayer);

    // run game
    while (world.isRunning())
    {
        newPlayer->readCommand();
        delay(100);
        //cout << "planer commands read" << endl;
        world.updatePlayer(newPlayer);
        world.addTurn();
        clearScreen();
        delay(10);
        world.display(newPlayer);
        delay(10);
    }

    return 0;
}