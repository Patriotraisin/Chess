#ifndef Piece_hpp
#define Piece_hpp

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class Piece{
public:
    // variables
    int pieceType;
    int parity; // -1 = black, 1 = white
    string position;
    string pieceName;
    float pieceValue;
    
    // constructors
    Piece();
    
    // functions
    void define(int type, int color, int pos, string name, float value);
    void printInfo();
    
};
#endif /* Piece_hpp */
