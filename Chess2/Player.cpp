#include "Player.hpp"
#include <iostream>

std::string Player::getMove(){
    std::string move;
    std::cout << "Input move (correct syntax, case-sensitive):" << std::endl;
    std::cin >> move;
    
    return move;
}
