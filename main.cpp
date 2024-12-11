#include "World/World.h"
#include "Maze/Maze.h"

int main()
{
    //Maze maze = Maze::createMazeByDifficulty("easy");
    Maze maze = Maze::createMazeBySize(30,50);
    //int height = maze.getSize().first;
    //int width = maze.getSize().second;
    World world(20, 20);
    world.debug(true);
    world.makeTestMap();
    world.makeMist();
    cout << "load maze" << endl;
    //world.loadEmpty(maze.getEmptyCells());
    cout << "empty cell loaded" << endl;
    //world.loadMaze(maze.getMaze());
    cout << "maze loaded, size: " << world.getSize().first << "," << world.getSize().second << endl;
    
    world.display();
    for (int i = 4; i < 10; i++)
    { // cratrue ID starts from 4

        Monster newMonster("Monster" + i, i);
        newMonster.setVisual('M', 1);
        newMonster.setHipPoint(10);
        newMonster.setAttack(2);
        newMonster.setDefence(4);
        world.addCreature(newMonster);
        cout << i << endl;
    }
    cout << "creature added" << endl;
    world.updateCreature();
    cout << "World created" << endl;

    world.display();

    Player newPlayer;
    newPlayer.setPos(make_pair(2,2));
    newPlayer.setVisual('P', 2);
    newPlayer.setHipPoint(10);
    newPlayer.setAttack(3);
    newPlayer.setDefence(5);
    cout << "Add player" << endl;
    world.addPlayer(newPlayer);
    cout << "Player added" << endl;
    world.display(newPlayer);
    cout<<"Start game"<<endl;
    while (1)
    {
        newPlayer.readCommand();
        Sleep(100);
        cout << "planer commands read" << endl;
        world.updatePlayer(newPlayer);
        system("cls");
        Sleep(10);
        world.display(newPlayer);
        Sleep(10);
    }
    
    return 0;
}