#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"


using namespace std;

class GameMechs
{
    private:
        char input;
        char prevInput; 
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;

    public:
        GameMechs();            //Constructor
        GameMechs(int boardX, int boardY);
        ~GameMechs();       //An empty destructor
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();
        char getPrevInput(); 
    

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        int incrementScore(int);
        void setScore(int val); 
};

#endif