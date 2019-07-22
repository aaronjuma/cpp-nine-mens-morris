#ifndef BOARDMANAGEMENT_H_
#define BOARDMANAGEMENT_H_
#include <iostream>
using namespace std;

const int maxRows = 7;
const int maxColumns = 7;
const char h = '-';
const char v = '|';
const char p = 'O';
const char s = ' ';
const char empty = char(32);
const int boardLength = 13;
const int maxMillRows = 16;
int xPieces;
int zPieces;

//Board Setup
char Board[maxRows][maxColumns] =
{
    /*1*/   /*2*/   /*3*/   /*4*/   /*5*/   /*6*/   /*7*/
    {'O',   empty,  empty,  'O',    empty,  empty,  'O'     },  /*A*/
    {empty, 'O',    empty,  'O',    empty,  'O',    empty   },  /*B*/
    {empty, empty,  'O',    'O',    'O',    empty,  empty   },  /*C*/
    {'O',   'O',    'O',    empty,  'O',    'O',    'O'     },  /*D*/
    {empty, empty,  'O',    'O',    'O',    empty,  empty   },  /*E*/
    {empty, 'O',    empty,  'O',    empty,  'O',    empty   },  /*F*/
    {'O',   empty,  empty,  'O',    empty,  empty,  'O'     }   /*G*/
};

char * setpoints[24] = {
    &Board[0][0], //A1
    &Board[0][3], //A4
    &Board[0][6], //A7
    &Board[1][1], //B2
    &Board[1][3], //B4
    &Board[1][5], //B6
    &Board[2][2], //C3
    &Board[2][3], //C4
    &Board[2][4], //C5
    &Board[3][0], //D1
    &Board[3][1], //D2
    &Board[3][2], //D3
    &Board[3][4], //D5
    &Board[3][5], //D6
    &Board[3][6], //D7
    &Board[4][2], //E3
    &Board[4][3], //E4
    &Board[4][4], //E5
    &Board[5][1], //F2
    &Board[5][3], //F4
    &Board[5][5], //F6
    &Board[6][0], //G1
    &Board[6][3], //G4
    &Board[6][6], //G7
};

void setSlot(int slot, char piece)
{
    int actualSlot = slot-1;
    *setpoints[actualSlot] = piece;
}


char getSlot(int slot)
{
    if(slot == 0)
    {
        return empty;
    }
    int actualSlot = slot-1;
    return *setpoints[actualSlot];
}

void resetBoard()
{
    for(int currentPosition = 1;currentPosition<25;currentPosition++)
    {
        setSlot(currentPosition, 'O');
    }
}

int convertCoordsToInt(string coordinates)
{
    int intCoords;

    //Converts the first character in a char
    char vertical = coordinates[0];

    //Converts the second character into an int
    int horizontal = coordinates[1] - '0';

    /*
     * First it evaluates the vertical coordinate (the letter)
     * Then it evauluates the horizontal coordinate (the number)
     * it then sets the intCoords variable into a position on the board
     *  */
    if(vertical == 'a' || vertical == 'A')
    {
        switch(horizontal)
        {
            case 1:     intCoords = 1; break;
            case 4:     intCoords = 2; break;
            case 7:     intCoords = 3; break;
            default:    intCoords = 0; break;
        }
    }
    else if(vertical == 'b' || vertical == 'B')
    {
        switch(horizontal)
        {
            case 2:     intCoords = 4; break;
            case 4:     intCoords = 5; break;
            case 6:     intCoords = 6; break;
            default:    intCoords = 0; break;
        }
    }
    else if(vertical == 'c' || vertical == 'C')
    {
        switch(horizontal)
        {
            case 3:     intCoords = 7; break;
            case 4:     intCoords = 8; break;
            case 5:     intCoords = 9; break;
            default:    intCoords = 0; break;
        }
    }
    else if(vertical == 'd' || vertical == 'D')
    {
        switch(horizontal)
        {
            case 1:     intCoords = 10; break;
            case 2:     intCoords = 11; break;
            case 3:     intCoords = 12; break;
            case 5:     intCoords = 13; break;
            case 6:     intCoords = 14; break;
            case 7:     intCoords = 15; break;
            default:    intCoords = 0;  break;
        }
    }
    else if(vertical == 'e' || vertical == 'E')
    {
        switch(horizontal)
        {
            case 3:     intCoords = 16; break;
            case 4:     intCoords = 17; break;
            case 5:     intCoords = 18; break;
            default:    intCoords = 0;  break;
        }
    }
    else if(vertical == 'f' || vertical == 'F')
    {
        switch(horizontal)
        {
            case 2:     intCoords = 19; break;
            case 4:     intCoords = 20; break;
            case 6:     intCoords = 21; break;
            default:    intCoords = 0;  break;
        }
    }
    else if(vertical == 'g' || vertical == 'G')
    {
        switch(horizontal)
        {
            case 1:     intCoords = 22; break;
            case 4:     intCoords = 23; break;
            case 7:     intCoords = 24; break;
            default:    intCoords = 0;  break;
        }
    }
    return intCoords;
}


