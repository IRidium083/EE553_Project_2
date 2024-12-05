#include "World.h"

int main()
{
    cout << "Game Start." << endl;
    World world(35, 15);

    world.makeTestMap();
    for (int i = 3; i < 12; i++)
    { // cratrue ID starts from 3
        Creature newCreatre("Monster" + i, i);
        newCreatre.setVisual('M', 1);
        world.addCreature(newCreatre);
    }
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