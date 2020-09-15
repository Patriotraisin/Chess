#include "Piece.hpp"
#include "Pawn.hpp"

Piece::Piece(){
    pieceType = 0;
    parity = 0;
    position = -1;
    pieceName = " ";
    pieceValue = 0;
}

void Piece::define(int type, int color, int pos, string name, float value){
    pieceType = type;
    parity = color;
    position = pos;
    pieceName = name;
    pieceValue = value;
}

void Piece::printInfo(){
    cout << "Piece ID: " << pieceType << endl;
    cout << "Color: " << parity << endl;
    cout << "Position: " << position << endl;
    cout << "Piece name: " << pieceName << endl;
    cout << "Piece value: " << pieceValue << endl;
}
