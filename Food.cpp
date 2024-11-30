#include "Food.h"
#include <iostream>
#include <time.h>
using namespace std;

void Food::generateFood(objPosArrayList* blockOff)      //Random character generation, blockoff contains player pos
{
    int numItemsGen =0; 
    int i, j, unique, RandNum_x, RandNum_y, xRange = 20, yRange = 10;
    char RandSymbol;
    bool existingInBucket = false;              //Sets the food that currently exists in the bucket to false so more can be generated
    srand(time(NULL));      //Seeding random through time

    while (numItemsGen!=5){         //While loop to ensure 5 characters are generated
  


    
        do
        {
            unique = 1;
            RandNum_x = (rand() % (xRange - 2)) + 1;        //Generate random x coodrinate from 1 to 18
            RandNum_y = (rand() % (yRange - 2)) + 1;        //Generate random y coodrinate from 1 to 8

            if(rand() % 4 == 0)
            {
                RandSymbol = 'S';                           //25% chance to generate a 'S' special food char
            }
            else if(rand() % 4 == 2)
            {
                RandSymbol = 's';                           //25% chance to generate a 's' special food char
            }
            else
            {
                RandSymbol = (rand() % 93) + 33;            //Otherwise randomly generate an ASCII char between 33 and 126
            }

            foodPos.pos->x = RandNum_x;         //Set current food pos and symbol to random ones
            foodPos.pos->y = RandNum_y;
            foodPos.symbol = RandSymbol;

            if(RandSymbol == ' ' || RandSymbol == '$' || RandSymbol == '*')     //Stops border and player chars from being generated
            {
                unique = 0;                                                 //breaks while loop and generates random chars again
            }

        
            if(snakeBodyCheck(blockOff, RandNum_x,RandNum_y))    //Stops from random food generating on player x and y coordinate,
            {
                unique = 0;                                     //calls snake body check to do this
            }                                                   //Breaks while loop and generates random coordinates again
            if (existingInBucket = inBucketCheck()){
                unique=0;                                       //Breaks while loop and generates again,
            }                                                   //if randomly generated chars are already in the bucket
            

          
        }
        while(unique == 0);         //inner while loop condition

        


        foodBucket->insertElement(numItemsGen,foodPos);     //Inserts the rand food chars into bucket
        numItemsGen++;                                      //Increments outer while loop condition
    
    }


  
    return; 
}

objPos Food::getFoodPos() const
{
    return foodPos;
}

Food::Food()     //Constructor
{
   foodBucket = new objPosArrayList(5); 
   foodPos= objPos();
}

Food::Food(Food const &f)     //Copy Constructor
{   
    foodPos.pos = new Pos;              //Deep copy by assigning new heap space for element copied to
    foodPos.pos->x = f.foodPos.pos->x;
    foodPos.pos->y = f.foodPos.pos->y;
    foodPos.symbol = f.foodPos.symbol;

}

Food& Food::operator=(Food const &f)     //Copy Assignment Operator
{
    if(this != &f)
    {
        this->foodPos.pos->x = f.foodPos.pos->x;            //Deep copy, heap already created for "this" object
        this->foodPos.pos->y = f.foodPos.pos->y;
        this->foodPos.symbol = f.foodPos.symbol;
    }
    
    return *this;
}


bool Food::inBucketCheck(){     //Function that checks if randomly generated chars are already in food bucket or not

    for (int i = 0; i<foodBucket->getSize(); i++ ){
        objPos currentFood = foodBucket->getElement(i).getObjPos();
        if ((currentFood.pos->x  == foodPos.pos->x && currentFood.pos->y  == foodPos.pos->y) || currentFood.getSymbol() == foodPos.getSymbol()){
            return true; 
        }

       
    }


            return false; 
        

}

bool Food::snakeBodyCheck(objPosArrayList* blockOff, int x, int y){ //Checks the player pos against x and y which are passed as arguments
    bool isCordTaken = false;                                       //Called in rand food generation function to ensure food is not generated on player pos
    for (int i =0; i<blockOff->getSize(); i++ ){
         isCordTaken = blockOff->getElement(i).pos->x == x &&  blockOff->getElement(i).pos->y == y; 
         if(isCordTaken){
            return isCordTaken; 
         }
    }

    return isCordTaken;
}

int Food::bucketSize(){

    return foodBucket->getSize(); 
}

objPos Food::getFromBucket(int index){      //Returns a food element (index) from food bucket
    return foodBucket->getElement(index); 
}

Food::~Food()    //Destructor
{  
    delete  foodBucket; 
}
