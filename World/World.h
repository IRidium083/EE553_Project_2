#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <windows.h>
#include "Monster.h"
#include "Player.h"
// #include "Maze.h"

class World
{
private:
    int height;
    int width;
    int **testMap;
    int **mazeMap;
    int **window;
    //Player player;
    vector<pair<int, int>> emptyCell;
    map<int, Creature> creatureList;
    int turn;

public:
    World(int, int);
    ~World();

    void makeTestMap();
    void addCreature(Creature);
    void addPlayer(Player);

    void display(Player);
    void display();
    void displayWindow();

    void updateCreature();
    void updatePlayer(Player &);
    void updateWindow();

    void inCombat(Player&, Creature&);
};

#endif