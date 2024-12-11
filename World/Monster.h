#ifndef MONSTER_H
#define MONSTER_H

#include "Creature.h"
using namespace std;

class Monster : public Creature
{
private:
    int speed;
    

public:
    Monster(string, int);

};
#endif