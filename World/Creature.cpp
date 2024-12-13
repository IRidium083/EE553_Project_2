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

// @brief get position of the creature
// @return pair<int,int> position of creature
pair<int, int> Creature ::getPos()
{
    return this->pos;
}

// @brief get hp of the creature
// @return int hp of creature
int Creature::getHitPoint()
{
    return this->hitPoint;
}

// @brief get attack of the creature
// @return int attack of creature
int Creature::getAttack()
{
    return this->attack;
}

// @brief get defence of the creature
// @return int defence of creature
int Creature::getDefence()
{
    return this->defence;
}

// @brief set name of the creature
// @param string name of the creature
// @return void
void Creature ::setName(string name)
{
    this->name = name;
}

// @brief set position of the creature
// @param pair<int,int> position of the creature
// @return void
void Creature ::setPos(pair<int, int> pos)
{
    this->pos = pos;
}

// @brief set hp of the creature
// @param int hp of the creature
// @return void
void Creature::setHipPoint(int hp)
{
    this->hitPoint = hp;
}

// @brief set attack of the creature
// @param int attack of the creature
// @return void
void Creature::setAttack(int atk)
{
    this->attack = atk;
}

// @brief set defence of the creature
// @param int defence of the creature
// @return void
void Creature::setDefence(int def)
{
    this->defence = def;
}

// @brief set visual of the creature
// @param char visual icon of the creature
// @param int color code of the creature
// @return void
void Creature::setVisual(char icon, int col)
{
    this->icon = icon;
    this->col = col;
}

// @brief display creature
// @return void
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