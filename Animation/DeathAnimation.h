/* Author: David
Date: Dec 2024
Description: Declare functions needed in DeathAnimation.cpp
*/

#ifndef DEATH_ANIMATION_H
#define DEATH_ANIMATION_H

#include "Animation.h"
using namespace std;

class DeathAnimation : public Animation 
{
public:
    void play(); // Override play method
};

#endif
