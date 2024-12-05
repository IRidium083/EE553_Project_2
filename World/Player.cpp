#include "Player.h"
Player::Player() {}
Player::Player(string name, pair<int, int> pos)
{
    this->name = name;
    this->pos = pos;
}

void Player::readCommands()
{
    string input;
    getline(cin, input);
    istringstream instream(input);
    char c;
    commands.clear();
    while (instream >> c)
    {
        this->commands.push_back(c);
    }
}

void Player::readCommand(){
    cout << "Please enter the next moves :";
    char c;
    cin>>c;
    this->command=c;
}
vector<char> Player::getCommands()
{
    return this->commands;
}

char Player::getCommand(){
    return this->command;
}