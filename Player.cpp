#include "Player.h"
#include "iostream"


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

int Player::movePlayer(Food *snakeFood)
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

    if (checkSelfCollision()){
        mainGameMechsRef->setLoseFlag();
        return 1; 
    }
    
    if(checkFoodConsumption(snakeFood) == 1)
    {
        increasePlayerLength(1);
        snakeFood->generateFood(playerPosList);
        mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(3));
    }

    if(checkFoodConsumption(snakeFood) == 2)
    {
        increasePlayerLength(3);
        snakeFood->generateFood(playerPosList);
        mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(1));
    }

    if((checkFoodConsumption(snakeFood) == -1))
    {
       increasePlayerLength(1);
       snakeFood->generateFood(playerPosList);
       mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(1));
    }

    playerPosList->insertHead(nextHead); 
    playerPosList->removeTail();
    return 0;

   
}

Player::Dir Player::getFSMState(){
    return myDir; 
}


int Player::checkFoodConsumption(Food *snakeFood){
    for (int i =0; i<snakeFood->bucketSize(); i++){
        objPos currentFood = snakeFood->getFromBucket(i);
        if (playerPosList->getHeadElement().pos->x == currentFood.pos->x  && playerPosList->getHeadElement().pos->y == currentFood.pos->y){
            if (currentFood.symbol == 'S')
            {
                return 1; 
            }
            else if(currentFood.symbol == 's')
            {
                return 2;
            }
            else
            {
                return -1; 
            }
        }
    }
    return 0;
}


void Player::increasePlayerLength(int num){
    objPos newTail = playerPosList->getTailElement();
        for(int i = 0; i < num; i++)
        {
            playerPosList->insertTail(objPos(newTail.pos->x,newTail.pos->y,'*')); 
        }
}
 
bool Player::checkSelfCollision(){
    objPos playerHead = playerPosList->getHeadElement();

    for (int i =1; i<playerPosList->getSize(); i++){
        objPos currentBodyPart = playerPosList->getElement(i);
        if (playerHead.pos->x == currentBodyPart.pos->x && playerHead.pos->y==currentBodyPart.pos->y){
            return true; 
        }
    }

    return false; 
}