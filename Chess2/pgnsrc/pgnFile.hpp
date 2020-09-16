#ifndef pgnFile_hpp
#define pgnFile_hpp
#include <string>

class pgnFile {
    int result;
    bool gameTerminated;
    std::string gameLog;
    // date
    int round;
    unsigned int whiteELO, blackELO;
    unsigned int TC_MINUTES, TC_SECONDSPERMOVE;
    std::string event, site;
    std::string blackName, whiteName;
    
public:
    pgnFile();
    void setRound(int);
    
    void saveGame();
    void APPEND_TO_GAMELOG(std::string);
    void printGameLog();
};

#endif /* pgnFile_hpp */
