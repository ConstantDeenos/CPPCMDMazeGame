#ifndef movingClass_h
#define movingClass_h

#include <ncurses.h>

class Moving
{
protected:
    int PositionX;
    int PositionY;
public:
    Moving();
    ~Moving();
    Moving(int, int);
public:
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    int getPositionX();
    int getPositionY();
public:
    void operator=(Moving);
};

#endif