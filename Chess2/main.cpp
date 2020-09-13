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
int gameEnded = 0;

// main function
int main() {
    CB.initialize();
    pgnFile pgnObject;
    pgnObject.saveGame();
    CB.printBoard();
    while (1){
        CB.move(1);
        CB.printBoard();
        CB.move(-1);
        CB.printBoard();
    }
    
    return 0;
}