char secondaryBoard[13][19]=
{
    {getSlot(1), h, h, h, h, h, h, h, h, getSlot(2), h, h, h, h, h, h, h, h, getSlot(3)},
    {v, s, s, s, s, s, s, s, s, v, s, s, s, s, s, s, s, s, v},//Spacer
    {v, s, s, getSlot(4), h, h, h, h, h, getSlot(5), h, h, h, h, h, getSlot(6), s, s, v},
    {v, s, s, v, s, s, s, s, s, v, s, s, s, s, s, v, s, s, v},//Spacer
    {v, s, s, v, s, s, getSlot(7), h, h, getSlot(8), h, h, getSlot(9), s, s, v, s, s, v},
    {v, s, s, v, s, s, v, s, s, s, s, s, v, s, s, v, s, s, v},//Spacer
    {getSlot(10), h, h, getSlot(11), h, h, getSlot(12), s, s, s, s, s, getSlot(13), h, h, getSlot(14), h, h, getSlot(15)},
    {v, s, s, v, s, s, v, s, s, s, s, s, v, s, s, v, s, s, v},//Spacer
    {v, s, s, v, s, s, getSlot(16), h, h, getSlot(17), h, h, getSlot(18), s, s, v, s, s, v},
    {v, s, s, v, s, s, s, s, s, v, s, s, s, s, s, v, s, s, v},//Spacer
    {v, s, s, getSlot(19), h, h, h, h, h, getSlot(20), h, h, h, h, h, getSlot(21), s, s, v},
    {v, s, s, s, s, s, s, s, s, v, s, s, s, s, s, s, s, s, v},//Spacer
    {getSlot(22), h, h, h, h, h, h, h, h, getSlot(23), h, h, h, h, h, h, h, h, getSlot(24)}
};

void updateSecondaryBoard()
{
    /*--UPDATES THE ELEMENTS OF THE BOARD--*/
    //Row A
    secondaryBoard[0][0]    = getSlot(1);
    secondaryBoard[0][9]    = getSlot(2);
    secondaryBoard[0][18]   = getSlot(3);
    //Row B
    secondaryBoard[2][3]    = getSlot(4);
    secondaryBoard[2][9]    = getSlot(5);
    secondaryBoard[2][15]   = getSlot(6);
    //Row C
    secondaryBoard[4][6]    = getSlot(7);
    secondaryBoard[4][9]    = getSlot(8);
    secondaryBoard[4][12]   = getSlot(9);
    //Row D
    secondaryBoard[6][0]    = getSlot(10);
    secondaryBoard[6][3]    = getSlot(11);
    secondaryBoard[6][6]    = getSlot(12);
    secondaryBoard[6][12]   = getSlot(13);
    secondaryBoard[6][15]   = getSlot(14);
    secondaryBoard[6][18]   = getSlot(15);
    //Row E
    secondaryBoard[8][6]    = getSlot(16);
    secondaryBoard[8][9]    = getSlot(17);
    secondaryBoard[8][12]   = getSlot(18);
    //Row F
    secondaryBoard[10][3]   = getSlot(19);
    secondaryBoard[10][9]   = getSlot(20);
    secondaryBoard[10][15]  = getSlot(21);
    //Row G
    secondaryBoard[12][0]   = getSlot(22);
    secondaryBoard[12][9]   = getSlot(23);
    secondaryBoard[12][18]  = getSlot(24);
}


