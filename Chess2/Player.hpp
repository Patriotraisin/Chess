#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>

class Player{
    std::string name;
    int age;
    unsigned int ELO;
    bool side; // true = white, false = black
public:
    Player();
    // functions
    static std::string getMove();
    
};

#endif /* Player_hpp */
