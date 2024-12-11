#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
#ifdef _WIN32
    #include <windows.h>
#endif
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
    int **mist;
    // Player player;
    vector<pair<int, int>> emptyCell;
    map<int, Creature> creatureList;
    int turn;

public:
    World(int, int);
    ~World();

    pair<int,int> getSize();
    
    void loadMaze(int**);
    void loadEmpty(vector<pair<int,int>>);

    void makeTestMap();
    void makeMist();
    void addCreature(Creature);
    void addPlayer(Player);

    void display(Player);
    void display();
    void displayWindow();

    void updateMist(pair<int, int> pos,int range);
    void updateCreature();
    void updatePlayer(Player &);
    void updateWindow();

    void inCombat(Player &, Creature &);
};

#endif