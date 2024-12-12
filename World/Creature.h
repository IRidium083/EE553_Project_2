#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

class Creature
{
protected:
    string name;
    pair<int, int> pos;
    int hitPoint;
    int maxHP;
    int attack;
    int defence;
    int ID;
    char icon;
    int col;

public:
    Creature();
    Creature(string);
    string getName();
    pair<int, int> getPos();
    virtual int getID();

    int getHitPoint();
    int getAttack();
    int getDefence();
    int getMaxHP();

    void setName(string);
    void setPos(pair<int, int>);
    virtual void setID(int);
    
    void setHipPoint(int);
    void setAttack(int);
    void setDefence(int);
    void setMaxHP(int);
    
    void setVisual(char, int);
    void displayCreature();
};
#endif