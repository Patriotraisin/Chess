/* pieces key:
 * empty = 0
 * pawn = 1
 * bishop = 2
 * knight = 3
 * rook = 4
 * queen = 5
 * king = 6
 */

// set monospace font

#define MOVES 3


#include <iostream>
#include <string>
#include <cctype>

#include "Piece.hpp"
#include "pgnFile.hpp"
#include "Chessboard.hpp"
#include "Player.hpp"

using namespace std;

// global variable chessboard; other variables
Chessboard CB;
int moveCounter = 1;

//functions
inline bool MOVELIMITREACHED();

// main function
int main() {
    int gameEnded = 0;
    CB.initialize();
    pgnFile pgnObject;
    //
    CB.printBoard();
    //
    while (!gameEnded){
        pgnObject.APPEND_TO_GAMELOG(to_string(moveCounter) + ". ");
        pgnObject.APPEND_TO_GAMELOG(CB.move(1) + " ");
        CB.printBoard();
        pgnObject.APPEND_TO_GAMELOG(CB.move(-1) + " ");
        CB.printBoard();
        ++moveCounter;
        //
        if (MOVELIMITREACHED()){
            gameEnded = 1;
        }
        //
    }
    pgnObject.printGameLog();
    pgnObject.saveGame();
    //
    return 0;
}

inline bool MOVELIMITREACHED(){
    return (moveCounter == (MOVES+1));
}



