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
// main function
int main() {
    string gameLog = "";
    //
    int gameEnded = 0;
    CB.initialize();
    pgnFile pgnObject;
    //
    CB.printBoard();
    //
    //cout << gameEnded << "D" << endl;
    while (gameEnded == 0){
        gameLog.append(to_string(moveCounter) + ". ");
        gameLog.append(CB.move(1) + " ");
        CB.printBoard();
        gameLog.append(CB.move(-1) + " ");
        CB.printBoard();
        ++moveCounter;
        //
        if (moveCounter == (MOVES+1)){
            gameEnded = 1;
        }
        //
    }
    cout << gameLog << endl;
    pgnObject.saveGame(gameLog);
    //
    return 0;
}


