#ifndef GAMECONTROL_H_
#define GAMECONTROL_H_
#include "boardManagement.h"
#include <iostream>
using namespace std;

int xPlaceablePieces = 9;
int zPlaceablePieces = 9;




/*
 * ####################################
 * #########  PLACING STONES  #########
 * ####################################
 */
void placingStones(Player piece)
{
    print();
    string input;
    bool status = true;
    int placeablePieces = (piece == X) ? xPlaceablePieces:zPlaceablePieces;
    int currentPieces = (piece == X) ? xPieces:zPieces;
    while(status == true)
    {

        //Tells who is inputting
        (piece == X) ? cout << "X Turn: " << endl:cout << "Z Turn: " << endl;

        cout << "Available pieces: " << placeablePieces << endl;
        cout << "Pieces on the board" << currentPieces << endl;
        cout << "Enter coordinates (ex. a1): ";
        //Gets input
        getline(cin, input);

        //If input fails
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            print();
            cout << "Invalid Input!" << endl;
            status = true;
        }
        
        //If the 3rd element is something other than null
        else if(input[2] != char(0))
        {
            print();
            cout << "Invalid Input!" << endl;
            status = true;
        }
        //If everthing so far is Valid
        else 
        {
            if(!isdigit(input[1]))
            {
                print();
                cout << "Invalid Input!" << endl;
                status = true;
            }
            else
            {
                //Sets up the variables for each element of the input
                char vertical = input[0];
                int horizontal = input[1] - '0';

                /*--CHECKS FIRST ELEMENT--*/
                bool isCapital;
                if((vertical >= char('a') && vertical <= char('g')))
                {
                    isCapital = false;
                }
                else if((vertical >= char('A') && vertical <= char('G')))
                {
                    isCapital = true;
                }
                else
                {
                    print();
                    cout << "Invalid Input!" << endl;
                    status = true;
                }


                /*--CHECKS SECOND ELEMENT--*/
                if(horizontal<=7 && horizontal>=1)
                {
                    //Really nothing to put down here
                }
                else
                {
                    print();
                    cout << "Invalid Input!" << endl;
                    status = true;
                }
                
                /*--PLACING THE PIECE--*/

                int letter_number;
                //This turns the vertical into a number
                if(isCapital == false)
                {
                    letter_number = (int(vertical)-97);
                } 
                else
                {
                    letter_number = (int(vertical)-65);
                }

                //Checks if the spot is not taken or a valid space
                if(Board[letter_number][horizontal-1] != 'O')
                {
                    print();
                    cout << "Invalid Input!" << endl;
                    status = true;
                }
                else
                {
                    Board[letter_number][horizontal-1] = (piece == X) ? 'X':'Z';
                    
                    //Increments player's piece
                    if(piece == X)
                    {
                        xPieces++;
                    }
                    else
                    {
                        zPieces++;
                    }
                    
                    status = false;
                    break;
                }
            }
        }
        
    }
}












/*
 * ####################################
 * ##########  ROW CHECKER   ##########
 * ####################################
 */
