#include "engineClass.h"

Engine::Engine(){
    //Map Reading and assignment to vector of strings
    string mapLine;
    ifstream mapFile ("map.txt");
    if (mapFile.is_open()){
        while (getline(mapFile, mapLine)){
            if (mapLine.size() > 0){
                Map.push_back(mapLine);
            }
        }
    }

    //Random Number Generator
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> distrX(1,9); //Remember to change the limits for the size of the new map and make it dynamic not a single int
    uniform_int_distribution<int> distrY(1,5); //Remember to change the limits for the size of the new map and make it dynamic not a single int

    //Place pawn in map
    int valid = 0;
    do{
        x = distrX(eng);
        y = distrY(eng);
        valid = checkCollision(x, y);
    } while (valid = 0);
    Poter tempPoter(x, y);
    Map.at(y).at(x) = 'p';
    poter = tempPoter;
}

Engine::~Engine(){

}

vector<string> Engine::getMap(){
    return Map;
}

void Engine::printCoordinates(){
}

int Engine::checkCollision(int x, int y){
    if(Map.at(y).at(x) != '*'){
        return 1;
    } else {
        return 0;
    }
}

void Engine::printMap(){
    //Printing the map
    for (int i = 0; i < Map.size(); i++){
        printw(Map[i].data());
        printw("\n");
    }
    refresh();
}

void Engine::nextRound(){
    int valid, validKeyPress = 0;
    do{
        int input = getch();
        switch (input){
        case KEY_LEFT:
            valid = checkCollision(poter.getPositionX() - 1, poter.getPositionY());
            if (valid == 1){
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX());
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX() - 1);
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX() - 1, 'p');
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX(), ' ');
                poter.MoveLeft();
                validKeyPress = 1;
            }
            break;
        case KEY_RIGHT:
            valid = checkCollision(poter.getPositionX() + 1, poter.getPositionY());
            if (valid == 1){
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX() + 1);
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX());
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX(), ' ');
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX() + 1, 'p');
                poter.MoveRight();
                validKeyPress = 1;
            }
            break;
        case KEY_UP:
            valid = checkCollision(poter.getPositionX(), poter.getPositionY() - 1);
            if (valid == 1){
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX());
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX(), ' ');
                Map.at(poter.getPositionY() - 1).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX());
                Map.at(poter.getPositionY() - 1).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX(), 'p');
                poter.MoveUp();
                validKeyPress = 1;
            }
            break;
        case KEY_DOWN:
            valid = checkCollision(poter.getPositionX(), poter.getPositionY() + 1);
            if (valid == 1){
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX());
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX(), ' ');
                Map.at(poter.getPositionY() + 1).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX());
                Map.at(poter.getPositionY() + 1).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX(), 'p');
                poter.MoveDown();
                validKeyPress = 1;
            }
            break;
        default:
            validKeyPress = 0;
            break;
        }
    } while (validKeyPress == 0);
    clear();
    printMap();
    refresh();
}

// int ch = getch();
    // char character = '*';

    // if (ch == character){
    //     printw("Yes *");
    // } else {
    //     printw("%d %d", ch, character);
    // }