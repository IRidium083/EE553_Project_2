#include "World/World.h"
#include "Maze/Maze.h"

int main()
{
    Maze maze = Maze::createMazeByDifficulty("easy");
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
    for (int i = 4; i < 10; i++)
    { // cratrue ID starts from 4

        Creature newCreatre("Monster" + i, i);
        newCreatre.setVisual('M', 1);

        world.addCreature(newCreatre);
        cout << i << endl;
    }
    cout << "creature added" << endl;
    world.updateCreature();
    cout << "World created" << endl;

    world.display();

    Player newPlayer;
    newPlayer.setPos(make_pair(5, 5));
    newPlayer.setVisual('P', 2);
    cout << "Add player" << endl;
    world.addPlayer(newPlayer);
    cout << "Player added" << endl;
    world.display(newPlayer);
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