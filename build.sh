#!/bin/bash
g++ -std=c++11 main.cpp \
    World/World.cpp \
    World/Creature.cpp \
    World/Monster.cpp \
    World/Player.cpp \
    Maze/Maze.cpp \
    Animation/AnimationTools.cpp \
    Animation/DeathAnimation.cpp \
    Animation/OpeningAnimation.cpp \
    Animation/VictoryAnimation.cpp \
    -o project
