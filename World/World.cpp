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
            delete[] window[i];
        }
        delete[] testMap;
        delete[] mazeMap;
        delete[] window;
    }
}
void World::display(Player player)
{
    cout << "Screen:" << endl;
    cout << "command: " << player.getCommand() << endl;
    cout << "new player pos: " << player.getPos().first << "," << player.getPos().second << endl;
    cout << "empty cell size: " << this->emptyCell.size() << endl;
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            int cell = testMap[i][j];
            // cout<<cell;
            switch (cell)
            {
            case 0:
                cout << setw(2) << "#"; // 0 for wall
                break;
            case 1:
                cout << setw(2) << " "; // 1 for empty cell
                break;
            case 2:
                player.displayCreature(); // 2 for player
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
            int cell = testMap[i][j];
            // cout<<cell;
            switch (cell)
            {
            case 0:
                cout << setw(2) << "#"; // 0 for wall
                break;
            case 1:
                cout << setw(2) << " "; // 1 for empty cell
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
    testMap = new int *[height];
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
                this->testMap[i][j] = 0; // 0 for wall
            }
            else
            {
                this->testMap[i][j] = 1; // 1 for empty cell
                this->emptyCell.push_back(make_pair(i, j));
            }
        }
    }
    cout << "test map created" << endl;
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
    this->testMap[playerPos.first][playerPos.second] = 2;
}

void World::updateCreature()
{
    map<int, Creature>::iterator iter;
    for (iter = creatureList.begin(); iter != creatureList.end(); iter++)
    {
        testMap[iter->second.getPos().first][iter->second.getPos().second] = iter->first;
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
            this->testMap[oldPos.first][oldPos.second] = 1;
            this->testMap[newPos.first][newPos.second] = 2;
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
