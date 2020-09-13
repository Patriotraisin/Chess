#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include <string>
#include "Piece.hpp"
#include "Arbiter.hpp"

class Chessboard{
public:
    
    Chessboard();
    
    Piece chessboard[8][8];
    Arbiter AB;
    
    void initialize();
    void printBoard();
    void emptySquare(int x, int y);
    
    
    void debug(std::string move);
    std::string move(int isWhite);
    int knight_moves(Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int *oldY);
    int bishop_moves(Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY);
};
#endif /* Chessboard_hpp */
