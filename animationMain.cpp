#include "Animation/OpeningAnimation.h"
#include "Animation/VictoryAnimation.h"
#include "Animation/AnimationTools.h"
#include "Animation/DeathAnimation.h"

int main() 
{
    // Play the opening animation
    OpeningAnimation opening;
    opening.play();

    // Simulate the game process
    cout << "The game is ongoing..." << endl;
    delay(2000);

    // Play the ending animation
    VictoryAnimation ending;
    ending.play();

    // Play the dead animation
    DeathAnimation deathending;
    deathending.play();

    return 0; // End the program
}


