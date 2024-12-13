/* Author: Yihan Huang
Date: Dec 2024
Description: Player class. 
*/ 
#include "Player.h"
Player::Player() {}
Player::Player(string name, pair<int, int> pos)
{
    this->name = name;
    this->pos = pos;
}

// @brief read commands for the player
// @return void
void Player::readCommand(){
    cout << "Please enter the next moves (W:left, D:right, W:up, S:down, Q: quit):"<<endl;
    char c;
    cin>>c;
    this->command=c;
}

char Player::getCommand(){
    return this->command;
}

// @brief set max hp of the creature
// @param int max hp of the creature
// @return void
void Creature::setMaxHP(int hp)
{
    this->maxHP = hp;
}

// @brief get max hp of the creature
// @return int max hp of the creature
int Creature::getMaxHP()
{
    return this->maxHP;
}