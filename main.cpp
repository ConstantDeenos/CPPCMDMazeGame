#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <random>
#include <chrono>
#include <thread>

#include "engineClass.h"
#include "engineClass.cpp"

using namespace std;

int main(){
    using namespace std::this_thread;
    using namespace std::chrono;

    int gameQuit = 0;
    int selection = 1;
    int input;
    string gameType;
    //Initialise Screen, set up memory, clear the screen and some settings
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    do{
        do{
            clear();
            if (selection == 1){
                printw("> ");
            }
            printw("Play -Player vs Computer-\n");
            if (selection == 2){
                printw("> ");
            }
            printw("Play -Computer vs Computer-\n");
            if (selection == 3){
                printw("> ");
            }
            printw("Quit\n");
            refresh();
            input = getch();
            switch (input)
            {
            case KEY_UP:
                if (selection > 1){
                    selection--;
                }
                break;
            case KEY_DOWN:
                if (selection < 3){
                    selection++;
                }
                break;
            case 27:
                selection = 3;
                break;
            default:
                break;
            }
        } while (input != 10 && input != 27);

        switch (selection)
        {
        case 1:{
                gameType = "Player";

                Engine engine(gameType);
                engine.printMap();
                do{
                    engine.nextRound();
                }while(!(engine.getGameState() == "Win" || engine.getGameState() == "End" || engine.getGameState() == "Lost"));
            }
            break;
        case 2:{
                gameType = "COM";

                Engine engine(gameType);
                engine.printMap();
                do{
                    sleep_for(500ms);
                    engine.nextRound();
                }while(!(engine.getGameState() == "Win" || engine.getGameState() == "End" || engine.getGameState() == "Lost"));
            }
            break;
        case 3:
            gameType = "NONE";
            gameQuit = 1;
            break;
        default:
            break;
        }
    } while (gameQuit == 0);

    // string mapString = "map.txt";
    // Engine engine;
    // vector<string> map = engine.getMap();

    // engine.printMap();
    // do{
    //     engine.nextRound();
    // } while(!(engine.getGameState() == "Win" || engine.getGameState() == "End" || engine.getGameState() == "Lost"));
    clear();
    endwin();

    return 0;
}