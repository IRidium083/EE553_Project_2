#!/bin/bash

# Compile the project
g++ -std=c++11 main.cpp World/World.cpp World/Player.cpp World/Creature.cpp \
    Maze/Maze.cpp Animation/AnimationTools.cpp Animation/DeathAnimation.cpp \
    Animation/OpeningAnimation.cpp Animation/VictoryAnimation.cpp -o project

# Run the program
./project
