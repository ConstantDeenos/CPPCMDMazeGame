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
#include "jewelClass.h"
#include "jewelClass.cpp"
#include "gnomeClass.h"
#include "gnomeClass.cpp"

using namespace std;

class Engine
{
private:
    Poter poter;
    Gnome gnome;
    vector<Jewel> jewels;
    vector<string> Map;
    int Round;
public:
    Engine();
    ~Engine();
public:
    vector<string> getMap();
    void printCoordinates();
    void printMap();
    int checkCollision(int, int);
    void nextRound();
    void coordinateMovements();
    void placePawnsInRandomPositions();
};
#endif