#ifndef Bishop_hpp
#define Bishop_hpp

#include <stdio.h>
#include <string>
#include "Chessboard.hpp"
#include "Arbiter.hpp"

class Bishop{
public:
    static int bishop_moves(Arbiter AB, Chessboard CB, int newX, int newY, int isWhite, int* oldX, int* oldY);
};

#endif /* Bishop_hpp */
