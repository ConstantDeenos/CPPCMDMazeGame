#ifndef engineClass_h
#define engineClass_h

//Libraries
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <random>
#include <ncurses.h>

//Classes
#include "poterClass.h"
#include "poterClass.cpp"
#include "movingClass.h"
#include "movingClass.cpp"
#include "jewelClass.h"
#include "jewelClass.cpp"
#include "gnomeClass.h"
#include "gnomeClass.cpp"
#include "traalClass.h"
#include "traalClass.cpp"
#include "scrollClass.h"
#include "scrollClass.cpp"
#include "hiScoreClass.h"
#include "hiScoreClass.cpp"

using namespace std;

class Engine
{
private:
    Poter poter;
    Gnome gnome;
    Traal traal;
    Scroll scroll;
    vector<Jewel> jewels;
    vector<string> Map;
    int Round;
    int Score;
    string GameState;
    HiScore hiScore;
public:
    //Constructors and Destructor
    Engine();
    ~Engine();
public:
    //Getters and Setters
    vector<string> getMap();
    string getGameState();
    HiScore getHiScore();
    int getScore();
public:
    //General Methods
    void printCoordinates();
    void printMap();
    int checkCollision(int, int);
    void checkGameState(int, int);
    void nextRound();
    void coordinateMovements();
    void placePawnsInRandomPositions();
    void placeScrollInMap();
    void initiateWin();
    void movePawn(int, int, char);
};
#endif