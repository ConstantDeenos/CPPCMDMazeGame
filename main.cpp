#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <random>

#include "engineClass.h"
#include "engineClass.cpp"

using namespace std;

int main(){
    //Initialise Screen, set up memory, clear the screen and some settings
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    string mapString = "map.txt";
    Engine engine;
    vector<string> map = engine.getMap();

    engine.printMap();
    do{
        engine.nextRound();
    } while(!(engine.getGameState() == "Win" || engine.getGameState() == "End" || engine.getGameState() == "Lost"));

    endwin();
    cout<<engine.getGameState();

    return 0;
}