void checkForRow(Player player)
{
    bool foundRow = false;
    char playerPiece = (player == X)?'X':'Z';
    
    //Checks each possible mill
    for(int currentRow=0;currentRow < maxMillRows;currentRow++)
    {
        //If it is not a mill already
        if(millCheck[currentRow] == false)
        {
            //Checks the slots of each row
            if( (getSlot(mills[currentRow][0])  == playerPiece) &&
                (getSlot(mills[currentRow][1])  == playerPiece) &&
                (getSlot(mills[currentRow][2])  == playerPiece))
            {
                //If there is a row, it sets the millCheck of that row to true
                //And sets the owner of the millOwner to avoid confusion on who owned it
                millCheck[currentRow] = true;
                millOwner[currentRow] = playerPiece;
                foundRow = true;
                break;
            }
        }
        //If it is a mill
        else
        {
            //Checks if the mill is still intact
            if( (getSlot(mills[currentRow][0])  != millOwner[currentRow]) ||
                (getSlot(mills[currentRow][1])  != millOwner[currentRow]) ||
                (getSlot(mills[currentRow][2])  != millOwner[currentRow]))
            {
                //Sets the millCheck to false and is no longer a mill
                millCheck[currentRow] = false;
                foundRow = false;
            }
        }
        
    }

    //If the program has found a new row
    if(foundRow == true)
    {
        print();
        string input;
        bool status = true;

        while(status == true)
        {
            cout << playerPiece << " has made a mill and gets to remove a piece! " << endl;
            cout << "Enter coordinates of piece to take off (ex. a1): ";
            //Gets input
            getline(cin, input);

            //If input fails
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                print();
                cout << "Invalid Input!" << endl;
                status = true;
            }
            
            //If the 3rd element is something other than null
            else if(input[2] != char(0))
            {
                print();
                cout << "Invalid Input!" << endl;
                status = true;
            }
            else if(!isdigit(input[1]))
            {
                print();
                cout << "Invalid Input!" << endl;
                status = true;
            }
            //If everthing so far is Valid
            else 
            {
                //Sets up the variables for each element of the input
                int horizontal = input[1] - '0';

                /*--CHECKS FIRST ELEMENT--*/
                if((input[0] >= 'A' && input[0] <= 'G') || (input[0] >= 'a' && input[0] <= 'g'))
                {
                    if(horizontal<=7 && horizontal>=1)
                    {
                        int desiredPosition = convertCoordsToInt(input);
                        if(desiredPosition == 0)
                        {
                            print();
                            cout << "Invalid Spot!" << endl;
                            status = true;
                        }
                        else if(getSlot(desiredPosition) == playerPiece)
                        {
                            print();
                            cout << "Invalid Spot!" << endl;
                            status = true;
                        }
                        else if(getSlot(desiredPosition) == 'O')
                        {
                            print();
                            cout << "Invalid Spot!" << endl;
                            status = true;
                        }
                        else
                        {
                            setSlot(desiredPosition, 'O');

                            //Decrements the opposite player's peices
                            if(playerPiece == 'X')
                            {
                                zPieces--;
                            }
                            else
                            {
                                xPieces--;
                            }
                            status = false;
                            break;
                        }
                    }
                    //If the number is not in the range
                    else
                    {
                        print();
                        cout << "Invalid Input!" << endl;
                        status = true;
                    }
                }
                //If the letter is not in the range
                else
                {
                    print();
                    cout << "Invalid Input!" << endl;
                    status = true;
                }
            }
        }
    }
}






/*
 * ####################################
 * ##########  STONE SLIDER  ##########
 * ####################################
 */
