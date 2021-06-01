#include "scrollClass.h"

Scroll::Scroll(/* args */)
{
}

Scroll::~Scroll()
{
}

Scroll::Scroll(int x, int y){
    PositionX = x;
    PositionY = y;
}

int Scroll::getPositionX(){
    return PositionX;
}

int Scroll::getPositionY(){
    return PositionY;
}

void Scroll::setPositionX(int x){
    PositionX = x;
}

void Scroll::setPositionY(int y){
    PositionY = y;
}


void Scroll::operator=(Scroll scroll){
    PositionX = scroll.getPositionX();
    PositionY = scroll.getPositionY();
}