/* Author: Yihan Huang
Date: Nov.15 2024
Description: Function definitions for the class npc
*/

#include "Creature.h"
Creature ::Creature() {}
// @brief Constructor function for Employee
// @param string name of the Employee
// @param int ID of the Employee
// @return Employee class
Creature ::Creature(string name, int ID)
{
    this->name = name;
    this->ID = ID;
}

// @brief get name of the employee
// @return string name of the employee
string Creature ::getName()
{
    return this->name;
}

// @brief get ID of the creature
// @return int ID of the crature
int Creature ::getID()
{
    return this->ID;
}

// @brief get position of the npc
// @return int[2] position (x,y) of the npc
pair<int, int> Creature ::getPos()
{
    return this->pos;
}

// @brief set name of the npc
// @param string name of the npc
// @return void
void Creature ::setName(string name)
{
    this->name = name;
}

// @brief set position of the npc
// @param int[2] position of the npc
// @return void
void Creature ::setPos(pair<int, int> pos)
{
    this->pos = pos;
}

// @brief set layer of the npc
// @param int layer of the npc
// @return void
void Creature ::setID(int id)
{
    this->ID = id;
}
void Creature::setVisual(char icon, int col)
{
    this->icon = icon;
    this->col = col;
}
void Creature::displayCreature()
{
    switch (this->col)
    {
    case 1:
        cout << setw(2) << "\033[31m" << " " << this->icon << "\033[0m";
        break;
    case 2:
        cout << setw(2) << "\033[32m" << " " << this->icon << "\033[0m";
    default:
        break;
    }
}