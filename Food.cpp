#include "Food.h"
#include <iostream>
using namespace std;

void Food::generateFood(objPos blockOff)
{
    int i, j, unique, RandNum_x, RandNum_y, xRange = 20, yRange = 10;
    char RandSymbol;

    if( (blockOff.pos->x == foodPos.pos->x) || (blockOff.pos->y  == foodPos.pos->y))
    {
        return;
    }
    
    for(i = 0; i < 1; i++)
    {
        do
        {
            unique = 1;
            RandNum_x = (rand() % xRange) + 1;
            RandNum_y = (rand() % yRange) + 1;

        
            RandSymbol = (rand() % 93) + 33;
            if(RandSymbol == ' ' || RandSymbol == '$' || RandSymbol == '*')
            {
                unique = 0;
                continue;
            }

            for(j = 0; j < i; j++)
            {   
                if((foodPos.pos->x == RandNum_x) && (foodPos.pos->y == RandNum_y))
                {
                    unique = 0;
                    break;
                }
            }

            for(j = 0; j < i; j++)
            {   
                if(foodPos.symbol == RandSymbol)
                {
                    unique = 0;
                    break;
                }
            }
        }
        while(unique == 0);

        foodPos.pos->x = RandNum_x;
        foodPos.pos->y = RandNum_y;
        foodPos.symbol = RandSymbol;
    }
}

objPos Food::getFoodPos() const
{
    return foodPos;
}

Food::Food()     //Constructor
{
    int unique = 1;
    
    foodPos.pos->x = 2;
    foodPos.pos->y = 5;
    do
    {
        foodPos.symbol = (rand() % 93) + 33;
        if(foodPos.symbol == ' ' || foodPos.symbol == '$' || foodPos.symbol == '*')
        {
            unique = 0;
            continue;
        }
    }
    while(unique == 0);
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

Food::~Food()    //Destructor
{
    delete foodPos.pos;
}
