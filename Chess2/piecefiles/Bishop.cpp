#include "Bishop.hpp"
#include <cmath>

int Bishop::bishop_moves(Arbiter AB, Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY){
    cout << "THE VALUE IS" << abs(double((newX-*oldX)/(newY-*oldY))) << endl;
    if (!(0 < newX and newX < 9) or !(0 < newY and newY < 9)){ // going outside the board
        AB.error(2);
        return 0;
    }
    if (abs(double((newX-*oldX)/(newY-*oldY))) == 1){ // detect diagonal movement
        int y = *oldY;
        int yG = ((*oldY > newY) ? -1 : 1);
        cout << "Diagonal movement detected." << endl;
        for (int i = ((newX>*oldX) ? *oldX : newX); ((i != ((newX>*oldX) ? newX : *oldX)) && y != (newY)); i += ((newX>*oldX) ? 1 : 0) ){
            /*if (CB.chessboard[i][y].parity == isWhite){
             cout << "I:" << i << " Y:" << y << endl;
             chessboard[i][y].printInfo();
             AB.error(2);
             return 0;
             }*/
            cout << "I:" << i << " Y:" << y << endl;
            y+=yG;
        }
        return 1;
    }
    
    return 0;
}
