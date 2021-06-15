#ifndef poterClass_h
#define poterClass_h

#include <ncurses.h>
#include <vector>
#include <string>
#include "movingClass.h"
using namespace std;
class Poter : public Moving{
    private:

    public:
        Poter(){};
        ~Poter(){};
        Poter(int x, int y) : Moving(x, y){

        }
    public:
        int determineMovement(std::vector<std::string>);
        int getMovementFromKeyboard();
};

#endif