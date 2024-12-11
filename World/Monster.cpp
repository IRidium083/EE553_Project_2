/* Author: Yihan Huang
Date: Dec 2024
Description: Monster class. 
*/ 
#include "Monster.h"
Monster::Monster(string name, int ID) : Creature(name)
{
    this->name = name;
    this->ID = ID;
}
// @brief set ID of the Monster
// @param int ID of the Monster
// @return void
void Creature ::setID(int id)
{
    this->ID = id;
}

// @brief get ID of the creature
// @return int ID of the crature
int Creature ::getID()
{
    return this->ID;
}