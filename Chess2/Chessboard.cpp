#include "Piece.hpp"
#include "Square.hpp"
#include "Chessboard.hpp"
#include "Arbiter.hpp"
#include "Player.hpp"

#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

#include <cmath>
#include <math.h>

Chessboard::Chessboard(){
}

void Chessboard::emptySquare(int x, int y){
    chessboard[x][y].define(0, 0, (int)((10*y)+x), "  ", 0);
}

void Chessboard::printBoard() const{
    cout << "\n\n\n\n" << endl;
    for (int y = 8; y >=1; y--){
        cout << " ==================================" << endl;
        cout << y << "||";
        for (int x = 1; x <= 8; x++){
            cout << chessboard[x][y].pieceName << "||";
            
        }
        
        cout << "\n";
    }
    cout << "  A   B   C   D   E   F   G   H" << endl;
    
}

void Chessboard::initialize(){
        for (int y = 1; y <= 9; y++){
            for (int x = 1; x <= 9; x++){
                emptySquare(x,y);
            }
        }
        for (int y = 1; y <= 9; y++){
            for (int x = 1; x <= 8; x++){
                if (y == 1){ // white minor / major pieces
                    if ((x == 1) || (x == 8)){
                        chessboard[x][y].define(4, 1, ((10*y)+x), "WR", 5); // white rooks
                    }
                    if ((x == 2) || (x == 7)){
                        chessboard[x][y].define(3, 1, ((10*y)+x), "WN", 3); // white knights
                    }
                    if ((x == 3) || (x == 6)){
                        chessboard[x][y].define(2, 1, ((10*y)+x), "WB", 3.25); // white bishops
                    }
                    if (x == 5){
                        chessboard[x][y].define(6, 1, ((10*y)+x), "WK", 1000); // white king
                    }
                    if (x == 4){
                        chessboard[x][y].define(5, 1, ((10*y)+x), "WQ", 9); // white queen
                    }
                }
                
                if (y == 8){ // black minor / major pieces
                    if ((x == 1) || (x == 8)){
                        chessboard[x][y].define(4, -1, ((10*y)+x), "BR", 5); // black rooks
                    }
                    if ((x == 2) || (x == 7)){
                        chessboard[x][y].define(3, -1, ((10*y)+x), "BN", 3); // black knights
                    }
                    if ((x == 3) || (x == 6)){
                        chessboard[x][y].define(2, -1, ((10*y)+x), "BB", 3.25); // black bishops
                    }
                    if (x == 5){
                        chessboard[x][y].define(6, -1, ((10*y)+x), "BK", 1000); // black king
                    }
                    if (x == 4){
                        chessboard[x][y].define(5, -1, ((10*y)+x), "BQ", 9); // black queen
                    }
                }
                
                // pawns
                if (y == 2){
                    chessboard[x][y].define(1, 1, ((10*y)+x), "WP", 1); // white pawn
                }
                if (y == 7){
                    chessboard[x][y].define(1, -1, ((10*y)+x), "BP", 1); // black pawn
                }
                
            }
        }
}

