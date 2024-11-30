#include "Food.h"
#include <iostream>
#include <time.h>
using namespace std;

void Food::generateFood(objPosArrayList* blockOff)
{
    int numItemsGen =0; 
    int i, j, unique, RandNum_x, RandNum_y, xRange = 20, yRange = 10;
    char RandSymbol;
    bool existingInBucket = false; 
    srand(time(NULL));

    while (numItemsGen!=5){
  


    
        do
        {
            unique = 1;
            RandNum_x = (rand() % (xRange - 2)) + 1;
            RandNum_y = (rand() % (yRange - 2)) + 1;

            if(rand() % 4 == 0)
            {
                RandSymbol = 'S';
            }
            else if(rand() % 4 == 2)
            {
                RandSymbol = 's';
            }
            else
            {
                RandSymbol = (rand() % 93) + 33;
            }

            foodPos.pos->x = RandNum_x;
            foodPos.pos->y = RandNum_y;
            foodPos.symbol = RandSymbol;

            if(RandSymbol == ' ' || RandSymbol == '$' || RandSymbol == '*')
            {
                unique = 0;
            }

        
            if(snakeBodyCheck(blockOff, RandNum_x,RandNum_y))
            {
                unique = 0;
            }
            if (existingInBucket = inBucketCheck()){
                unique=0; 
            } 
            

          
        }
        while(unique == 0);

        


        foodBucket->insertElement(numItemsGen,foodPos);
        numItemsGen++; 
    
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
    foodPos.pos = new Pos;
    foodPos.pos->x = f.foodPos.pos->x;
    foodPos.pos->y = f.foodPos.pos->y;
    foodPos.symbol = f.foodPos.symbol;

}

Food& Food::operator=(Food const &f)     //Copy Assignment Operator
{
    if(this != &f)
    {
        this->foodPos.pos = new Pos;
        this->foodPos.pos->x = f.foodPos.pos->x;
        this->foodPos.pos->y = f.foodPos.pos->y;
        this->foodPos.symbol = f.foodPos.symbol;
    }
    
    return *this;
}


bool Food::inBucketCheck(){

    for (int i = 0; i<foodBucket->getSize(); i++ ){
        objPos currentFood = foodBucket->getElement(i).getObjPos();
        if ((currentFood.pos->x  == foodPos.pos->x && currentFood.pos->y  == foodPos.pos->y) || currentFood.getSymbol() == foodPos.getSymbol()){
            return true; 
        }

       
    }


            return false; 
        

}

bool Food::snakeBodyCheck(objPosArrayList* blockOff, int x, int y){
    bool isCordTaken = false;
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

objPos Food::getFromBucket(int index){
    return foodBucket->getElement(index); 
}

Food::~Food()    //Destructor
{  
    delete  foodBucket; 
}
