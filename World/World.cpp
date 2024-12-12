/* Author: Yihan Huang
Date: Dec 2024
Description: World class. Includes map, creatures, and animation. And their interation logic.
*/

#include "World.h"
#include "../Animation/AnimationManager.h"
World::World(int width, int height)
{
    this->width = width;
    this->height = height;
    this->turn = 0;
    srand(time(0));
};

World::~World()
{
    if (this->testMap != nullptr)
    {
        for (int i = 0; i < this->height; i++)
        {
            delete[] testMap[i];
            delete[] mazeMap[i];
            delete[] mist[i];
        }
        delete[] testMap;
        delete[] mazeMap;
        delete[] mist;
    }
}

void World::addTurn()
{
    this->turn++;
}

pair<int, int> World::getSize()
{
    return make_pair(this->height, this->width);
}

void World::loadEndCell(pair<int, int> endCell)
{
    this->endCell = endCell;
}

void World::loadMaze(int **maze)
{
    this->mazeMap = maze;
    maze[this->endCell.first][this->endCell.second] = -2;
}

void World::loadEmpty(vector<pair<int, int>> empty)
{
    this->emptyCell = empty;
    // cout << "size of empty cell: " << empty.size() << endl;
}
void World::display(Player *player)
{
    updateMist(player->getPos(), 2);
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            int cell = mazeMap[i][j] * mist[i][j];
            // int cell = testMap[i][j] * mist[i][j];
            switch (cell)
            {
            case -1:
                break;
            case -2:
                cout << setw(2) << "\033[93m" << " " << '?' << "\033[0m";
                break;
            case 0:
                cout << setw(2) << "~"; // 0 for mist
                break;
            case 1:
                cout << setw(2) << "#"; // 1 for wall
                break;
            case 2:
                cout << setw(2) << " "; // 2 for empty cell
                break;
            case 3:
                player->displayCreature(); // 3 for player
                break;
            default:
                this->creatureList.at(cell)->displayCreature(); // IDs in the creature list
                break;
            }
        }
        cout << endl;
    }
    // cout << "Turn: " << this->turn << endl;
    // cout << "Player HP: " << player->getHitPoint() << endl;
    this->printState(isCombat, player);
}

void World::display()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // int cell = testMap[i][j] * mist[i][j];
            int cell = mazeMap[i][j] * mist[i][j];
            switch (cell)
            {
            case -1:
                break;
            case -2:
                cout << setw(2) << "\033[93m" << " " << '?' << "\033[0m";
                break;
            case 0:
                cout << setw(2) << "~"; // ~ for mist
                break;
            case 1:
                cout << setw(2) << "#"; // 1 for wall
                break;
            case 2:
                cout << setw(2) << " "; // 2 for empty cell
                break;
            case 3:
                break;
            default:
                this->creatureList.at(cell)->displayCreature(); // IDs in the creature list
                break;
            }
        }
        cout << endl;
    }
}

void World::printState(int state, Player *player)
{
    int hp = player->getHitPoint();
    int maxHP = player->getMaxHP();
    //cout << hp << ";" << maxHP << endl;
    cout << "This is turn " << this->turn << ". Your HP is: " << hp << endl;
    switch (state)
    {
    case 0: // normal moving
        if (hp >= maxHP / 3 * 2)
            cout << "You are walking confidently!" << endl;
        else if (hp >= maxHP / 3 && hp < maxHP / 3 * 2)
            cout << "You are walking worriedly!" << endl;
        else if (hp < maxHP / 3)
            cout << "You are walking painfully!" << endl;
        break;
    case 1: // in combat
        cout << "You are in combat!" << endl;
        cout << "You hit the enemy by: " << turnInfo["dmg"] << endl;
        cout << "The enemy hit you by: " << turnInfo["wound"] << endl;
        break;
    default:
        break;
    }
}
void World::displayWindow()
{
    int windowHeight = 5;
    int windowWidth = 5;
    for (int i = 0; i < windowHeight; i++)
    {
        for (int j = 0; j < windowWidth; j++)
        {
            if (i == 0 || i == windowHeight - 1)
            {
                if (j == 0 || j == windowWidth - 1)
                {
                    cout << "+";
                }
                else
                {
                    cout << "-";
                }
            }
            else if (j == 0 || j == windowWidth - 1)
            {
                cout << "|";
            }
        }
        cout << endl;
    }
}

void World::makeTestMap()
{
    cout << "start create test map" << endl;
    this->testMap = new int *[height];
    for (int i = 0; i < height; i++)
    {
        this->testMap[i] = new int[width];
    }
    cout << "height: " << height << endl;
    cout << "width: " << width << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                this->testMap[i][j] = 1; // 1 for wall
            }
            else
            {
                this->testMap[i][j] = 2; // 2 for empty cell
                this->emptyCell.push_back(make_pair(i, j));
            }
        }
    }
    cout << "test map created" << endl;
}

void World::makeMist()
{
    // cout << "start create mist" << endl;
    this->mist = new int *[height];
    for (int i = 0; i < height; i++)
    {
        this->mist[i] = new int[width];
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            this->mist[i][j] = 0; // 0: mist in cell, 1: no mist in cell
        }
    }
    // cout << "mist created" << endl;
}

