#include "GameMechs.h"

GameMechs::GameMechs()      //Constructor
{
 score =0;
 exitFlag = false; 
 loseFlag= false; 
}

GameMechs::GameMechs(int boardX, int boardY)        //Constructor, intializes all values
{
    boardSizeX = boardX; 
    boardSizeY = boardY; 
    score =0;
    exitFlag = false; 
    loseFlag=false; 
}

GameMechs::~GameMechs()     //No destrcuctor needed because no member is created on the heap,
{                           //no class function creates anything on heap either
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{

    return loseFlag; 
}
    

char GameMechs::getInput() const
{

    return input; 
}

int GameMechs::getScore() const
{

    return score; 
}

int GameMechs::incrementScore(int increment)        //Increments score based on value passed
{
    score += increment;
    return score;
}

int GameMechs::getBoardSizeX() const
{
    //Starting from 0
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    //Starting from 0
    return boardSizeY; 
}


void GameMechs::setExitTrue()
{
    exitFlag = true; 

}

void GameMechs::setLoseFlag()
{
    loseFlag = true; 
}

void GameMechs::setInput(char this_input)
{
    prevInput = input;              ////Stores previous input
    input = this_input;             //Updates the current input, based on this_input (passed as an argument)
}

void GameMechs::clearInput()
{

    input = 0; 
}

char GameMechs::getPrevInput(){
    return prevInput; 
}

void GameMechs::setScore(int val){      //Sets score to a value passed to it
    score=val; 
}
// More methods should be added here