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

    string difficulty = Maze::selectDifficulty();
    
    Maze maze = Maze::createMazeByDifficulty(difficulty); 
    // cout<<"Player at: "<<maze.getStartAndEndPoints()[0].first<<","<<maze.getStartAndEndPoints()[0].second<<endl;
    // cout<<"Goal at: "<<maze.getStartAndEndPoints()[1].first<<","<<maze.getStartAndEndPoints()[1].second<<endl;
    // maze.display();
    int height = maze.getSize().first;
    int width = maze.getSize().second;
    World world(height, width);
    world.makeMist();
    world.loadEmpty(maze.getEmptyCells());
    // cout << "empty cell loaded" << endl;
    world.loadEndCell(maze.getStartAndEndPoints()[1]);
    world.loadMaze(maze.getMaze());
    
    // cout << "maze loaded, size: " << world.getSize().first << "," << world.getSize().second << endl;
    
    // world.display();
    int monster_quantity = 0;
    if(difficulty == "easy") monster_quantity = 3;
    else if (difficulty == "medium") monster_quantity = 6;
    else if (difficulty == "hard") monster_quantity = 9;
    
    for (int i = 1; i <= monster_quantity; i++)
    { // cratrue ID starts from 4
        // cout << "add creature: " << i << endl;
        int id = 100 + i;
        Creature *newCreature = new Monster("Monster" + to_string(i), id);
        // Monster newCreatre("Monster" + i, i);
        newCreature->setVisual('M', i % 5 + 1);
        newCreature->setHipPoint(10);
        newCreature->setAttack(2);
        newCreature->setDefence(2);
        // cout << newCreature->getName() << endl;
        world.addCreature(newCreature);
    }
    // cout << "creature added" << endl;
    // world.updateCreature();
    cout << "World created" << endl;

    // world.display();

    Player *newPlayer = new Player();
    //cout<<"Player at: "<<maze.getStartAndEndPoints()[0].first<<","<<maze.getStartAndEndPoints()[0].second<<endl;
    newPlayer->setPos(maze.getStartAndEndPoints()[0]);
    //cout<<"Player at: "<<maze.getStartAndEndPoints()[0].first<<","<<maze.getStartAndEndPoints()[0].second<<endl;
    newPlayer->setVisual('P', 2);
    if(difficulty == "easy") newPlayer->setHipPoint(10);
    else if (difficulty == "medium") newPlayer->setHipPoint(20);
    else if (difficulty == "hard") newPlayer->setHipPoint(30);
    newPlayer->setAttack(4);
    newPlayer->setDefence(5);
    // cout << "Add player" << endl;
    world.addPlayer(newPlayer);
    // cout << "Player added" << endl;
    world.display(newPlayer);
    while (world.isRunning())
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

    
    return 0;
}