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

    Round = 0;
    Score = 0;
    GameState = "Starting";

    placePawnsInRandomPositions();
}

Engine::~Engine(){

}

vector<string> Engine::getMap(){
    return Map;
}

string Engine::getGameState(){
    return GameState;
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

void Engine::checkGameState(int x, int y){
    if (x == traal.getPositionX() && y == traal.getPositionY()){
        GameState = "Lost";
    } else if (x == gnome.getPositionX() && y == gnome.getPositionY()){
        GameState = "Lost";
    }

    for (int i = 0; i < 10; i++){
        if (x == jewels[i].getPositionX() && y == jewels[i].getPositionY()){
            jewels[i].setPositionX(0);
            jewels[i].setPositionY(0);
            Score = Score + 10;
        }
    }

    if (x == scroll.getPositionX() && y == scroll.getPositionY()){
        scroll.setPositionX(0);
        scroll.setPositionY(0);
        Score = Score + 100;
        GameState = "Win";
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

void Engine::placePawnsInRandomPositions(){
    //Random Number Generator
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> distrX(1, 9); //Remember to change the limits for the size of the new map and make it dynamic not a single int
    uniform_int_distribution<int> distrY(1, 5); //Remember to change the limits for the size of the new map and make it dynamic not a single int
    if (Round == 0){
        //Place Player on Map
        int valid = 0;
        int x, y;
        do
        {
            x = distrX(eng);
            y = distrY(eng);
            valid = checkCollision(x, y);
        } while (valid == 0);
        Poter tempPoter(x, y);
        Map.at(y).at(x) = 'P';
        poter = tempPoter;

        //Place Jewels on Map
        for(int i = 0; i < 10; i++){
            valid = 0;
            x = y = 0;
            do
            {
                x = distrX(eng);
                y = distrY(eng);
                valid = checkCollision(x, y);
                if (x == poter.getPositionX() && y == poter.getPositionY())
                {
                    valid = 0;
                } else if (i != 0){
                    for (int j = 0; j < jewels.size() - 1; j++){
                        if (x == jewels[j].getPositionX() && y == jewels[j].getPositionY()){
                            valid = 0;
                        }
                    }
                }
            } while (valid == 0);
            Jewel tempJewel(x, y);
            jewels.push_back(tempJewel);
            Map.at(y).at(x) = 'J';
        }

        //Place Traal on Map
        valid = 0;
        x = y = 0;
        do
        {
            x = distrX(eng);
            y = distrY(eng);
            valid = checkCollision(x, y);
            if (x == poter.getPositionX() && y == poter.getPositionY()){
                valid = 0;
            } else{
                for (int i = 0; i < 10; i++){
                    if (x == jewels[i].getPositionX() && jewels[i].getPositionY()){
                        valid = 0;
                    }
                }
            }
        } while (valid == 0);
        Traal tempTraal(x, y);
        traal = tempTraal;
        Map.at(y).at(x) = 'T';
        
        //Place Gnome on Map
        valid = 0;
        x = y = 0;
        do
        {
            x = distrX(eng);
            y = distrY(eng);
            valid = checkCollision(x, y);
            if (x == poter.getPositionX() && y == poter.getPositionY()){
                valid = 0;
            } else{
                for (int i = 0; i < 10; i++){
                    if (x == jewels[i].getPositionX() && jewels[i].getPositionY()){
                        valid = 0;
                    }
                }
            }
        } while (valid == 0);
        Gnome tempGnome(x, y);
        gnome = tempGnome;
        Map.at(y).at(x) = 'G';
        GameState = "Jewels";
    }
}

void Engine::coordinateMovements(){
    int valid, validKeyPress = 0;
    
    do{
        int input = poter.determineMovement();
        switch (input){
        case KEY_LEFT:
            valid = checkCollision(poter.getPositionX() - 1, poter.getPositionY());
            checkGameState(poter.getPositionX() - 1, poter.getPositionY());
            if (valid == 1){
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX());
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX() - 1);
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX() - 1, 'P');
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX(), ' ');
                poter.MoveLeft();
                validKeyPress = 1;
            }
            break;
        case KEY_RIGHT:
            valid = checkCollision(poter.getPositionX() + 1, poter.getPositionY());
            checkGameState(poter.getPositionX() + 1, poter.getPositionY());
            if (valid == 1){
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX() + 1);
                Map.at(poter.getPositionY()).erase(Map.at(poter.getPositionY()).begin() + poter.getPositionX());
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX(), ' ');
                Map.at(poter.getPositionY()).insert(Map.at(poter.getPositionY()).begin() + poter.getPositionX() + 1, 'P');
                poter.MoveRight();
                validKeyPress = 1;
            }
            break;
        case KEY_UP:
            valid = checkCollision(poter.getPositionX(), poter.getPositionY() - 1);
            checkGameState(poter.getPositionX(), poter.getPositionY() - 1);
            if (valid == 1){
                Map[poter.getPositionY()].erase(Map[poter.getPositionY()].begin() + poter.getPositionX());
                Map[poter.getPositionY()].insert(Map[poter.getPositionY()].begin() + poter.getPositionX(), ' ');
                poter.MoveUp();
                Map[poter.getPositionY()].erase(Map[poter.getPositionY()].begin() + poter.getPositionX());
                Map[poter.getPositionY()].insert(Map[poter.getPositionY()].begin() + poter.getPositionX(), 'P');
                validKeyPress = 1;
            }
            break;
        case KEY_DOWN:
            valid = checkCollision(poter.getPositionX(), poter.getPositionY() + 1);
            checkGameState(poter.getPositionX(), poter.getPositionY() + 1);
            if (valid == 1){
                Map[poter.getPositionY()].erase(Map[poter.getPositionY()].begin() + poter.getPositionX());
                Map[poter.getPositionY()].insert(Map[poter.getPositionY()].begin() + poter.getPositionX(), ' ');
                poter.MoveDown();
                Map[poter.getPositionY()].erase(Map[poter.getPositionY()].begin() + poter.getPositionX());
                Map[poter.getPositionY()].insert(Map[poter.getPositionY()].begin() + poter.getPositionX(), 'P');
                validKeyPress = 1;
            }
            break;
        case ' ':
            validKeyPress = 1;
            break;
        case 27:
            validKeyPress = 1;
            GameState = "End";
            break;
        default:
            validKeyPress = 0;
            break;
        }
    } while (validKeyPress == 0);
    if (Score == 100){
        placeScrollInMap();
    }
}

