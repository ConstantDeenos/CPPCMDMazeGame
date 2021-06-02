#include "movingClass.h"

Moving::Moving(/* args */)
{
    
}

Moving::~Moving()
{
}

Moving::Moving(int x, int y){
    PositionX = x;
    PositionY = y;
}

void Moving::MoveLeft(){
    PositionX--;
}

void Moving::MoveRight(){
    PositionX++;
}
void Moving::MoveUp(){
    PositionY--;
}

void Moving::MoveDown(){
    PositionY++;
}

int Moving::getPositionX(){
    return PositionX;
}

int Moving::getPositionY(){
    return PositionY;
}

void Moving::operator=(Moving moving){
    PositionX = moving.getPositionX();
    PositionY = moving.getPositionY();
}