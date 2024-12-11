#include "World/World.h"
#include "Maze/Maze.h"
#include "Animation/AnimationManager.h"
#include <chrono>
#include <thread>

int main()
{
    // Play the opening animation
    OpeningAnimation opening;
    opening.play();

    Maze maze = Maze::createMazeByDifficulty("easy");
    //Maze maze = Maze::createMazeBySize(30,50);
    int height = maze.getSize().first;
    int width = maze.getSize().second;
    World world(height, width);
    world.makeMist();
    cout << "load maze" << endl;
    world.loadEmpty(maze.getEmptyCells());
    cout << "empty cell loaded" << endl;
    world.loadMaze(maze.getMaze());
    cout << "maze loaded, size: " << world.getSize().first << "," << world.getSize().second << endl;
    
    world.display();
    for (int i = 4; i < 8; i++)
    { // cratrue ID starts from 4

        Creature newCreatre("Monster" + to_string(i), i);
        newCreatre.setVisual('M', 1);

        world.addCreature(newCreatre);
        cout << i << endl;
    }
    cout << "creature added" << endl;
    world.updateCreature();
    cout << "World created" << endl;

    world.display();

    Player newPlayer;
    newPlayer.setPos(make_pair(2,2));
    newPlayer.setVisual('P', 2);
    cout << "Add player" << endl;
    world.addPlayer(newPlayer);
    cout << "Player added" << endl;
    world.display(newPlayer);
    cout<<"Start game"<<endl;
    while (1)
    {
        newPlayer.readCommand();
        this_thread::sleep_for(std::chrono::milliseconds(100));
        cout << "planer commands read" << endl;
        world.updatePlayer(newPlayer);
        system("cls");
        this_thread::sleep_for(std::chrono::milliseconds(10));
        world.display(newPlayer);
        this_thread::sleep_for(std::chrono::milliseconds(10));

        // // Play the dead animation
        // DeathAnimation deathending;
        // deathending.play();
    }


    // Play the ending animation
    VictoryAnimation ending;
    ending.play();
    
    return 0;
}