/* Author: Yihan Huang
Date: Nov.15 2024
Description: Function definitions for the class Creature
*/

#include "Creature.h"
Creature ::Creature() {}

// @brief Constructor function for Employee
// @param string name of the Employee
// @param int ID of the Employee
// @return Employee class
Creature ::Creature(string name)
{
    this->name = name;
}

// @brief get name of the employee
// @return string name of the employee
string Creature ::getName()
{
    return this->name;
}

// @brief get position of the npc
// @return int[2] position (x,y) of the npc
pair<int, int> Creature ::getPos()
{
    return this->pos;
}

int Creature::getHitPoint()
{
    return this->hitPoint;
}
int Creature::getMaxHP(){
    return this->maxHP;
}
int Creature::getAttack()
{
    return this->attack;
}

int Creature::getDefence()
{
    return this->defence;
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

void Creature::setHipPoint(int hp)
{
    this->hitPoint = hp;
    
}
void Creature::setMaxHP(int hp){
    this->maxHP=hp;
}

void Creature::setAttack(int atk)
{
    this->attack = atk;
}

void Creature::setDefence(int def)
{
    this->defence = def;
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
    case 2: // Red
        cout << setw(2) << "\033[31m" << " " << this->icon << "\033[0m";
        break;
    case 1: // Green
        cout << setw(2) << "\033[32m" << " " << this->icon << "\033[0m";
        break;
    case 3: // Yellow
        cout << setw(2) << "\033[33m" << " " << this->icon << "\033[0m";
        break;
    case 4: // Blue
        cout << setw(2) << "\033[34m" << " " << this->icon << "\033[0m";
        break;
    case 5: // Magenta
        cout << setw(2) << "\033[35m" << " " << this->icon << "\033[0m";
        break;
    default:
        break;
    }
}