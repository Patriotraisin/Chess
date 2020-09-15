#ifndef Knight_hpp
#define Knight_hpp

#include <stdio.h>
#include <string>
#include "Chessboard.hpp"

class Knight{
public:
    static int knight_moves(Arbiter AB, Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY);
};

#endif /* Knight_hpp */
