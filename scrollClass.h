#ifndef srcollClass_h
#define srcollClass_h

#include <ncurses.h>

class Scroll
{
protected:
    int PositionX;
    int PositionY;
public:
    Scroll();
    ~Scroll();
    Scroll(int, int);
public:
    int getPositionX();
    int getPositionY();
    void setPositionX(int);
    void setPositionY(int);
public:
    void operator=(Scroll);
};

#endif