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
    int turn;       // total number of turns of the game
    int height;     //map height
    int width;      //map width
    int **testMap;
    int **mazeMap;
    int **window;
    int **mist;
    bool running=true;
    bool DEBUG = false;
    int isCombat=0;
    map<string,int> record={{"kills",0},{"dmg",0},{"wound",0}};
    map<string,int> turnInfo={{"hp",0},{"dmg",0},{"wound",0}};
    vector<pair<int, int>> emptyCell;
    pair<int,int> endCell;
    map<int, Creature*> creatureList;

public:
    World(int, int);
    ~World();

    pair<int,int> getSize();
    void addTurn();
    void loadMaze(int**);
    void loadEmpty(vector<pair<int,int>>);
    void loadEndCell(pair<int,int>);

    void makeTestMap();
    void makeMist();
    void addCreature(Creature*);
    void addPlayer(Player*);

    void display(Player*);
    void display();
    void displayWindow();
    void printState(int,Player*);

    void updateMist(pair<int, int> pos,int range);
    void updateCreature();
    void updatePlayer(Player *);
    void updateWindow();

    void inCombat(Player *, Creature *);
    void endGame(string);
    bool isRunning();
    
};

#endif