void slideStone(Player player)
{
    print();

    //Variable declaration and assignments
    char piece = (player == X) ? 'X':'Z';
    string coordinates;
    string secondCoord;
    int firstPos;
    int secondPos;
    bool inputStatus = false;
    bool firstInput = false;
    bool secondInput = false;

    //Loops until the first input is successful
    while(firstInput == false)
    {
        //Asks user for input
        cout << piece << " Enter the rock you would like to move (ex a1): ";
        getline(cin, coordinates);
        
        //If input failed or if the third element is invalid
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    
            print();
            cout << "Invalid Input!" << endl;
            firstInput = false;
            inputStatus = false;
        }
        else if(coordinates[2] != char(0))
        {
            print();
            cout << "Invalid Input!" << endl;
            firstInput = false;
            inputStatus = false;
        }
        else
        {
            //Checks if the vertical coordinate is valid
            if((coordinates[0] >= 'A' && coordinates[0] <= 'G') || (coordinates[0] >= 'a' && coordinates[0] <= 'g'))
            {
                //Converts char to int
                int vertical = coordinates[1] - '0';

                //Checks if the horizontal coordinate is valid
                if(vertical >= 1 && vertical <= 7)
                {
                    //Checks the slot if it is valid
                    firstPos = convertCoordsToInt(coordinates);
                    if(getSlot(firstPos) != piece)
                    {
                        print();
                        cout << "Invalid Coordinate!" << endl;
                        firstInput = false;
                        inputStatus = false;
                    }
                    //If Slot is valid
                    else
                    {
                        print();
                        while(secondInput == false)
                        {
                            //Asks user where to place their rock
                            cout << "Currently Selected Coordinate: " << coordinates << endl;
                            cout << "Enter X to deselect rock." << endl;
                            cout << "Enter the coordinate where you would like to slide your rook: ";
                            getline(cin, secondCoord);

                            //If input fails or if input is invalid or if user inputted X
                            if(cin.fail())
                            {   
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');    
                                print();
                                cout << "Invalid Input!" << endl;
                                secondInput = false;
                            }
                            else if(secondCoord[2] != char(0))
                            {
                                print();
                                cout << "Invalid Input!" << endl;
                                secondInput = false;
                            }
                            else if(secondCoord == "X" || secondCoord == "x")
                            {
                                print();
                                cout << "Deselected Rock!" << endl;
                                firstInput = false;
                                break;
                            }
                            //If input is valid
                            else
                            {
                                //Checks the characters of the coordinates
                                if((coordinates[0] >= 'A' && coordinates[0] <= 'G') || (coordinates[0] >= 'a' && coordinates[0] <= 'g'))
                                {
                                    //Converts char into int
                                    int vertical_2 = coordinates[1] - '0';

                                    //Checks if the horizontal coordinate is valid
                                    if(vertical_2 >= 1 && vertical_2 <= 7)
                                    {
                                        //Checks if the slot is valid 
                                        secondPos = convertCoordsToInt(secondCoord);
                                        if(getSlot(secondPos) != 'O') 
                                        {
                                            print();
                                            cout << "Invalid Coordinate!" << endl;
                                            secondInput = false;
                                            inputStatus = false;
                                        }
                                        //If slot is valid
                                        else
                                        {
                                            //Checks if both coordinates are adjacent
                                            bool validOption = areTheyAdjacent(coordinates, secondCoord);
                                            if(validOption == true)
                                            {
                                                //Sets the previous slot to empty and sets the desired slot to the piece
                                                setSlot(firstPos, 'O');
                                                setSlot(secondPos, piece);
                                                //Loop enders
                                                secondInput = true;
                                                firstInput = true;
                                                inputStatus = true;
                                                break;
                                            }
                                            //If not
                                            else
                                            {
                                                print();
                                                cout << "Invalid Slot!" << endl;
                                                secondInput = false;
                                                inputStatus = false;
                                            }
                                        }
                                    }
                                    //If number in coordinate is invalid
                                    else
                                    {
                                        print();
                                        cout << "Invalid Input!" << endl;
                                        secondInput = false;
                                        firstInput = false;
                                        inputStatus = false;
                                    }
                                    
                                }
                                //If letter in coordinate is invalid
                                else
                                {
                                    print();
                                    cout << "Invalid Input!" << endl;
                                    secondInput = false;
                                    firstInput = false;
                                    inputStatus = false;
                                }
                            }
                        }
                    }
                }
                //If number in coordinate is invalid
                else
                {
                    print();
                    cout << "Invalid Input!" << endl;
                    firstInput = false;
                    inputStatus = false;
                }
            }
            //If letter in coordinate is invalid
            else
            {
                print();
                cout << "Invalid Input!" << endl;
                firstInput = false;
                inputStatus = false;
            }
        }//End of else
    } //End of firstInput loop
} //End of function







/*
 * ####################################
 * ##########  STONE JUMPER  ##########
 * ####################################
 */
