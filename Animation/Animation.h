#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <string>

using namespace std;

// Abstract Base Class
class Animation 
{
public:
    virtual void play() = 0; // Pure virtual function, must be implemented by derived classes
    virtual ~Animation() {}  // Virtual destructor to prevent memory leaks when deleting derived objects
};

#endif

