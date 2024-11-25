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
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

string gameBoard[10]={
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
GameMechs* gameMechInstance = new GameMechs(20,10);

Player* snakeHead = new Player(gameMechInstance); 

Food* snakeFood = nullptr;
Food* new_snakeFood = nullptr;

int wipe_food;

int main(void)
{

    Initialize();

    srand(time(NULL));
    snakeFood = new Food();
    new_snakeFood = new Food();

    while(gameMechInstance->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    wipe_food = 0;
}

void GetInput(void)
{

    if (MacUILib_hasChar()){

        gameMechInstance->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{

    if (gameMechInstance->getInput()== 27){
        gameMechInstance->setExitTrue();
    }

    if (gameMechInstance->getInput() == 61)        //Debug key (=) to wipe away current food and generate new food
    {
        wipe_food = 1;
    }
    snakeHead->updatePlayerDir();
    snakeHead->movePlayer();

    gameMechInstance->clearInput(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos myCharacter = snakeHead->getPlayerPos();

    if(wipe_food == 1)
    {
        snakeFood->generateFood(myCharacter);
        wipe_food = 0;
    }

    objPos foodGeneration = snakeFood->getFoodPos();

for (int i =0; i<gameMechInstance->getBoardSizeY();i++){
        for (int j=0; j<gameMechInstance->getBoardSizeX(); j++){
            int printed =0; 

            
            //if the character position is met in the gameboard, print character
            if (myCharacter.pos->x== j && myCharacter.pos->y == i){
                MacUILib_printf("%c", myCharacter.getSymbol());
                printed = 1; 
            }

            if(foodGeneration.pos->x == j && foodGeneration.pos->y == i)
            {
                MacUILib_printf("%c", foodGeneration.symbol);
                printed = 1;
            }

            if (printed!=1){
                MacUILib_printf("%c", gameBoard[i][j]);
            }
            
            
            
        
        
    }
    MacUILib_printf("\n");


    

  }


MacUILib_printf("\n///Debugging Messages///\n");
MacUILib_printf("Key Pressed: %c\n", gameMechInstance->getPrevInput());
MacUILib_printf("Current state of FSM: %d\n",snakeHead->getFSMState());
MacUILib_printf("Current Player Coordinates (x,y): (%d,%d)\n", myCharacter.pos->x, myCharacter.pos->y);
MacUILib_printf("Current Random Food Coordinates (x,y): (%d,%d)", foodGeneration.pos->x, foodGeneration.pos->y);
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete gameMechInstance;
    delete snakeHead;
    delete snakeFood;
    delete new_snakeFood;

    MacUILib_clearScreen();    
    if(gameMechInstance->getLoseFlagStatus() == true ){

        MacUILib_printf ("You Lost, Better Luck Next Time!"); 
    }
    else if (gameMechInstance->getExitFlagStatus() == true){
        MacUILib_printf("See You Next Time!"); 
    }
    MacUILib_uninit();
}
 