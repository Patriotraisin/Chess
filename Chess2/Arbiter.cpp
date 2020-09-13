#include "Arbiter.hpp"

#include <iostream>
#include <string>

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




