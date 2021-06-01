#include "jewelClass.h"

Jewel::Jewel(/* args */)
{
}

Jewel::~Jewel()
{
}

Jewel::Jewel(int x, int y){
    PositionX = x;
    PositionY = y;
}

int Jewel::getPositionX(){
    return PositionX;
}

int Jewel::getPositionY(){
    return PositionY;
}

void Jewel::setPositionX(int x){
    PositionX = x;
}

void Jewel::setPositionY(int y){
    PositionY = y;
}


void Jewel::operator=(Jewel jewel){
    PositionX = jewel.getPositionX();
    PositionY = jewel.getPositionY();
}