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
    Engine engine;
    vector<string> map = engine.getMap();

    //Initialise Screen, set up memory, clear the screen and some settings
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    
    engine.printMap();
    int tempMoves = 0; //Temporary for ending of game
    do{
        tempMoves++;
        engine.nextRound();
    } while(!(engine.getGameState() == "Win" || engine.getGameState() == "End" || engine.getGameState() == "Lost"));

    //Deallocates memory and ends ncurses
    endwin();

    return 0;
}