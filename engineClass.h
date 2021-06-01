#ifndef engineClass_h
#define engineClass_h

#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <random>
#include <ncurses.h>

#include "poterClass.h"
#include "poterClass.cpp"
#include "movingClass.h"
#include "movingClass.cpp"

using namespace std;

class Engine
{
private:
    Poter poter;
    vector<string> Map;
    int x, y;
public:
    Engine();
    ~Engine();
public:
    vector<string> getMap();
    void printCoordinates();
    void printMap();
    int checkCollision(int, int);
    void nextRound();
};
#endif