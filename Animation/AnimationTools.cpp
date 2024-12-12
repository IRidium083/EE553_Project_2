/* Author: David
Date: Dec 2024
Description: Functions that help create animation
*/

#include "AnimationTools.h"

void clearScreen() {
#ifdef _WIN32
    system("cls"); // Windows clear screen
#else
    system("clear"); // Unix/MacOS clear screen
#endif
}

void delay(int milliseconds) 
{
    this_thread::sleep_for(chrono::milliseconds(milliseconds)); // Delay execution
}

void gradualPrint(const string& text, int delayPerChar) 
{
    for (char c : text) 
    {
        cout << c << flush; // Print each character and flush output
        delay(delayPerChar); // Delay for typing effect
    }
    cout << endl;
}
