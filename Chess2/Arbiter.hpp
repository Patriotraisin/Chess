#ifndef Arbiter_hpp
#define Arbiter_hpp

#include <stdio.h>

class Arbiter{
public:
    Arbiter();
    int error(int id);
    static void announceTurn(int isWhite);
    
    static int SET_MOVE_ILLEGAL();
    static int SET_MOVE_LEGAL();
};

#endif /* Arbiter_hpp */
