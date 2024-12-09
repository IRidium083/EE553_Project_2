#include "DeathAnimation.h"
#include "AnimationTools.h" // Includes utility functions

void DeathAnimation::play()
{
    clearScreen(); // Clear the screen for a fresh display

    // Display a dramatic "Game Over" with flashing effect
    for (int i = 0; i < 3; i++) 
    {
        clearScreen();
        if (i % 2 == 0) 
        {
            cout << R"(
  ██████  █████  ███    ███ ███████     ███████ ██     ██  ███████ ██████  
 ██      ██   ██ ████  ████ ██          ██   ██ ██     ██  ██      ██   ██ 
 ██  ███ ███████ ██ ████ ██ █████       ██   ██  ██   ██   █████   ██████  
 ██   ██ ██   ██ ██  ██  ██ ██          ██   ██   ██ ██    ██      ██   ██ 
  ██████ ██   ██ ██      ██ ███████     ███████    ███     ███████ ██   ██ 
)" << endl;
        }
        delay(500); // Pause for flashing effect
    }

    // Gradual print the dramatic death message
    gradualPrint("Oh no! You died in the maze.", 70);
    delay(500);
    gradualPrint("Better luck next time!", 70);

    // Play the warrior collapsing animation
    clearScreen();
    cout << "You're dead..." << endl;
    delay(200);
    cout << R"(
     O
    /|\
    / \
    )" << endl; // The warrior starts upright
    delay(300);

    clearScreen();
    cout << "You're dead..." << endl;
    delay(200);
    cout << R"(
     O
     |
    / \
    )" << endl; // The warrior loses their arms
    delay(300);

    clearScreen();
    cout << "You're dead..." << endl;
    delay(200);
    cout << R"(
     O
     |
     /
    )" << endl; // The warrior collapses further
    delay(300);

    clearScreen();
    cout << "You're dead..." << endl;
    delay(200);
    cout << R"(
     O
     |
    )" << endl; // The warrior collapses further
    delay(300);

    clearScreen();
    cout << "You're dead..." << endl;
    delay(200);
    cout << R"(
     O
    )" << endl; // The warrior collapses further
    delay(300);

    clearScreen();
    cout << "You're dead..." << endl;
    delay(200);
    cout << R"(
    )" << endl; // The warrior collapses further
    delay(300);
    

    // Final static screen with "Try Again" message
    clearScreen();
    cout << R"(
   ████████ ██████  ██    ██          █████   ████████   █████   ████████  ██████  ██    ██
      ██    ██   ██ ██    ██         ██   ██  ██        ██   ██  ██          ██    ███   ██
      ██    ██████   ██████         █████████ ██  ████ █████████ ██  ████    ██    ██ ██ ██
      ██    ██   ██    ██           ██     ██ ██    ██ ██     ██ ██    ██    ██    ██   ███
      ██    ██   ██    ██           ██     ██ ████████ ██     ██ ████████  ██████  ██    ██
)" << endl;
    gradualPrint("Press any key to try again!", 100); // Prompt user to restart
    delay(1000);
}