void jumpStone(Player player)
{
    print();

    //Variable declaration and assignments
    char piece = (player == X) ? 'X':'Z';
    string coordinates;
    string secondCoord;
    int firstPos;
    int secondPos;
    bool inputStatus = false;
    bool firstInput = false;
    bool secondInput = false;

    //Loops until the first input is successful
    while(firstInput == false)
    {
        //Asks user for input
        cout << piece << " Enter the rock you would like to move (ex a1): ";
        getline(cin, coordinates);
        
        //If input failed or if the third element is invalid
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    
            print();
            cout << "Invalid Input!" << endl;
            firstInput = false;
            inputStatus = false;
        }
        else if(coordinates[2] != char(0))
        {
            print();
            cout << "Invalid Input!" << endl;
            firstInput = false;
            inputStatus = false;
        }
        else
        {
            //Checks if the vertical coordinate is valid
            if((coordinates[0] >= 'A' && coordinates[0] <= 'G') || (coordinates[0] >= 'a' && coordinates[0] <= 'g'))
            {
                //Converts char to int
                int vertical = coordinates[1] - '0';

                //Checks if the horizontal coordinate is valid
                if(vertical >= 1 && vertical <= 7)
                {
                    //Checks the slot if it is valid
                    firstPos = convertCoordsToInt(coordinates);
                    if(getSlot(firstPos) != piece)
                    {
                        print();
                        cout << "Invalid Coordinate!" << endl;
                        firstInput = false;
                        inputStatus = false;
                    }
                    //If Slot is valid
                    else
                    {
                        print();
                        while(secondInput == false)
                        {
                            //Asks user where to place their rock
                            cout << "Currently Selected Coordinate: " << coordinates << endl;
                            cout << "Enter X to deselect rock." << endl;
                            cout << "You have 3 pieces left! You can place your rock in any empty spots on the board." << endl;
                            cout << "Enter the coordinate where you would like to slide your rook: ";
                            getline(cin, secondCoord);

                            //If input fails or if input is invalid or if user inputted X
                            if(cin.fail())
                            {   
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');    
                                print();
                                cout << "Invalid Input!" << endl;
                                secondInput = false;
                            }
                            else if(secondCoord[2] != char(0))
                            {
                                print();
                                cout << "Invalid Input!" << endl;
                                secondInput = false;
                            }
                            else if(secondCoord == "X" || secondCoord == "x")
                            {
                                print();
                                cout << "Deselected Rock!" << endl;
                                firstInput = false;
                                break;
                            }
                            //If input is valid
                            else
                            {
                                //Checks the characters of the coordinates
                                if((coordinates[0] >= 'A' && coordinates[0] <= 'G') || (coordinates[0] >= 'a' && coordinates[0] <= 'g'))
                                {
                                    //Converts char into int
                                    int vertical_2 = coordinates[1] - '0';

                                    //Checks if the horizontal coordinate is valid
                                    if(vertical_2 >= 1 && vertical_2 <= 7)
                                    {
                                        //Checks if the slot is valid 
                                        secondPos = convertCoordsToInt(secondCoord);
                                        if(getSlot(secondPos) != 'O') 
                                        {
                                            print();
                                            cout << "Invalid Coordinate!" << endl;
                                            secondInput = false;
                                            inputStatus = false;
                                        }
                                        //If slot is valid
                                        else
                                        {
                                            //Checks if second coordinate is empty
                                            if(getSlot(secondPos) == 'O')
                                            {
                                                //Sets the previous slot to empty and sets the desired slot to the piece
                                                setSlot(firstPos, 'O');
                                                setSlot(secondPos, piece);
                                                //Loop enders
                                                secondInput = true;
                                                firstInput = true;
                                                inputStatus = true;
                                                break;
                                            }
                                            //If not
                                            else
                                            {
                                                print();
                                                cout << "Invalid Slot!" << endl;
                                                secondInput = false;
                                                inputStatus = false;
                                            }
                                        }
                                    }
                                    //If number in coordinate is invalid
                                    else
                                    {
                                        print();
                                        cout << "Invalid Input!" << endl;
                                        secondInput = false;
                                        firstInput = false;
                                        inputStatus = false;
                                    }
                                    
                                }
                                //If letter in coordinate is invalid
                                else
                                {
                                    print();
                                    cout << "Invalid Input!" << endl;
                                    secondInput = false;
                                    firstInput = false;
                                    inputStatus = false;
                                }
                            }
                        }
                    }
                }
                //If number in coordinate is invalid
                else
                {
                    print();
                    cout << "Invalid Input!" << endl;
                    firstInput = false;
                    inputStatus = false;
                }
            }
            //If letter in coordinate is invalid
            else
            {
                print();
                cout << "Invalid Input!" << endl;
                firstInput = false;
                inputStatus = false;
            }
        }//End of else
    } //End of firstInput loop
} //End of function




bool checkValidSpots(Player player)
{
    char piece = (player == X) ? 'X':'Z';
    bool validSpots = false;
    for(int currentSlot = 1;currentSlot<25;currentSlot++)
    {
        if(getSlot(currentSlot) == piece)
        {
            for(int adjacentSlot = 0; adjacentSlot < 4; adjacentSlot++)
            {
                if(getSlot(adjacentSpots[currentSlot][adjacentSlot]) == 'O')
                {
                    validSpots = true;
                }
            }
        }
    }
    return validSpots;
}













/*
 * ####################################
 * ############  WIN CHECK ############
 * ####################################
 */
int checkForWinner()
{
    // /*
    //  * Checks for winner
    //  * 0 = nobody
    //  * 1 = X
    //  * 2 = Z
    //  */
    // int winner = 0;


    // /*--CHECKING FOR PIECES--*/
    // if(xCurrentPieces > 3)
    // {
    //     winner = 1;
    // }

    // if(zCurrentPieces > 3)
    // {
    //     winner = 2;
    // }


    // /*--CHECKING FOR VALID MOVES--*/
    // for(int xPieces = 0; xPieces < xCurrentPieces; xPieces++)
    // {
        
    // }
    // return winner;
}
#endif
