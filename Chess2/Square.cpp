#include "Square.hpp"

int Square::getParity(int x_coord, int y_coord){ // 1 = white, -1 = black
    if ((x_coord + y_coord) % 2){ // if sum is odd
        return 1;
    }
    return -1; // or even
}
