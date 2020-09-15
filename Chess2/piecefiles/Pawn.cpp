#include "Pawn.hpp"

void Pawn::setPawnPresets(int isWhite, int* pawnUpperBound, int *pawnLowerBound, std::string* piece, int *pawnVar){
    if(isWhite == 1){
        *pawnUpperBound = 9;
        *pawnLowerBound = 2; // 2
        *piece = "WP";
    }
    else if (isWhite == -1){
        *pawnUpperBound = 7; // 7
        *pawnLowerBound = 0;
        *piece = "BP";
    }
    else{
        *piece = "error";
    }
    //
    if (isWhite == 1){
        *pawnVar = 1;
    }
    else if (isWhite == -1){
        *pawnVar = 8;
    }
}
