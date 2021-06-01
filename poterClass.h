#ifndef poterClass_h
#define poterClass_h

#include <ncurses.h>

#include "movingClass.h"

class Poter : public Moving{
    private:

    public:
        Poter(){};
        ~Poter(){};
        Poter(int x, int y) : Moving(x, y){

        }
    public:
        int determineMovement();
};

#endif