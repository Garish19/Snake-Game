#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class GameMechs;        //removing this stops the code from compiling **IMPORTANT
class Food;             //removing this stops the code from compiling **IMPORTANT

class Player
{   
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();      //Destructor

        objPosArrayList* getPlayerPos() const;      
        void updatePlayerDir();
        int movePlayer(Food *snakeFood);
        Dir getFSMState(); 
        int checkFoodConsumption(Food* snakeFood);
        void increasePlayerLength(); 
        bool checkSelfCollision(); 

    private:
        objPosArrayList* playerPosList;    //Pointer of type objPosArrayit 
        Dir myDir;                         //Current direction
        int backLog;   //Backlog of how many characters need to be inserted into snake tail. Done to ensure that when inserting many characters, they don't insert on top of one another

        //A reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif