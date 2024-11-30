#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
#include <iostream>
using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()      //Constructor
{
    arrayCapacity = ARRAY_MAX_CAP;  //Constructor assigns heap space because aList is a pointer of type objPos
    listSize = 0;                   //so the objPos has to be initialized on the heap
    aList = new objPos[ARRAY_MAX_CAP];  
   
}

objPosArrayList::objPosArrayList(int foodListSize)      //Constructor
{
    arrayCapacity = foodListSize;
    listSize = foodListSize;
    aList = new objPos[foodListSize];       //Same heap logic as default constructor
   
}

objPosArrayList::~objPosArrayList()     //Destructor 
{
    delete[] aList;
}

objPosArrayList::objPosArrayList(objPosArrayList const &arr)        //Copy constructor
{
    listSize = arr.listSize;
    arrayCapacity = arr.arrayCapacity;
    aList = new objPos[listSize];           //Deep copy by assigning new heap space for element copied to
    for(int i = 0; i < listSize; i++)
    {
        aList[i] = arr.aList[i];
    }
}

objPosArrayList& objPosArrayList::operator =(objPosArrayList const &arr)
{
    if(this != &arr)
    {
        
        this->listSize = arr.listSize;
        this->arrayCapacity = arr.arrayCapacity;
        for(int i = 0; i < listSize; i++)           //Deep copy, heap already created for "this" object
        {
            this->aList[i] = arr.aList[i];
        }
    }

    return *this;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout << "Array list is full" << endl;
    }

    for(int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i-1];
    }

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout << "Array list is full" << endl;
    }

    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
   if(listSize != arrayCapacity)
   {
        for(int i = 0; i < listSize; i++)
        {
            aList[i] = aList[i + 1];
        }
        listSize--;
   }
   
   else
   {    
        cout << "No head to delete" << endl;
   }
}  

void objPosArrayList::removeTail()
{
    if(listSize != 0)
    {
       listSize--;
    }

    else
    {    
        cout << "No tail to delete" << endl;
    }
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const     //Returns element of specified index, passed as an argument
{
    if(index >= 0 && index < listSize)
    {
        return aList[index];
    }

    else
    {
        cout << "Tried to get element of out of acccess index" << endl;
    }
}

void objPosArrayList::insertElement(int index, objPos food) const   //Inserts element at a specifed index, passed as an argument
{                                                                   //The inserted index is of type food, passed as an argument
    if(index >= 0 && index < listSize)
    {
       aList[index] = food ; 
    }

    else
    {
        cout << "Tried to insert element in out of acccess index" << endl;
    }
}