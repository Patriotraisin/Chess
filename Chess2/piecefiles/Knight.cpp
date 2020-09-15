#include "Knight.hpp"

int Knight::knight_moves(Arbiter AB, Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY){ // function to calculate possible knight moves, obtain OldX and OldY values.
    const static int offsets[][2]= {{-2,-1},{-2,1}, {-1,-2}, {-1, 2}, {1,-2}, {1,2}, {2,1}, {2,-1},};
    for (int i = 0; i < 8; i++){ // take out invalid squares.
        //cout << (newX+offsets[i][0]) << (newY+offsets[i][1]) << endl;
        if ( (newX+offsets[i][0]) > 8  or (newX+offsets[i][0]) < 1 or (newY+offsets[i][1]) > 8 or (newY+offsets[i][1]) < 0 ){
            //cout << (newX+offsets[i][0]) << (newY+offsets[i][1]) << endl;
        }
        else{ // scan for pieces.
            if ((CB.chessboard[(newX+offsets[i][0])][(newY+offsets[i][1])].parity == isWhite) && (CB.chessboard[(newX+offsets[i][0])][(newY+offsets[i][1])].pieceValue == 3)){ // if knight
                *oldX = (newX+offsets[i][0]);
                *oldY = (newY+offsets[i][1]);
                return 1;
            }
        } // end of else
    } // end of for loop.
    AB.error(2);
    return 0;
}
