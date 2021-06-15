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
    
    //Check if command line supports colors and if so create color pairs
    if (has_colors() != 0){
        start_color();
        init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_RED, COLOR_BLACK);
    }

    //Loop for multiple rounds
    do{
        //Loop for menu
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
                //Escape Case
                selection = 3;
                break;
            default:
                break;
            }
        } while (input != 10 && input != 27);

        //Switch for the selection the user made from the menu
        switch (selection)
        {
        case 1:{
                //Case for player being a human
                gameType = "Player";

                Engine engine(gameType);
                engine.printMap();
                do{
                    engine.nextRound();
                }while(!(engine.getGameState() == "Win" || engine.getGameState() == "End" || engine.getGameState() == "Lost"));
            }
            break;
        case 2:{
                //Case for the player being a bot
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
            //Case for quitting game
            gameType = "NONE";
            gameQuit = 1;
            break;
        default:
            break;
        }
    } while (gameQuit == 0);

    //Clearing and closing the window when the game ends
    clear();
    endwin();

    return 0;
}