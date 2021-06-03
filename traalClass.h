#ifndef traalClass_h
#define traalClass_h

#include <ncurses.h>
#include <fstream>

#include "movingClass.h"

class Traal : public Moving{
    private:

    public:
        Traal(){};
        ~Traal(){};
        Traal(int x, int y) : Moving(x, y){

        }
    public:
        int determineMovement(vector<string>, int, int);
};

#endif