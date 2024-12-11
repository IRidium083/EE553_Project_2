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



void Player::readCommand(){
    cout << "Please enter the next moves :";
    char c;
    cin>>c;
    this->command=c;
}


char Player::getCommand(){
    return this->command;
}