string Chessboard::move(int isWhite){
    string move;
    string piece;
    float value = 0;
    int pawnVar = 0;
    int pawnUpperBound = 0;
    int pawnLowerBound = 0;
    bool isLegal = 0;
    int newX = 0, newY = 0, oldX = 0, oldY = 0; // positional variables
    
    Pawn::setPawnPresets(isWhite, &pawnUpperBound, &pawnLowerBound, &piece, &pawnVar);

    // end of pawn variable
    while (!isLegal){
        isLegal = Arbiter::SET_MOVE_LEGAL();
        Arbiter::announceTurn(isWhite);
        move = Player::getMove();
        if (move.length() < 5){ //
            if (!(isupper(move[0]))){ // pawn move.
                value = 1;
                if(isWhite == 1){
                    pawnUpperBound = 9;
                    pawnLowerBound = 2; // 2
                    piece = "WP";
                }
                else if (isWhite == -1){
                    pawnUpperBound = 7; // 7
                    pawnLowerBound = 0;
                    piece = "BP";
                }
                else{
                    piece = "error";
                }
                
                if (move[1] == 'x'){ // if captures
                    setDestinationSquares(value, 1, &newX, &newY, &oldX, &oldY, move, isWhite);
                    for (int count = (newY+isWhite); count != (/*isWhite + */pawnVar); count -= isWhite){
                        if ((chessboard[oldX][count].parity == isWhite) && (chessboard[oldX][count].pieceValue == 1)){
                            oldY = count;
                            //cout << "pawn detected at " << move[0] << oldY << "." << endl; // DEBUGLINE
                            break;
                        }
                        else{
                            // pawn not detected at Y level.
                    }
                    }
            //
                    if (chessboard[newX][newY].pieceValue == 0){ // cant capture nothing!
                        isLegal = AB.error(4);
                    }
                    else if (newY == oldY or newX == oldX){
                        isLegal = AB.error(4);
                    }
                    else if (abs(newX-oldX) != 1){
                        isLegal = AB.error(4);
                    }
                    else if (abs(newY-oldY) >= 2){ // you cant move more than these squares.
                        cout << "illegal move: square " << move[0] << newY << " is not a possible destination for " << chessboard[oldX][oldY].pieceName << " on " << move[0] << oldY << endl;
                        isLegal = AB.error(2);
                    }
                    //
                } // end of captures.
                else{ // or forward move.
                    setDestinationSquares(value, 0, &newX, &newY, &oldX, &oldY, move, isWhite);
                    for (int count = newY; count != pawnVar; count -= isWhite){ // scanned to find the location of the old piece
                        if ((chessboard[newX][count].pieceValue == 1) && (chessboard[newX][count].parity == isWhite)){  // finding nearest pawn that is the one which is moved
                            oldY = count;
                            cout << "pawn detected at " << move[0] << oldY << "." << endl;
                            break;
                        }
                    }
                    if ( !((pawnLowerBound < newY) and (newY < pawnUpperBound)) ){ // cant go beyond certain preset boundaries. goes for every pawn move.
                        isLegal = AB.error(2);
                    }
                    //cout << "\ndifference in Y values from new destination to old: " << abs(newY-oldY) << "\nstarting Y value: " << pawnVar+isWhite << "\nnewY:" << newY << "\noldY: " << oldY << "\npawn var: " << pawnVar << "\nis white (1 = white, -1 = black)" << isWhite << endl;
                    else if ((abs(newY-oldY) > 2) && (oldY == (pawnVar+isWhite)) ){ // starting square.
                        //cout << "illegal move: square " << move[0] << newY << " is not a possible destination for " << chessboard[oldX][oldY].pieceName << " on " << move[0] << oldY << endl;
                        isLegal = AB.error(2);
                    }
                    else if ((abs(newY-oldY) > 1) && !(oldY == (pawnVar+isWhite))){
                        isLegal = AB.error(2);
                    }
                    else if (oldY == newY){ // cant go to same square
                        isLegal = AB.error(3);
                        //cout << "illegal move. can't move to same square." << endl;
                    }
                    else if (chessboard[newX][newY].pieceValue != 0){
                        isLegal = AB.error(4);
                        //cout << "illegal move. you cant capture straight." << endl;
                    }
                    else if ((oldY != ((isWhite) + pawnVar)) && (abs(newY-oldY) >= 2)){
                        isLegal = AB.error(2);
                        //cout << oldY << "test" << ((isWhite) + pawnVar)<< "." << endl;
                        //cout << "your coefficient is" << isWhite + pawnVar << endl;
                        //cout << "illegal move. pawns can only move 2 squares on first turn." << endl;
                    }
                } // end of forward move.
            } // end of pawn move
            
            
            
            else if (isupper(move[0])){ // different piece moves.
                if (move[0] == 'N'){ // knight move
                    // presets
                    //isLegal = 1;
                    value = 3;
                    if(isWhite == 1){
                        piece = "WN";
                    }
                    else if (isWhite == -1){
                        piece = "BN";
                    }
                    else{
                        piece = "error";
                    }
                    // end of presets
                    
                    if (move[1] == 'x'){ // if captures
                        setDestinationSquares(2, 1, &newX, &newY, &oldX, &oldY, move, isWhite);
                        isLegal = (Knight::knight_moves(AB, *this, newX, newY, isWhite, &oldX, &oldY)
                                | capture_vetting(*this, newX, newY, isWhite, &oldX, &oldY)); // basic movement vetting
                    }
                    else{ // or normal move
                        setDestinationSquares(2, 0, &newX, &newY, &oldX, &oldY, move, isWhite);
                        isLegal = (Knight::knight_moves(AB, *this, newX, newY, isWhite, &oldX, &oldY)
                                  | normal_vetting(*this, newX, newY, isWhite, &oldX, &oldY)); // basic movement vetting
                    }
                } // end of knight move
                
                else if (move[0] == 'B'){ // bishop move
                    // presets
                    //isLegal = 1;
                    value = 3.25;
                    if(isWhite == 1){
                        piece = "WB";
                    }
                    else if (isWhite == -1){
                        piece = "BB";
                    }
                    else{
                        piece = "error";
                    }
                    // end of presets, now find old X / old Y
                    
                    
                    // now running through code
                         
                    if (move[1] == 'x'){ // if captures
                        setDestinationSquares(3, 1, &newX, &newY, &oldX, &oldY, move, isWhite);
                        //cout << "you are planning bishop captures on " << newX << newY << " or Bx" << move[2] << move[3] << "." << endl;
                        isLegal = (Bishop::bishop_moves(AB, *this, newX, newY, isWhite, &oldX, &oldY)
                                  & capture_vetting(*this, newX, newY, isWhite, &oldX, &oldY));
                        
                    }
                    else{ // or normal move
                        setDestinationSquares(3, 0, &newX, &newY, &oldX, &oldY, move, isWhite);
                        //cout << "you are planning bishop " << newX << newY << " or B" << move[1] << move[2] << "." << endl;
                        isLegal = (Bishop::bishop_moves(AB, *this, newX, newY, isWhite, &oldX, &oldY)
                                &  normal_vetting(*this, newX, newY, isWhite, &oldX, &oldY)); // vetting bishop and normal moves
                    }
                    cout << isLegal << endl;
                } // end of bishop move
                
                else if (move[0] == 'R'){ // rook move
                    //isLegal = 1;
                    value = 5;
                    if (move[1] == 'x'){ // if captures
                        setDestinationSquares(value, 1, &newX, &newY, &oldX, &oldY, move, isWhite);
                        cout << "you are planning rook captures on " << newX << newY << " or Rx" << move[2] << move[3] << "." << endl;
                    }
                    else{ // or normal move
                        setDestinationSquares(value, 0, &newX, &newY, &oldX, &oldY, move, isWhite);
                        cout << "you are planning rook " << newX << newY << " or R" << move[1] << move[2] << "." << endl;
                    }
                } // end of rook move
                
                else if (move[0] == 'Q'){ // queen move
                    //isLegal = 1;
                    value = 9;
                    if (move[1] == 'x'){ // if captures
                        setDestinationSquares(value, 1, &newX, &newY, &oldX, &oldY, move, isWhite);
                        cout << "you are planning Queen captures on " << newX << newY << " or Qx" << move[2] << move[3] << "." << endl;
                    }
                    else{ // or normal move
                        setDestinationSquares(value, 0, &newX, &newY, &oldX, &oldY, move, isWhite);
                        cout << "you are planning Queen " << newX << newY << " or Q" << move[1] << move[2] << "." << endl;
                    }
                } // end of queen move
                else if (move[0] == 'K'){ // king move
                    //isLegal = 1;
                    if (move[1] == 'x'){ // if captures
                        setDestinationSquares(value, 1, &newX, &newY, &oldX, &oldY, move, isWhite);
                        //cout << "you are planning king captures on " << newX << newY << " or Kx" << move[2] << move[3] << "." << endl;
                    }
                    else{ // or normal move
                        setDestinationSquares(value, 0, &newX, &newY, &oldX, &oldY, move, isWhite);
                        //cout << "you are planning king " << newX << newY << " or K" << move[1] << move[2] << "." << endl;
                    }
                } // end of king move
                
                else{ // invalid syntax move
                    cout << "Illegal move: Invalid Syntax" << endl;
                    isLegal = Arbiter::SET_MOVE_ILLEGAL();
                } // invalid syntax
                
            } // end of different piece moves.
            
        } // end of < 4
        else{
            isLegal = AB.error(10);
        }
    } // end of while is legal
    // TODO: WRITE MOVE TO FILE
    
    
    cout << "REPLACING OLD PIECE AT " << oldX << oldY << endl;
    emptySquare(oldX, oldY);
    chessboard[newX][newY].define(1, isWhite, ((10*newY)+newX), piece, value);
    
    return move;
    
} // end of void move



