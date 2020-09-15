#ifndef Pawn_hpp
#define Pawn_hpp

#include <stdio.h>
#include <string>

class Pawn{
public:
    static void setPawnPresets(int isWhite, int* pawnUpperBound, int *pawnLowerBound, std::string* piece, int *pawnVar);
};
#endif /* Pawn_hpp */