void print()
{
    //Prints out the board
    system("clear");
    char verticalCord = 'A';
    int counter = 0;
    
    cout << "\11   " << "1  2  3  4  5  6  7" << endl << endl; 
    for(int rows=0;rows<13;rows++)
    {
        if(rows%2==0)
        {
            cout << "\11" << verticalCord++ << "  ";
        }
        else
        {
            cout << "\11" << "  " << " ";
        }
        for(int columns=0; columns<19;columns++)
        {
            cout << secondaryBoard[rows][columns];
        }
        cout << endl;
    }
}

void pause()
{
    cout << "Press any button to continue..";
    cin.get();
}

void clearConsole()
{
    system("clear");
}

enum Player 
{
    X = 0,
    Z = 1
};










/*
 * ####################################
 * ########## MILL CONTROL ############
 * ####################################
 */
char * millOwner = new char[maxRows];

int mills[maxMillRows][3] = 
{
    /*OUTER ROWS*/
    {1, 2, 3}, //TOP OUTER ROW
    {1, 10, 22}, //LEFT OUTER COLUMN
    {22, 23, 24}, //BOTTOM OUTER ROW
    {3, 15, 24}, //RIGHT OUTER COLUMN
    /*MIDDLE ROWS*/
    {4, 5, 6}, //MIDDLE TOP ROW
    {4, 11, 19}, //MIDDLE LEFT COLUMN
    {19, 20, 21}, //MIDDLE BOTTOM ROW
    {6, 14, 21}, //MIDDLE RIGHT COLUMN
    /*INNER ROWS*/
    {7, 8, 9}, //INNER TOP ROW
    {7, 12, 16}, //INNTER LEFT COLUMN
    {16, 17, 18}, // INNER BOTTOM ROW
    {9, 13, 18}, //INNER RIGHT COLUMN
    /*MIDDLES*/
    {2, 5, 8}, //TOP MIDDLE
    {10, 11, 12}, //LEFT MIDDLE
    {17, 20, 23}, //BOTTOM MIDDLE
    {13, 14, 15}, //RIGHT MIDDLE

};

bool millCheck[maxRows];

void resetMillChecks()
{
    //Sets all the elements in the array to false
    for(int counter=0;counter<maxRows;counter++)
    {
        millCheck[counter] = false;
    }
}









/*
 * ####################################
 * ###### ADJACENT SPOT CONTROL #######
 * ####################################
 */
int adjacentSpots[25][5] = { 
    /*
     * First Element: Left Adjacent Spot
     * Second Element: Top Adjacent Spot
     * Third Element: Right Adjacent Spot
     * Fourth Element: Bottom Adjacent Spot
     * The array is dependant on the position (ex. the adjacent spots for position 1 is array 1)
     * 0 means invalid
     * The first array is 0 so the the array 1 is the real first row
     */
    {0, 0, 0, 0},
    {0, 0, 2, 10},      //Position: 1
    {1, 0, 3, 5},       //Position: 2 
    {2, 0, 0, 15},      //Position: 3
    {0, 0, 5, 11},      //Position: 4
    {4, 2, 6, 8},       //Position: 5
    {5, 0, 0, 14},      //Position: 6
    {0, 0, 8, 12},      //Position: 7
    {7, 5, 9, 0},       //Position: 8
    {8, 0, 0, 13},      //Position: 9
    {0, 1, 11, 22},     //Position: 10
    {10, 4, 12, 19},    //Position: 11
    {11,7, 0, 16},      //Position: 12
    {0, 9, 14, 18},     //Position: 13
    {13, 6, 15, 21},    //Position: 14
    {14, 3, 0, 24},     //Position: 15
    {0, 12, 17, 0},     //Position: 16
    {16, 0, 18, 20},    //Position: 17
    {17, 13, 0, 0},     //Position: 18
    {0, 11, 20, 0},     //Position: 19
    {19, 17, 21, 23},   //Position: 20
    {20, 14, 0, 0},     //Position: 21
    {0, 10, 23, 0},     //Position: 22
    {22, 20, 24, 0},    //Position: 23
    {23, 15, 0, 0}      //Position: 24
};



bool areTheyAdjacent(string currentPosition, string desiredPosition)
{
    bool returnValue = false;
    int currentNum = convertCoordsToInt(currentPosition);
    int desiredNum = convertCoordsToInt(desiredPosition);

    for(int adjacentCounter = 0;adjacentCounter<4;adjacentCounter++)
    {
        if(adjacentSpots[currentNum][adjacentCounter] == desiredNum)
        {
            returnValue = true;
            break;
        }
    }

    return returnValue;
}


#endif