int Chessboard::capture_vetting(Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY){
    if (chessboard[newX][newY].pieceValue == 0){
        return AB.error(1);
    }
    else if (chessboard[newX][newY].parity == isWhite){
        return AB.error(4);
    }
    return 1;
}

int Chessboard::normal_vetting(Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int *oldX, int *oldY){
    if (chessboard[newX][newY].pieceValue != 0){ // if you move you cannot capture.
        return AB.error(1);
    }
    else if ((newX == *oldX) && (newY == *oldY)){ // cant attempt to move skip by staying in the same place
        return AB.error(3);
    }
    else if (chessboard[newX][newY].parity == isWhite){ // cant capture own pieces
        return AB.error(4);
    }
    return 1;
}

void Chessboard::setDestinationSquares(int pieceType, bool captures, int* newX, int* newY, int *oldX, int *oldY, string move, int isWhite){
    int pawnVar = 0;
    if (isWhite == 1){
        pawnVar = 1;
    }
    else if (isWhite == -1){
        pawnVar = 8;
    }
    switch(pieceType){
        case 1: // pawn
            if (captures){
                *oldX = (int(move[0]) - 96);
                *newX = (int(move[2]) - 96);
                *newY = (int(move[3]) - 48);
            }
            else{
                *newX = (int(move[0]) - 96);
                *newY = (int(move[1]) - 48);
                *oldX = *newX;
                for (int count = *newY; count != pawnVar; count -= isWhite){ // scanned to find the location of the old piece
                    if ((chessboard[*newX][count].pieceValue == 1) && (chessboard[*newX][count].parity == isWhite)){  // finding nearest pawn that is the one which is moved
                        *oldY = count;
                        cout << "pawn detected at " << move[0] << *oldY << "." << endl;
                        break;
                    }
                }
            }
            break;
            
        case 2: // knight
            break;
        case 3: // bishop
            if (captures){
                *newX = (int(move[2]) - 96);
                *newY = (int(move[3]) - 48);
            }
            else{
                *newX = (int(move[1]) - 96);
                *newY = (int(move[2]) - 48);
            }
            for (int x = 0; x < 9; ++x){ // scan through chessboard to find bishops of same color
                for (int y = 0; y < 9; ++y){
                    if ((chessboard[x][y].parity == isWhite) && (chessboard[x][y].pieceValue == 3.25) && (Square::getParity(*newX, *newY) == Square::getParity(x, y))){
                        *oldX = x;
                        *oldY = y;
                    }
                }
            }
            break;
            
        default: // everything else, only sets newY.
            if (captures){
                *newX = (int(move[2]) - 96);
                *newY = (int(move[3]) - 48);
            }
            else{
                *newX = (int(move[1]) - 96);
                *newY = (int(move[2]) - 48);
            }
            break;
    }
}

void Chessboard::setPiecePresets(){
    
}