void Engine::placeScrollInMap()
{
    if (GameState != "Scroll") //Checking if a scroll has already been placed
    {
        int valid = 0;
        int x = 0;
        int y = 0;

        //Random Number Generator
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<int> distrX(1, 9); //Remember to change the limits for the size of the new map and make it dynamic not a single int
        uniform_int_distribution<int> distrY(1, 5); //Remember to change the limits for the size of the new map and make it dynamic not a single int

        do
        {
            x = distrX(eng);
            y = distrY(eng);
            valid = checkCollision(x, y);
            if (x == poter.getPositionX() && y == poter.getPositionY())
            {
                valid = 0;
            }
            else if (x == traal.getPositionX() && y == traal.getPositionY())
            {
                valid = 0;
            }
            else if (x == gnome.getPositionX() && y == gnome.getPositionY())
            {
                valid = 0;
            }
            else
            {
                for (int i = 0; i < 10; i++)
                {
                    if (x == jewels[i].getPositionX() && jewels[i].getPositionY())
                    {
                        valid = 0;
                    }
                }
            }
        } while (valid == 0);
        Scroll tempScroll(x, y);
        scroll = tempScroll;
        Map.at(y).at(x) = 'S';
        GameState = "Scroll";
    }
}

void Engine::nextRound(){
    cout<<Score<<endl;
    coordinateMovements();
    clear();
    printMap();
    refresh();
    Round++;
}