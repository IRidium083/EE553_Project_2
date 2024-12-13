/* Author: Yihan Huang
Date: Dec 2024
Description: World class. Includes map, creatures, and animation. And their interation logic.
*/

#include "World.h"
#include "../Animation/AnimationManager.h"

// @brief constructor function
// @param int width of the map
// @param int width of the map
World::World(int width, int height)
{
    this->width = width;
    this->height = height;
    this->turn = 0;
    srand(time(0));
};

// @brief destructor function, delete maps
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

// @brief constructor function
void World::addTurn()
{
    this->turn++;
}

// @brief get size of the map
pair<int, int> World::getSize()
{
    return make_pair(this->height, this->width);
}

// @brief load end cell from maze
void World::loadEndCell(pair<int, int> endCell)
{
    this->endCell = endCell;
}

// @brief load maze
// @param int ** double pointer to maze map
void World::loadMaze(int **maze)
{
    this->mazeMap = maze;
    maze[this->endCell.first][this->endCell.second] = -2;
}

// @brief load empty cells from maze
void World::loadEmpty(vector<pair<int, int>> empty)
{
    this->emptyCell = empty;
}

// @brief display the world with player
void World::display(Player *player)
{
    updateMist(player->getPos(), 2);
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            int cell = mazeMap[i][j] * mist[i][j];
            // int cell = testMap[i][j] * mist[i][j];  // for debug only
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
    this->printState(isCombat, player);
}

// @brief display the world without player
void World::display()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // int cell = testMap[i][j] * mist[i][j]; // for debug only
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

// @brief display state of the player
void World::printState(int state, Player *player)
{
    int hp = player->getHitPoint();
    int maxHP = player->getMaxHP();
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

// @brief make test map for debug
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

// @brief generate mist map
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
}

// @brief add creature to the world
void World::addCreature(Creature *newCreature)
{

    int i = rand() % emptyCell.size(); // find a empty cell randomly

    pair<int, int> newPos = emptyCell.at(i);

    emptyCell.erase(emptyCell.begin() + i); // erase the cell from empty cell vector

    newCreature->setPos(newPos);
    int ID = newCreature->getID();
    this->mazeMap[newPos.first][newPos.second] = ID;
    this->creatureList.emplace(ID, newCreature);
}

// @brief add player to the world
void World::addPlayer(Player *player)
{
    pair<int, int> playerPos = player->getPos();
    this->mazeMap[playerPos.first][playerPos.second] = 3;
    // this->testMap[playerPos.first][playerPos.second] = 3; // for debug only
}

// @brief update creature in the world
void World::updateCreature()
{
    cout << "start update creature" << endl;
    map<int, Creature *>::iterator iter;
    for (iter = creatureList.begin(); iter != creatureList.end(); iter++)
    {
        cout << "check creature: " << iter->first << iter->second->getName() << endl;

        // testMap[iter->second->getPos().first][iter->second->getPos().second] = iter->first; // for debug only
        mazeMap[iter->second->getPos().first][iter->second->getPos().second] = iter->first;
    }
}

// @brief update mist map
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

// @brief update player
void World::updatePlayer(Player *player)
{
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
    if (newPos == this->endCell)
    {
        endGame("win"); // the player wins when reach end cell
    }
    for (int i = 0; i < emptyCell.size(); i++)
    {
        if (emptyCell.at(i) == newPos) // search in empty cells
        {
            isCombat = 0;
            player->setPos(newPos);
            this->emptyCell.erase(emptyCell.begin() + i); // remove new pos from empty cells
            this->mazeMap[oldPos.first][oldPos.second] = 2;
            this->mazeMap[newPos.first][newPos.second] = 3;
            // this->testMap[oldPos.first][oldPos.second] = 2;  // for debug only
            // this->testMap[newPos.first][newPos.second] = 3;  // for debug only
            this->emptyCell.insert(emptyCell.begin() + i, oldPos); // add old pos to empty cells
        }
    }
    for (pair<int, Creature *> creature : this->creatureList)
    {
        if (creature.second->getPos() == newPos)
        {
            inCombat(player, creature.second); // get in combat if player reaches monster
            isCombat = 1;
            break;
        }
    }
    turnInfo["hp"] = player->getHitPoint();
}

// @brief combat function, calculate damage
void World::inCombat(Player *player, Creature *creature)
{
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

    if (player->getHitPoint() <= 0) // player dies
    {
        this->endGame("dead");
    }
    if (creature->getHitPoint() <= 0) // creature dies
    {
        player->setHipPoint(player->getHitPoint() + 1);
        creature->setVisual(' ', 1);
        emptyCell.push_back(creature->getPos());
    }
}

// @brief end game function
void World::endGame(string state)
{
    if (state == "dead") // player dies
    {
        DeathAnimation deathending;
        deathending.play();
        cout << "In your " << turn << " turns of advanture. " << "You received " << record["dmg"] << " damage. You delivered " << record["wound"]
             << " damage. You killed " << record["dmg"] / 10 << " monster(s)." << endl;
        delay(5000);
    }
    else if (state == "win") // player wins
    {
        cout << "In your " << turn << " turns of advanture. " << "You received " << record["dmg"] << " damage. You delivered " << record["wound"]
             << " damage. You killed " << record["dmg"] / 10 << " monster(s)." << endl;
        delay(5000);
        VictoryAnimation victoryending;
        victoryending.play();
    }
    this->running = false;
    exit(-1);
}

// @brief if world is running
bool World::isRunning()
{
    return this->running;
}
