#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"


class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        int movePlayer(Food *snakeFood);
        Dir getFSMState(); 
        int checkFoodConsumption(Food* snakeFood);
        void increasePlayerLength(); 
        bool checkSelfCollision(); 

        // More methods to be added here

    private:
        objPosArrayList* playerPosList; // Upgrade this in iteration 3.       
        Dir myDir;
        int backLog;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif