#include "World.h"
#include "Maze/Maze.h"
#include "Animation/AnimationManager.h"
#include <chrono>
#include <thread>

int main()
{
    // Play the opening animation
    OpeningAnimation opening;
    //opening.play();

    //Maze maze = Maze::createMazeByDifficulty("easy");
    Maze maze = Maze::createMazeBySize(10,10,10);
    cout<<"Player at: "<<maze.getStartAndEndPoints()[0].first<<","<<maze.getStartAndEndPoints()[0].second<<endl;
    cout<<"Goal at: "<<maze.getStartAndEndPoints()[1].first<<","<<maze.getStartAndEndPoints()[1].second<<endl;
    maze.display();
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
for (int i = 4; i < 5; i++)
    { // cratrue ID starts from 4
        cout << "add creature: " << i << endl;
        Creature *newCreature = new Monster("Monster" + to_string(i), i);
        // Monster newCreatre("Monster" + i, i);
        newCreature->setVisual('M', 1);
        newCreature->setHipPoint(10);
        newCreature->setAttack(200);
        newCreature->setDefence(2);
        cout << newCreature->getName() << endl;
        world.addCreature(newCreature);
    }
    cout << "creature added" << endl;
    world.updateCreature();
    cout << "World created" << endl;

    world.display();

    Player *newPlayer = new Player();
    newPlayer->setPos(make_pair(2,2));
    cout<<"Player at: "<<maze.getStartAndEndPoints()[0].first<<","<<maze.getStartAndEndPoints()[0].second<<endl;
    newPlayer->setVisual('P', 2);
    newPlayer->setHipPoint(10);
    newPlayer->setAttack(4);
    newPlayer->setDefence(5);
    cout << "Add player" << endl;
    world.addPlayer(newPlayer);
    cout << "Player added" << endl;
    world.display(newPlayer);
    while (1)
    {
        newPlayer->readCommand();
        this_thread::sleep_for(std::chrono::milliseconds(100));
        cout << "planer commands read" << endl;
        world.updatePlayer(newPlayer);
        world.addTurn();
        //system("cls");
        this_thread::sleep_for(std::chrono::milliseconds(10));
        world.display(newPlayer);
        this_thread::sleep_for(std::chrono::milliseconds(10));
    }


    // Play the ending animation
    // VictoryAnimation ending;
    // ending.play();
    
    return 0;
}