void World::addCreature(Creature *newCreature)
{

    int i = rand() % emptyCell.size(); // find a empty cell randomly

    pair<int, int> newPos = emptyCell.at(i);

    emptyCell.erase(emptyCell.begin() + i); // erase the cell from empty cell vector

    newCreature->setPos(newPos);
    int ID = newCreature->getID();
    // cout << "Creature ID: " << ID << endl;
    this->mazeMap[newPos.first][newPos.second] = ID;
    this->creatureList.emplace(ID, newCreature);
}

void World::addPlayer(Player *player)
{
    pair<int, int> playerPos = player->getPos();
    this->mazeMap[playerPos.first][playerPos.second] = 3;
    // this->testMap[playerPos.first][playerPos.second] = 3;
}

void World::updateCreature()
{
    cout << "start update creature" << endl;
    map<int, Creature *>::iterator iter;
    for (iter = creatureList.begin(); iter != creatureList.end(); iter++)
    {
        cout << "check creature: " << iter->first << iter->second->getName() << endl;

        // testMap[iter->second->getPos().first][iter->second->getPos().second] = iter->first;
        mazeMap[iter->second->getPos().first][iter->second->getPos().second] = iter->first;
    }
}
void World::updateMist(pair<int, int> pos, int range)
{
    for (int i = pos.first - range; i <= pos.first + range; i++)
    {
        for (int j = pos.second - range; j <= pos.second + range; j++)
        {
            if (i >= 0 && i < height && j >= 0 && j < width)
            {
                this->mist[i][j] = 1;
            }
        }
    }
}
void World::updatePlayer(Player *player)
{

    // cout << "comMand is:" << player->getCommand() << endl;
    // cout << "++" << endl;
    pair<int, int> oldPos = player->getPos();
    pair<int, int> newPos;
    switch (player->getCommand())
    {
    case 'Q':
        exit(-1);
        break;
    case 'A':
        newPos = make_pair(player->getPos().first, player->getPos().second - 1); // move 1 cell left
        break;
    case 'D':
        newPos = make_pair(player->getPos().first, player->getPos().second + 1); // move 1 cell right
        break;
    case 'W':
        newPos = make_pair(player->getPos().first - 1, player->getPos().second); // move 1 cell up
        break;
    case 'S':
        newPos = make_pair(player->getPos().first + 1, player->getPos().second); // move 1 cell down
        break;
    default:
        break;
    }
    // cout << newPos.first << "," << newPos.second << endl;
    if (newPos == this->endCell)
    {
        endGame("win");
    }
    for (int i = 0; i < emptyCell.size(); i++)
    {
        if (emptyCell.at(i) == newPos)
        {
            isCombat = 0;
            player->setPos(newPos);
            this->emptyCell.erase(emptyCell.begin() + i);
            this->mazeMap[oldPos.first][oldPos.second] = 2;
            this->mazeMap[newPos.first][newPos.second] = 3;
            // this->testMap[oldPos.first][oldPos.second] = 2;
            // this->testMap[newPos.first][newPos.second] = 3;
            this->emptyCell.insert(emptyCell.begin() + i, oldPos);
        }
    }
    for (pair<int, Creature *> creature : this->creatureList)
    {
        if (creature.second->getPos() == newPos)
        {
            inCombat(player, creature.second);
            isCombat = 1;
            break;
        }
    }
    turnInfo["hp"] = player->getHitPoint();
    // cout << "update finish" << endl;
}

void World::inCombat(Player *player, Creature *creature)
{
    // cout << "Player HP: " << player->getHitPoint() << endl;
    // cout << creature->getName() << " HP: " << creature->getHitPoint() << endl;
    int playerDMG, monsterDMG;
    int playerATK = player->getAttack();
    int monsterATK = creature->getAttack();
    int playerDEF = player->getDefence();
    int monsterDEF = creature->getDefence();
    if (playerATK > monsterDEF)
        playerDMG = playerATK - monsterDEF;
    else
        playerDMG = 1;
    if (monsterATK > playerDEF)
        monsterDMG = monsterATK - playerDEF;
    else
        monsterDMG = 1;
    creature->setHipPoint(creature->getHitPoint() - playerDMG);
    player->setHipPoint(player->getHitPoint() - monsterDMG);
    turnInfo["dmg"] = playerDMG;
    turnInfo["wound"] = monsterDMG;
    record["dmg"] += playerDMG;
    record["wound"] += monsterDMG;
    if (player->getHitPoint() <= 0)
    {
        this->endGame("dead");
    }
    if (creature->getHitPoint() <= 0)
    {
        player->setHipPoint(player->getHitPoint() + 1);
        creature->setVisual(' ', 1);
        emptyCell.push_back(creature->getPos());
        
    }
}

void World::endGame(string state)
{
    if (state == "dead")
    {
        DeathAnimation deathending;
        deathending.play();
        cout << "In your " << turn << " turns of advanture. " << "You received " << record["dmg"] << " damage. You delivered " << record["wound"]
             << " damage. You killed " << record["dmg"]/10 << " monster(s)." << endl;
        delay(5000);
    }
    else if (state == "win")
    {
        cout << "In your " << turn << " turns of advanture. " << "You received " << record["dmg"] << " damage. You delivered " << record["wound"]
             << " damage. You killed " << record["dmg"]/10 << " monster(s)." << endl;
        delay(5000);
        VictoryAnimation victoryending;
        victoryending.play();
    }
    this->running = false;
    exit(-1);
}

bool World::isRunning()
{
    return this->running;
}
