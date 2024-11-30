#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
int RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


GameMechs* gameMechInstance = new GameMechs(20,10);     //Create gameboard

Player* snakeHead = new Player(gameMechInstance);       //Create the snake

Food* snakeFood = nullptr;      //Pointer to food is set to null initially

int main(void)
{

    Initialize();

   


    while(gameMechInstance->getExitFlagStatus() == false && gameMechInstance->getLoseFlagStatus() == false)  
    {
        GetInput();         //Only runs the input, draw screen, and loop delay functions while the player
        if (RunLogic() != 1);{  //has not forecully exited out of the game, or has lost the game
        DrawScreen();
        }

        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    snakeFood = new Food();     //Initalizes food
    snakeFood->generateFood(snakeHead->getPlayerPos());   //Generates food, passing playerPos into the function                                                  
    exitFlag = false;                                     //so that food does not spawn on top of snake/player
}

void GetInput(void)
{

    if (MacUILib_hasChar()){

        gameMechInstance->setInput(MacUILib_getChar());   //Get input char and set it using MacULib ansynchronous functions
    }
}

int RunLogic(void)
{

    if (gameMechInstance->getInput()== 27){     //Forecully exit the game if input is Esc key
        gameMechInstance->setExitTrue();
    }
    snakeHead->updatePlayerDir();           //Updates snake direction 
    if (1==snakeHead->movePlayer(snakeFood)){  //If movePlayer function returns 1, (the snake has collided into itself)
        MacUILib_clearScreen();                //Then clear the screen 
        return 1; 
    }
    gameMechInstance->clearInput();     //Clear input and reset it for every iteration
}

void DrawScreen(void)
{
    MacUILib_clearScreen();     //Clear the screen for every iteration

    objPosArrayList* myCharacter = snakeHead->getPlayerPos();  //Creates a variable myCharacter, which is a pointer to the playerPos

    
    string gameBoard[10]={          //Initializes game board
    {"$$$$$$$$$$$$$$$$$$$$"},  
    {"$                  $"},   
    {"$                  $"},
    {"$                  $"},
    {"$                  $"},
    {"$                  $"},
    {"$                  $"},
    {"$                  $"},
    {"$                  $"},
    {"$$$$$$$$$$$$$$$$$$$$"}  
};  


for (int i =0; i<gameMechInstance->getBoardSizeY();i++){      //Iterates through the game baord's cols
        for (int j=0; j<gameMechInstance->getBoardSizeX(); j++){    //Iterates through the game board's rows
            int printed = 0;        //printed is a variable to check conditions of player/snake being printed

            for (int  k = 0; k<myCharacter->getSize(); k++){
            objPos snake = myCharacter->getElement(k);   //snake variable iterates through each element in myCharacter, or the snake/player
            //if the character position is met in the gameboard, print character
            if (snake.pos->x== j && snake.pos->y == i){
                MacUILib_printf("%c", snake.getSymbol());
                printed = 1;        //Ensures following conditions do not trigger
            }
            }
             if (printed!=1){           //If the player was not printed, then checks random food printing conditions
                for (int foodIndex =0; foodIndex < snakeFood->bucketSize(); foodIndex++){   //Iterates through food bucket

                    objPos foodGeneration = snakeFood->getFromBucket(foodIndex); //food generation iterates through each element in food bucket

                    if(foodGeneration.pos->x == j && foodGeneration.pos->y == i)  //if the food generation x and y pos match the rows and cols of the gameboad respectively
                    {   printed =1; 
                        MacUILib_printf("%c", foodGeneration.getSymbol());  //Then print food
                        break; 
                    }
                }
            }

            if (printed!=1){   //If neither player nor food are printed, then print game board as it is defined/intialized above
                MacUILib_printf("%c", gameBoard[i][j]);
                 
            }
            
            
            
        
        
    }
    MacUILib_printf("\n");      //Move down a line after each row iteration


    

  }

MacUILib_printf("\nEating S = +3 score\nEating s = +3 snake length\n");     //Instructions for player
MacUILib_printf("\n///Debugging Messages///\n");
MacUILib_printf("Key Pressed: %c\n", gameMechInstance->getPrevInput());
MacUILib_printf("Current state of FSM: %d\n",snakeHead->getFSMState());
MacUILib_printf("Score: %d", gameMechInstance->getScore());         //Prints player's score
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

 


    MacUILib_clearScreen();    
    
    
       if(gameMechInstance->getLoseFlagStatus() == true ){

        MacUILib_printf ("You Lost, Better Luck Next Time!");   //Prints losing message
    }
    else  {
        MacUILib_printf("See You Next Time!");      //Prints forceful escape message
    }


    delete gameMechInstance;     //Delete all global variables that were initialized on the heap
    delete snakeHead;
    delete snakeFood;

    
}
 