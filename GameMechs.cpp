#include "GameMechs.h"

GameMechs::GameMechs()
{
 score =0;
 exitFlag = false; 
 loseFlag= false; 
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX; 
    boardSizeY = boardY; 
    score =0;
    exitFlag = false; 
    loseFlag=false; 
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
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

int GameMechs::incrementScore(int increment)
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
    input = this_input;
    prevInput = this_input; 
}

void GameMechs::clearInput()
{

    input = 0; 
}

char GameMechs::getPrevInput(){
    return prevInput; 
}

void GameMechs::setScore(int val){
    score=val; 
}
// More methods should be added here