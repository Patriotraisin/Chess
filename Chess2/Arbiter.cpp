#include "Arbiter.hpp"

#include <iostream>
#include <string>
#include <exception>

Arbiter::Arbiter(){
    
}

int Arbiter::error(int id){
    std::string name;
    switch(id){
        case 1: //cannot capture empty piece.
            name = "empty capture";
            break;
        case 2:
            name = "bad destination";
            break;
        case 3:
            name = "cannot skip move";
            break;
        case 4:
            name = "illegal capture";
            break;
        default:
            name = "invalid syntax";
            break;
    }
    std::cout << "illegal move - " << name << " #" << id << std::endl;
    return 0;
}

void Arbiter::announceTurn(int isWhite){
    if (isWhite == 1){
        std::cout << "White to move. ";
    }
    else if (isWhite == -1){
        std::cout << "Black to move. ";
    }
    else{
        throw new std::runtime_error("An error occurred.");
    }
}

int Arbiter::SET_MOVE_ILLEGAL(){
    return 0;
}

int Arbiter::SET_MOVE_LEGAL(){
    return 1;
}






