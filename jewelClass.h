#ifndef jewelClass_h
#define jewelClass_h

#include <ncurses.h>

class Jewel
{
protected:
    int PositionX;
    int PositionY;
public:
    Jewel();
    ~Jewel();
    Jewel(int, int);
public:
    int getPositionX();
    int getPositionY();
    void setPositionX(int);
    void setPositionY(int);
public:
    void operator=(Jewel);
};

#endif