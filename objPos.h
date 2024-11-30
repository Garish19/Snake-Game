#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;      //Pointer to 2 a struct pos, has 2 int values, x and y  
        char symbol;

        objPos();   //Constructor 
        objPos(int xPos, int yPos, char sym);
        
        ~objPos();    //Destructor

        objPos(const objPos &a);    //Copy Constructor

        objPos& operator=(const objPos &a);     //Copy Assignment Operator

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;
};

#endif