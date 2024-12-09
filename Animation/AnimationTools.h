#ifndef ANIMATION_TOOLS_H
#define ANIMATION_TOOLS_H

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

// Function declarations
void clearScreen(); // Clear the console screen
void delay(int milliseconds); // Delay execution for a given time in milliseconds
void gradualPrint(const string& text, int delayPerChar); // Print text gradually

#endif // ANIMATION_TOOLS_H
