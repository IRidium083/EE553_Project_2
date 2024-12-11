#include "World/World.h"

int main()
{
    cout << "Game Start." << endl;
    World world(25, 15);
    world.makeMist();
    world.makeTestMap();
    for (int i = 4; i < 15; i++)
    { // cratrue ID starts from 4
        cout << "add creature: " << i << endl;
        Creature *newCreature = new Monster("Monster" + to_string(i), i);
        // Monster newCreatre("Monster" + i, i);
        newCreature->setVisual('M', 1);
        newCreature->setHipPoint(10);
        newCreature->setAttack(2);
        newCreature->setDefence(2);
        cout << newCreature->getName() << endl;
        world.addCreature(newCreature);
    }
    world.updateCreature();
    cout << "World created" << endl;
    world.display();

    Player *newPlayer = new Player();
    newPlayer->setPos(make_pair(5, 5));
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
        Sleep(100);
        cout << "planer commands read" << endl;
        world.updatePlayer(newPlayer);
        world.addTurn();
        // system("cls");
        Sleep(10);
        world.display(newPlayer);
        Sleep(10);
    }

    return 0;
}