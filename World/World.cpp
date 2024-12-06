#include "World.h"
World::World(int width, int height)
{
    this->width = width;
    this->height = height;
    cout << "test" << endl;
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

pair<int, int> World::getSize()
{
    return make_pair(this->height, this->width);
}

void World::loadMaze(int **maze)
{
    this->mazeMap = maze;
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            int temp=mazeMap[i][j]+1;
            mazeMap[i][j] = temp;
        }
    }
}
void World::loadEmpty(vector<pair<int, int>> empty)
{
    this->emptyCell = empty;
    cout << "size of empty cell: " << empty.size() << endl;
}
void World::display(Player player)
{
    cout << "Screen:" << endl;
    cout << "command: " << player.getCommand() << endl;
    cout << "new player pos: " << player.getPos().first << "," << player.getPos().second << endl;
    cout << "empty cell size: " << this->emptyCell.size() << endl;
    updateMist(player.getPos(), 2);
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // int cell = testMap[i][j] * mist[i][j];
            int cell = mazeMap[i][j] * mist[i][j];
            switch (cell)
            {
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
                player.displayCreature(); // 3 for player
                break;
            default:
                this->creatureList.at(cell).displayCreature(); // IDs in the creature list
                break;
            }
        }
        cout << endl;
    }
}
void World::display()
{
    cout << "Screen:" << endl;
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // int cell = testMap[i][j] * mist[i][j];
            int cell = mazeMap[i][j] * mist[i][j];
            // cout<<cell;
            switch (cell)
            {
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
                this->creatureList.at(cell).displayCreature(); // IDs in the creature list
                break;
            }
        }
        cout << endl;
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
    cout << "start create mist" << endl;
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
    cout << "mist created" << endl;
}

void World::addCreature(Creature newCreature)
{
    // find a empty cell randomly
    int i = rand() % emptyCell.size();
    pair<int, int> newPos = emptyCell.at(i);

    // erase the cell from empty cell vector
    emptyCell.erase(emptyCell.begin() + i);

    newCreature.setPos(newPos);
    int ID = newCreature.getID();
    this->creatureList.emplace(ID, newCreature);
}

void World::addPlayer(Player player)
{
    pair<int, int> playerPos = player.getPos();
    // this->testMap[playerPos.first][playerPos.second] = 3;
    this->mazeMap[playerPos.first][playerPos.second] = 3;
}

void World::updateCreature()
{
    map<int, Creature>::iterator iter;
    for (iter = creatureList.begin(); iter != creatureList.end(); iter++)
    {
        // testMap[iter->second.getPos().first][iter->second.getPos().second] = iter->first;
        mazeMap[iter->second.getPos().first][iter->second.getPos().second] = iter->first;
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
void World::updatePlayer(Player &player)
{

    cout << "comMand is:" << player.getCommand() << endl;
    cout << "++" << endl;
    pair<int, int> oldPos = player.getPos();
    pair<int, int> newPos;
    switch (player.getCommand())
    {
    case 'A':
        newPos = make_pair(player.getPos().first, player.getPos().second - 1); // move 1 cell left
        break;
    case 'D':
        newPos = make_pair(player.getPos().first, player.getPos().second + 1); // move 1 cell right
        break;
    case 'W':
        newPos = make_pair(player.getPos().first - 1, player.getPos().second); // move 1 cell up
        break;
    case 'S':
        newPos = make_pair(player.getPos().first + 1, player.getPos().second); // move 1 cell down
        break;
    default:
        break;
    }
    cout << newPos.first << "," << newPos.second << endl;
    for (int i = 0; i < emptyCell.size(); i++)
    {
        if (emptyCell.at(i) == newPos)
        {
            player.setPos(newPos);
            this->emptyCell.erase(emptyCell.begin() + i);
            // this->testMap[oldPos.first][oldPos.second] = 2;
            // this->testMap[newPos.first][newPos.second] = 3;
            this->mazeMap[oldPos.first][oldPos.second] = 2;
            this->mazeMap[newPos.first][newPos.second] = 3;
            this->emptyCell.insert(emptyCell.begin() + i, oldPos);
        }
        else
        {
            for (pair<int, Creature> creature : this->creatureList)
            {
                if (creature.second.getPos() == newPos)
                {
                    inCombat(player, creature.second);
                }
            }
        }
    }

    cout << "update finish" << endl;
}

void World::inCombat(Player &player, Creature &creature)
{
}
