#include <iostream>
#include "gameplay.h"
using namespace std;

int main()
{
    bool programStatus = false;

    /*
     * This do-while loop will loop until the user 
     * asks to exit while in the menu
     */
    do
    {
        clearConsole();
        //Menu 
        GameStatus gameStatus = menu();
        /*
         * Actual Gameplay
         */
        if(gameStatus == Play)
        {
            clearConsole();
            gamePlay();
        }

        /*
         * Tutorial
         */
        else if(gameStatus == Tutorial)
        {
            clearConsole();
            gameTutorial();
        }

        /*
         * Exit
         */
        else if(gameStatus == Exit)
        {
            programStatus = true;
            break;
        }


    } while(programStatus == false);
    
    printGoodBye();
    pause();
    system("clear");
    cout << endl << endl;
    return 0;
}