
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
    
    // function
    
    void define(int type, int color, int pos, string name, float value){
        pieceType = type;
        parity = color;
        position = pos;
        pieceName = name;
        pieceValue = value;
    }
    void printInfo(){
        cout << "Piece ID: " << pieceType << endl;
        cout << "Color: " << parity << endl;
        cout << "Position: " << position << endl;
        cout << "Piece name: " << pieceName << endl;
        cout << "Piece value: " << pieceValue << endl;
    }
    
    
    // constructors
    Piece(){
        pieceType = 0;
        parity = 0;
        position = -1;
        pieceName = " ";
        pieceValue = 0;
    }
    Piece (int type, int color, int pos, string name, float value){
        pieceType = type;
        parity = color;
        position = pos;
        pieceName = name;
        pieceValue = value;
    }
    
};


#endif /* Piece_hpp */
