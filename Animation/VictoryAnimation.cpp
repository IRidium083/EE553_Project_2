#include "VictoryAnimation.h"
#include "AnimationTools.h" // Includes utility functions

// Implementation of the ending animation
void VictoryAnimation::play() 
{
    clearScreen(); // Clear the console screen for a fresh display
    gradualPrint("========== The Maze is Conquered ==========", 50); // Print the ending title with a typing animation
    delay(500); // Short delay for dramatic effect
    gradualPrint("The warrior is leaving the maze victorious...", 50); // Print the description text
    delay(1000); // Short delay for dramatic effect
    
    // Display the warrior leaving the maze animation
    for (int step = 20; step >= 0; step--) // Loop for the animation
    {
        clearScreen(); // Clear the screen before displaying each frame

        // Draw the maze entrance
        cout << "                              ###########" << endl; 
        cout << "                              #         #" << endl;
        cout << "                              #         #" << endl;
        cout << "                              #         #" << endl;
        cout << "                              ###########" << endl;

        // Draw the warrior moving further away horizontally
        cout << string(step * 2, ' ') << "  O" << endl; // Head
        cout << string(step * 2, ' ') << " /|\\" << endl; // Body
        cout << string(step * 2, ' ') << " / \\" << endl; // Legs

        delay(200); // Delay between frames to create animation effect
    }

    // Display the ending message
    clearScreen(); // Clear the screen for the final message
    gradualPrint("Thank you for playing the Maze Game!", 100); // Display gratitude message
    delay(1000); // Short pause
    gradualPrint("See you next time!", 100); // Final goodbye message
    delay(1000); // Short pause before exiting
}
