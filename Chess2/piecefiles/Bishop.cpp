#include "Bishop.hpp"
#include <cmath>
#include <iostream>

int Bishop::bishop_moves(Arbiter AB, Chessboard CB, int newX, int newY, int isWhite, int* oldX, int* oldY){
    if (!(0 < newX and newX < 9) or !(0 < newY and newY < 9)){ // going outside the board
        AB.error(2);
        return 0;
    }
    
    if (abs(double((newX-*oldX)/(newY-*oldY))) == 1){ // detect diagonal movement
        int xG = ((newX>*oldX) ? 1 : -1);
        int yG = ((*oldY > newY) ? -1 : 1);
        int y = *oldY + yG;
        cout << "Diagonal movement detected." << endl;

        for (int i = *oldX + xG; ((i != newX) && y != (newY)); i += xG ){ // scanning in between pieces
            cout << "TEST: " << !((i == *oldX) && (y == newX)) << endl;
            if (CB.chessboard[i][y].parity == isWhite){
             cout << "I:" << i << " Y:" << y << endl;
             CB.chessboard[i][y].printInfo();
             AB.error(2);
             return 0;
             }
            cout << "I:" << i << " Y:" << y << endl;
            y+=yG;
        }
        std::cout << *oldX << *oldY << std::endl;
        std::cout << newX << newY << std::endl;
        cout << "I made it past the for loop" << endl;
        return 1;
    }
    
    return 0;
}
