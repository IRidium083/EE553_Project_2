#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"

class Player : public Creature
{
private:
    vector<char> commands;
    char command;
public:
    Player();
    Player(string, pair<int, int>);
    void readCommands();
    void readCommand();
    vector<char> getCommands();
    char getCommand();
};

#endif