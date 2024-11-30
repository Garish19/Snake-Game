#include "objPos.h"

objPos::objPos()        //Constructor assigns heap space because pos is a pointer to a struct Pos containing x and y,
{                       //so the struct has to be initialized on the heap
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)        //Similar reasoning as default constructor above
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//Destructor
objPos::~objPos(){

    delete pos;             //Deletes the struct created on memory
}

//Copy Constructor
objPos::objPos(const objPos &a){
    pos = new Pos;                  //Deep copy by assigning new heap space for element copied to
    pos->x = a.pos->x;
    pos->y = a.pos->y;
    symbol = a.symbol;
}

//Copy Assignmnet Constructor
objPos& objPos::operator=(const objPos &a){

   if(this != &a)
   {
        this->pos->x  = a.pos->x;       //Deep copy, heap already created for "this" object
        this->pos->y  = a.pos->y;
        this->symbol = a.symbol;
   }

    return *this;
}

void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const     //Checks x and y pos of a current objPos variable, compared to a
{                                                       //refrence pos which is passed as an argument. Then returns that pos
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const   //Calls isPosEqual to check if the current objPos variable has
{                                                              //the pos same as a reference pos (passed as an argument).  
    if(isPosEqual(refPos))                                     //If it is, then return the symbol of that variable
        return symbol;
    else
        return 0;
}
