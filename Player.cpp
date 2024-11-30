#include "Player.h"
#include "iostream"


Player::Player(GameMechs* thisGMRef)        //Initializes all data members of Player class
{
    playerPosList = new objPosArrayList();      //Starting player size
    mainGameMechsRef = thisGMRef;
    myDir = STOP;                             //Starting state is stop
    playerPosList->insertHead(objPos(11,5,'*'));    //Starts player in the middle of the board
    backLog = 0;            //Backlog starts as 0, since no food has been eaten yet
}

Player::~Player()
{
    delete playerPosList;           //Deletes the playerPosList assigned on the heap
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;        //Returns the reference to the playerPos arrray list
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

int Player::movePlayer(Food *snakeFood)         //Player movement logic
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
    case STOP:          //Stop case has no change in x or y coordinates, player does not move
        break; 
    }

    if (checkSelfCollision()){          //Calls checkSelfCollision, if true then loseFlag is called and set to true.
        mainGameMechsRef->setLoseFlag();    //Then the game ends
        return 1; 
    }
    
    if(checkFoodConsumption(snakeFood) == 1)  //Calls checkFoodConsumption, if return value is 1 (capital S was eaten), do the following:
    {
        backLog = 1;    //Backlog is set 1, so size can be increazed by 1 later. 'S' only increments length by 1, same as default chars
        snakeFood->generateFood(playerPosList); //Generates new food because food was just eaten, passes playerPosList so food does not generate on top of the player/snake
        mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(3));    //Special character 'S', increments score by 3
    }

    if(checkFoodConsumption(snakeFood) == 2)   //Calls checkFoodConsumption, if return value is 2 (lowercase s was eaten), do the following:
    {
        backLog = 3;    //Backlog is set to 3, so size can be increazed by 3 later. So, special character 's', increments snake/player length by 3 instead of default 1
        snakeFood->generateFood(playerPosList);  //Generates new food because food was just eaten, passes playerPosList so food does not generate on top of the player/snake
        mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(1)); //'s' only increments score by 1, same as default chars
    }

    if((checkFoodConsumption(snakeFood) == -1)) //Calls checkFoodConsumption, if return value is 2 (default char was eaten), do the following:
    {
        backLog = 1;     //Backlog is set 1, so size can be increazed by 1 later. Defualt chars only increase length by 1
       snakeFood->generateFood(playerPosList);  //Generates new food because food was just eaten, passes playerPosList so food does not generate on top of the player/snake
       mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(1));   //Default chars only increment score by 1
    }
  
    if(backLog>0)   //if backlog is more than 0, then a food was eaten
    {          
        backLog--;          //Decrement backlog for future iterations
        playerPosList->insertHead(nextHead);   //Then increase length for each iteration where backlog was more than 0,
    }                                          //which is 3 times for 's' and once for anything else

    else{       //If backlog is 0, food was not eaten
        playerPosList->insertHead(nextHead);   //Follow the normal movement logic

        playerPosList->removeTail();        //Tail is removed here because we want the snake size to remain constant and move it,
    }                                       //not add more chars to snake.
    
    return 0;

   
}

Player::Dir Player::getFSMState(){
    return myDir; 
}


int Player::checkFoodConsumption(Food *snakeFood){  //Checks if food was eaten by obtaining current food from bucket,
    for (int i =0; i<snakeFood->bucketSize(); i++){     //and comparing the current food's x and y coordinates
        objPos currentFood = snakeFood->getFromBucket(i);      //to the snake/player head's x and y coordinates
        if (playerPosList->getHeadElement().pos->x == currentFood.pos->x  && playerPosList->getHeadElement().pos->y == currentFood.pos->y){
            if (currentFood.symbol == 'S')              //If the current food does have the same x and y pos as snake/player head,
            {                                           //return value depends on food symbol "eaten". This is to implement "Special chars" and how they function in the game
                return 1;                               //If current food symbol is 'S' (capital S), return 1
            }
            else if(currentFood.symbol == 's')
            {
                return 2;                               //If current food symbol is 's' (lowercase S), return 2
            }
            else
            {
                return -1;                      //If current food symbol is any other character, return -1
            }
        }                                       //These values are used in various fucntions for other purposes
    }
    return 0;           //Default return of 0
}


void Player::increasePlayerLength(){
    objPos newTail = playerPosList->getHeadElement();       //Increases player length at head element
    
    playerPosList->insertHead(objPos(newTail.pos->x,newTail.pos->y,'*')); 
        
}
 
bool Player::checkSelfCollision(){     
    objPos playerHead = playerPosList->getHeadElement();    //Creates a new variable and assigns it to the snake head pos

    for (int i =1; i<playerPosList->getSize(); i++){        //Iterates through the whole snake body,
        objPos currentBodyPart = playerPosList->getElement(i);  //assigns currentBodyPart to the snake element it has iterated to.
        if (playerHead.pos->x == currentBodyPart.pos->x && playerHead.pos->y==currentBodyPart.pos->y)   //And checks if the player head has the same x and y pos as the current body
        { 
            return true;    
        }
    }

    return false; 
}