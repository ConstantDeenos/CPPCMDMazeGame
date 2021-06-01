#ifndef gnomeClass_h
#define gnomeClass_h

#include <ncurses.h>

#include "movingClass.h"

class Gnome : public Moving{
    private:

    public:
        Gnome(){};
        ~Gnome(){};
        Gnome(int x, int y) : Moving(x, y){

        }
    public:
        int determineMovement();
};

#endif