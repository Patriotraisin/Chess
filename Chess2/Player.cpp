#include "Player.hpp"
#include "pgnFile.hpp"
#include <iostream>

Player::Player():name("John Doe"),age(18),ELO(1000),side(true){
    std::cout << "Player created." << std::endl;
}
std::string Player::getMove(){
    std::string move;
    std::cout << "Input move (correct syntax, case-sensitive):" << std::endl;
    std::cin >> move;
    
    return move;
}

