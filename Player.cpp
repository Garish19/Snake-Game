#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    playerPosList = new objPosArrayList(); 
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList->insertHead(objPos(11,5,'*'));
    


   

    // more actions to be included

}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList; 
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; 
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
       char input = mainGameMechsRef->getInput();
        // Check if the input is 'w' or 'W' and the current direction is not DOWN
        // If true, set the direction to UP
        if ((input == 'w' || input == 'W') && myDir != DOWN) {
            myDir = UP;
        }
        // Check if the input is 's' or 'S' and the current direction is not UP
        // If true, set the direction to DOWN
        else if ((input == 's' || input == 'S') && myDir != UP) {
            myDir = DOWN;
        }
        // Check if the input is 'a' or 'A' and the current direction is not RIGHT
        // If true, set the direction to LEFT
        else if ((input == 'a' || input == 'A') && myDir != RIGHT) {
            myDir = LEFT;

        }
        // Check if the input is 'd' or 'D' and the current direction is not LEFT
        // If true, set the direction to RIGHT
        else if ((input == 'd' || input == 'D') && myDir != LEFT) {
            myDir = RIGHT;
            }




}

void Player::movePlayer(Food *snakeFood)
{
    objPos nextHead = playerPosList->getHeadElement(); 

    // PPA3 Finite State Machine logic
    //Switch Case for changing player position
    switch (myDir) {
    // If the current direction is DOWN, move the character down by 1
    case DOWN:
        nextHead.pos->y++;
    

        // If the character's y-position reaches 9 (out of bounds), wrap around to y = 1
        if (nextHead.pos->y == mainGameMechsRef->getBoardSizeY()- 1 ){
            nextHead.pos->y = 1;
        }
        break;

    // If the current direction is UP, move the character up by 1
    case UP:
        nextHead.pos->y--;
        // If the character's y-position reaches 0 (out of bounds), wrap around to y = 8
        if (nextHead.pos->y == 0) {
            nextHead.pos->y = mainGameMechsRef->getBoardSizeY()-2;
        }
        break;

    // If the current direction is RIGHT, move the character right by 1
    case RIGHT:
        nextHead.pos->x++;
        // If the character's x-position reaches 19 (out of bounds), wrap around to x = 1
        if (nextHead.pos->x == mainGameMechsRef->getBoardSizeX()-1) {
            nextHead.pos->x = 1;
        }
        break;

    // If the current direction is LEFT, move the character left by 1
    case LEFT:
        nextHead.pos->x--;
        // If the character's x-position reaches 0 (out of bounds), wrap around to x = 18
        if (nextHead.pos->x== 0) {
            nextHead.pos->x = mainGameMechsRef->getBoardSizeX()-2;
        }
        break;
    case STOP:
        break; 
    }

    
    
    if (checkFoodConsumption(snakeFood)){
        playerPosList->insertHead(objPos(11,5,'*')); 
        snakeFood->generateFood(playerPosList);
    }

    playerPosList->insertHead(nextHead); 
    playerPosList->removeTail();

   
}

Player::Dir Player::getFSMState(){
    return myDir; 
}


bool Player::checkFoodConsumption(Food *snakeFood){
    for (int i =0; i<snakeFood->bucketSize(); i++){
        objPos currentFood = snakeFood->getFromBucket(i);
        if (playerPosList->getHeadElement().pos->x == currentFood.pos->x  && playerPosList->getHeadElement().pos->y == currentFood.pos->y){
            return true; 
        }
    }
    return false;

}