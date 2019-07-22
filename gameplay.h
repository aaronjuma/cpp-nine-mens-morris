#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_
#include <iostream>
#include "gameControl.h"
using namespace std;


/* #######################
 * ######### MENU  ####### 
 * #######################
 */
enum GameStatus
{
    Play,
    Tutorial,
    Exit
};

GameStatus menu()
{
    cout << "Welcome to C++ Malom!" << endl;
    cout << "*********************" << endl;
    cout << "1. Play the game" << endl;
    cout << "2. Tutorial" << endl;
    cout << "3. Exit" << endl;

    bool inputStatus = false;
    string input;
    int option;
    GameStatus returnOption;
    bool alreadyPrintedOption = true;

    while(inputStatus == false)
    {
        if(alreadyPrintedOption == true)
        {
            alreadyPrintedOption = false;
        } 
        else
        {
            clearConsole();
            cout << "Welcome to C++ Malom!" << endl;
            cout << "*********************" << endl;
            cout << "1. Play the game" << endl;
            cout << "2. Tutorial" << endl;
            cout << "3. Exit" << endl;
            cout << endl << "Invalid Option" << endl;
        }
        
        cout << endl << "Please enter an option: ";
        getline(cin, input);
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inputStatus = false;
        }
        else
        {
            //Checks if it is more than 1 character
            if(input[1] != char(0) || !isdigit(input[0]))
            {
                inputStatus = false;
            }
            else
            {
                //Converts the char into an int
                option = input[0] - '0';
                if(option == 1)
                {
                    returnOption = Play;
                    inputStatus = true;
                    break;
                }
                else if(option == 2)
                {
                    returnOption = Tutorial;
                    inputStatus = true;
                    break;
                }
                else if(option == 3)
                {
                    returnOption = Exit;
                    inputStatus = true;
                    break;
                }
                else
                {
                    inputStatus = false;
                }
            }
        }
    }
    return returnOption;
}


/* ###########################
 * ######### TUTORIAL  ####### 
 * ###########################
 */
void gameTutorial()
{
	clearConsole();
	cout << "Malom is a board game for two players." << endl;
	pause();
	cout <<  endl << endl << "Players take turns to place their piece onto the empty spots on the board." << endl;
	cout << "If you form a line of 3 pieces, you can remove an enemy piece on a board" << endl;
	pause();
	cout << endl << endl << "There is a winner once the other person cannot make a legal move " << endl;
	cout << "OR if they have less than 3 pieces on the board." << endl;
	pause();
}




/* #######################
 * ####### GAMEPLAY ###### 
 * #######################
 */
Player player_1;
Player player_2;

void gameIntroduction() 
{
    cout << "Welcome to Malom!" << endl;
    pause();
    clearConsole();
    cout << "We will flip a coin to see what Player One would like to play as: " << endl;
    pause();
    srand(time(0));
    int randNum = (rand() % 2) + 1;
    if(randNum == 1)
    {
        cout << "Player One will be X" << endl;
        cout << "Player Two will be Z" << endl;
        player_1 = X;
        player_2 = Z;
    }
    else
    {
        cout << "Player One will be Z" << endl;
        cout << "Player Two will be X" << endl;
        player_1 = Z;
        player_2 = X;
    }
    pause();
}


void gamePlay()
{
    
    int maxTurns = 18;
    int game = 0; //variable to check if they would like to play agaim
    Player winner;

    resetMillChecks();
    
    do
    {
        resetBoard();
        xPlaceablePieces = 9;
        zPlaceablePieces = 9;
        xPieces = 0;
        zPieces = 0;

        /*--PLACING PHASE--*/
        while(xPlaceablePieces != 0 && zPlaceablePieces != 0)
        {
            updateSecondaryBoard();
            checkForRow(Z);
            placingStones(X);
            updateSecondaryBoard();
            checkForRow(X);
            xPlaceablePieces--;

            updateSecondaryBoard();
            checkForRow(X);
            placingStones(Z);
            updateSecondaryBoard();
            checkForRow(Z);
            zPlaceablePieces--;
        }
        
        /*--SLIDING/JUMPUNG PHASE--*/
        while(xPieces > 3 || zPieces > 3)
        {
            /*--X STONE SLIDER/JUMPER--*/
            if(xPieces < 3)
            {
                winner == Z;
                break;
            }
            //If the pieces are greater than 3
            if(xPieces > 3)
            {
                updateSecondaryBoard();

                //Checks if there is a valid spot
                if(checkValidSpots(X) == false)
                {
                    winner == Z;
                    break;
                }

                slideStone(X);
                updateSecondaryBoard();
                checkForRow(X);
            }
            //If the pieces are equal to 3
            else
            {
                updateSecondaryBoard();
                jumpStone(X);
                updateSecondaryBoard();
                checkForRow(X);
            }
            


            /*--Z STONE SLIDER/JUMPER--*/
            //Checks if the pieces are less than 3 so that it doesnt run the other code
            if(zPieces < 3)
            {
                winner == X;
                break;
            }
            //If the pieces are greater than 3
            if(zPieces > 3)
            {
                updateSecondaryBoard();

                //Checks if there is a valid spot
                if(checkValidSpots(X) == false)
                {
                    winner == Z;
                    break;
                }

                slideStone(Z);
                updateSecondaryBoard();
                checkForRow(Z);
            }
            //If the pieces are equal to 3
            else
            {
                updateSecondaryBoard();
                jumpStone(Z);
                updateSecondaryBoard();
                checkForRow(Z);
            }
        }

        if(winner == X)
        {
            print();
            cout << "X WINS" << endl;
            pause();
        }
        else if(winner == Z)
        {
            print();
            cout << "Z WINS" << endl;
            pause();
        }
        

    } while (game == 0);
}





/* #######################
 * ####### GOODBYE  ###### 
 * #######################
 */

void printGoodBye()
{
    clearConsole();
    cout << "Thank You for Playing!" << endl;
    cout << "Hope to see you again!" << endl;
}


#endif
