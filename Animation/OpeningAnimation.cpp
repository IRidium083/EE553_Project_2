/* Author: David
Date: Dec 2024
Description: Functions that create opening animation
*/

#include "OpeningAnimation.h"
#include "AnimationTools.h" // Includes utility functions

void OpeningAnimation::play() 
{
    clearScreen(); // Clear the console screen for a fresh display
    gradualPrint("========== Welcome to the Maze Game ==========", 50); // Print the title with a typing animation
    delay(500); // Short delay for dramatic effect
    gradualPrint("This game is created by YenJun,Tsui and YiHan,Huang", 50);
    delay(500); // Short delay for dramatic effect
    gradualPrint("A mysterious maze awaits you...", 50); // Print the introduction text
    delay(1000); // Delay before the animation begins

    // Display the warrior approaching the maze entrance animation
    for (int step = 0; step < 20; step++) 
    {
        clearScreen(); // Clear the screen before displaying each frame

         // Draw the maze entrance (fixed far right position)
        cout << "                              ###########" << endl; 
        cout << "                              #         #" << endl;
        cout << "                              #         #" << endl;
        cout << "                              #         #" << endl;
        cout << "                              ###########" << endl;

        // Draw the warrior moving closer horizontally
        cout << string(step * 2, ' ') << "  O" << endl; // Head
        cout << string(step * 2, ' ') << " /|\\" << endl; // Body
        cout << string(step * 2, ' ') << " / \\" << endl; // Legs

        delay(200); // Delay to create animation effect
    }

    // Final static display: Warrior at the entrance
    clearScreen();
    cout << string(30, ' ') << "###########" << endl;
    cout << string(30, ' ') << "#         #" << endl;
    cout << string(30, ' ') << "#   O     #" << endl;
    cout << string(30, ' ') << "#  /|\\    #" << endl;
    cout << string(30, ' ') << "#  / \\    #" << endl;
    cout << string(30, ' ') << "###########" << endl;

    gradualPrint("The warrior has reached the entrance!", 100);
    delay(1000);
    clearScreen();
    gradualPrint("Let the adventure begin!", 100);
    delay(1000);
}


