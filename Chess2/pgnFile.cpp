#include "pgnFile.hpp"
#include <fstream>
#include <ctime>
#include <string>


pgnFile::pgnFile(){
    result = 0;
    gameTerminated = false;
    round = 1;
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

void pgnFile::saveGame(std::string gameLog){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // TODO:
    //Determine file name
    // Get file handle
    std::ofstream pgnFileHandle;
    pgnFileHandle.open("TODOestablishfilename.pgn", std::ofstream::out | std::ofstream::trunc); // ensure empty file
    // TODO: write to file
    pgnFileHandle << "[Result \""         << (result == 0 ? ("1/2-1/2"): (result == 1 ? ("1-0"):("0-1"))) << "\"] "
    << "\n"
                  << "[Termination \""    << (gameTerminated == 1 ? ("terminated") : ("unterminated")) << "\"] "
    << "\n"
                  << "[Date \""           << (1900 + ltm->tm_year) << "." << (1 + ltm->tm_mon) << "." << (ltm->tm_mday) << "\"] "
    << "\n"
                  << "[Round \""          << round << "\"] "
    << "\n"
                  << "[WhiteElo \""       << whiteELO << "\"] "
    << "\n"
                  << "[TimeControl \""    << TC_MINUTES << "+" << TC_SECONDSPERMOVE << "\"] "
    << "\n"
                  << "[Event \""          << event << "\"] "
    << "\n"
                  << "[Black \""          << blackName << "\"] "
    << "\n"
                  << "[BlackElo \""       << blackELO << "\"] "
    << "\n"
                  << "[Site \""           << site << "\"] "
    << "\n"
                  << "[White \""          << whiteName << "\"]\n\n"
    ;
    // print actual game
    pgnFileHandle << gameLog;
    // close file
    pgnFileHandle.close();
    // throw exception if issue found
}


