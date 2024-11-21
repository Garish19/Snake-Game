#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(11,5,'*');
    // more actions to be included

}

Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    return playerPos.getObjPos();
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

void Player::movePlayer()
{

    // PPA3 Finite State Machine logic
    //Switch Case for changing player position
    switch (myDir) {
    // If the current direction is DOWN, move the character down by 1
    case DOWN:
        playerPos.pos->y++;
    

        // If the character's y-position reaches 9 (out of bounds), wrap around to y = 1
        if (playerPos.pos->y == mainGameMechsRef->getBoardSizeY()- 1 ){
            playerPos.pos->y = 1;
        }
        break;

    // If the current direction is UP, move the character up by 1
    case UP:
        playerPos.pos->y--;
        // If the character's y-position reaches 0 (out of bounds), wrap around to y = 8
        if (playerPos.pos->y == 0) {
            playerPos.pos->y = mainGameMechsRef->getBoardSizeY()-1;
        }
        break;

    // If the current direction is RIGHT, move the character right by 1
    case RIGHT:
        playerPos.pos->x++;
        // If the character's x-position reaches 19 (out of bounds), wrap around to x = 1
        if (playerPos.pos->x == mainGameMechsRef->getBoardSizeX()-1) {
            playerPos.pos->x = 1;
        }
        break;

    // If the current direction is LEFT, move the character left by 1
    case LEFT:
        playerPos.pos->x--;
        // If the character's x-position reaches 0 (out of bounds), wrap around to x = 18
        if (playerPos.pos->x== 0) {
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX()-1;
        }
        break;
    case STOP:
        break; 
    }
    
}

Player::Dir Player::getFSMState(){
    return myDir; 
}
