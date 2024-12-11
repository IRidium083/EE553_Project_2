#include "World/World.h"
#include <chrono>
#include <thread>


int main()
{
    cout << "Game Start." << endl;
    World world(25, 15);
    world.makeMist();
    world.makeTestMap();
    for (int i = 4; i < 15; i++)
    { // cratrue ID starts from 4
        Creature newCreatre("Monster" + to_string(i), i);
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
        this_thread::sleep_for(std::chrono::milliseconds(100));
        cout << "planer commands read" << endl;
        world.updatePlayer(newPlayer);
        system("cls");
        this_thread::sleep_for(std::chrono::milliseconds(10));
        world.display(newPlayer);
        this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}