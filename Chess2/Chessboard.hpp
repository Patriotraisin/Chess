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
    void printBoard() const;
    void emptySquare(int x, int y);
    
    
    void debug(std::string move);
    std::string move(int isWhite);
    
    void setDestinationSquares(int pieceType, bool captures, int* newX, int* newY, int* oldX, int *oldY, std::string move, int isWhite);
    void setPiecePresets();
        
    
    int capture_vetting(Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY);
    int normal_vetting(Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY);

    
    
};
#endif /* Chessboard_hpp */
