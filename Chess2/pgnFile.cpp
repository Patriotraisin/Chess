#include "pgnFile.hpp"
#include <fstream>

pgnFile::pgnFile(){
    result = 0;
    round = 0;
    gameTerminated = false;
    TC_MINUTES = 30;
    TC_SECONDSPERMOVE = 0;
    whiteELO = 1000;
    blackELO = 1000;
    event = "null";
    site = "null";
    whiteName = "Player A";
    blackName = "Player B";
}

void pgnFile::setRound(int gameRound){
    round = gameRound;
}

void pgnFile::saveGame(){
    // Determine file name
    // Get file handle
    std::ofstream pgnFileHandle;
    pgnFileHandle.open("TODOestablishfilename.pgn", std::ofstream::out | std::ofstream::trunc); // makes sure file is empty
    // write to file
    pgnFileHandle << "test";
    // close file
    pgnFileHandle.close();
    // throw exception if issue found
}
