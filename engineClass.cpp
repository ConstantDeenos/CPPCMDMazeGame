#include "engineClass.h"

Engine::Engine(string gameType){
    //Map Reading and assignment to vector of strings
    string mapLine;
    ifstream mapFile (inputFileName().data());
    if (!mapFile.is_open()){
        perror("Error while opening file");
        exit(1);
    }

    if (mapFile.bad()){
        perror("Errow while reading file");
        exit(2);
    }

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
    GameType = gameType;

    placePawnsInRandomPositions();

    mapFile.close();
}

void Engine::setGameType(string gameType){
    GameType = gameType;
}

Engine::~Engine(){

}

vector<string> Engine::getMap(){
    return Map;
}

string Engine::getGameState(){
    return GameState;
}

int Engine::getScore(){
    return Score;
}

HiScore Engine::getHiScore(){
    return hiScore;
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

void Engine::checkGameState(int x, int y, char pawn){
    if (pawn == 'P'){
        if (x == traal.getPositionX() && y == traal.getPositionY())
        {
            GameState = "Lost";
        }
        else if (x == gnome.getPositionX() && y == gnome.getPositionY())
        {
            GameState = "Lost";
        }

        for (int i = 0; i < 10; i++)
        {
            if (x == jewels[i].getPositionX() && y == jewels[i].getPositionY())
            {
                jewels[i].setPositionX(0);
                jewels[i].setPositionY(0);
                Score = Score + 10;
            }
        }

        if (x == scroll.getPositionX() && y == scroll.getPositionY())
        {
            scroll.setPositionX(0);
            scroll.setPositionY(0);
            Score = Score + 100;
            GameState = "Win";
        }
    } else if (pawn == 'T' || pawn == 'G') {
        if (poter.getPositionX() == x && poter.getPositionY() == y){
            GameState = "Lost";
        }
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
    uniform_int_distribution<int> distrX(1, Map[0].size() - 1); //Remember to change the limits for the size of the new map and make it dynamic not a single int
    uniform_int_distribution<int> distrY(1, Map.size() - 1); //Remember to change the limits for the size of the new map and make it dynamic not a single int
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
                    for (int j = 0; j < jewels.size(); j++){
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
    movePawn(poter.getPositionX(), poter.getPositionY(), 'P');
    
    if (GameState != "Lost"){
        movePawn(traal.getPositionX(), traal.getPositionY(), 'T');
    }
    
    if (GameState != "Lost"){
        movePawn(gnome.getPositionX(), gnome.getPositionY(), 'G');
    }

    if (Score == 100){
        placeScrollInMap();
    }
}

void Engine::movePawn(int x, int y, char pawn){
    int input, valid, validKeyPress = 0;

    do{
        switch (pawn)
        {
        case 'P':
            if (GameType == "Player"){
                input = poter.getMovementFromKeyboard();
            } else if (GameType == "COM"){
                input = poter.determineMovement(Map);
            }
            break;
        case 'T':
            input = traal.determineMovement(Map);
            break;
        case 'G':
            input = gnome.determineMovement(Map);
            break;
        default:
            break;
        }
        int isJemOrScroll = 0;
        switch (input){
        case KEY_LEFT:
            valid = checkCollision(x - 1, y);
            checkGameState(x - 1, y, pawn);
            if (valid == 1){
                Map[y].erase(Map[y].begin() + x);
                // Checking if the pawn is a monster and if it is and its standing on a scoll or jewel, it makes the jewel or scroll reappear when the monster is gone from the position
                if (pawn == 'T'){
                    for (int i = 0; i < jewels.size(); i++){
                        if (traal.getPositionX() == jewels[i].getPositionX() && traal.getPositionY() == jewels[i].getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'J');
                            isJemOrScroll = 1;
                        } else if (traal.getPositionX() == scroll.getPositionX() && traal.getPositionY() == scroll.getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'S');
                            isJemOrScroll = 1;
                        }
                    }
                } else if (pawn == 'G') {
                    for (int i = 0; i < jewels.size(); i++){
                        if (gnome.getPositionX() == jewels[i].getPositionX() && gnome.getPositionY() == jewels[i].getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'J');
                            isJemOrScroll = 1;
                        } else if (gnome.getPositionX() == scroll.getPositionX() && gnome.getPositionY() == scroll.getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'S');
                            isJemOrScroll = 1;
                        }
                    }
                }

                if (isJemOrScroll == 0){
                    Map[y].insert(Map[y].begin() + x, ' ');
                }

                if (pawn == 'P'){
                    poter.MoveLeft();
                    x = poter.getPositionX();
                    y = poter.getPositionY();
                } else if (pawn == 'T'){
                    traal.MoveLeft();
                    x = traal.getPositionX();
                    y = traal.getPositionY();
                } else if (pawn == 'G'){
                    gnome.MoveLeft();
                    x = gnome.getPositionX();
                    y = gnome.getPositionY();
                }

                Map[y].erase(Map[y].begin() + x);
                Map[y].insert(Map[y].begin() + x, pawn);
                validKeyPress = 1;
            }
            break;
        case KEY_RIGHT:
            valid = checkCollision(x + 1, y);
            checkGameState(x + 1, y, pawn);
            if (valid == 1){
                Map[y].erase(Map[y].begin() + x);
                // Checking if the pawn is a monster and if it is and its standing on a scoll or jewel, it makes the jewel or scroll reappear when the monster is gone from the position
                if (pawn == 'T'){
                    for (int i = 0; i < jewels.size(); i++){
                        if (traal.getPositionX() == jewels[i].getPositionX() && traal.getPositionY() == jewels[i].getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'J');
                            isJemOrScroll = 1;
                        } else if (traal.getPositionX() == scroll.getPositionX() && traal.getPositionY() == scroll.getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'S');
                            isJemOrScroll = 1;
                        }
                    }
                } else if (pawn == 'G') {
                    for (int i = 0; i < jewels.size(); i++){
                        if (gnome.getPositionX() == jewels[i].getPositionX() && gnome.getPositionY() == jewels[i].getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'J');
                            isJemOrScroll = 1;
                        } else if (gnome.getPositionX() == scroll.getPositionX() && gnome.getPositionY() == scroll.getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'S');
                            isJemOrScroll = 1;
                        }
                    }
                }

                if (isJemOrScroll == 0){
                    Map[y].insert(Map[y].begin() + x, ' ');
                }
                
                if (pawn == 'P'){
                    poter.MoveRight();
                    x = poter.getPositionX();
                    y = poter.getPositionY();
                } else if (pawn == 'T'){
                    traal.MoveRight();
                    x = traal.getPositionX();
                    y = traal.getPositionY();
                } else if (pawn == 'G'){
                    gnome.MoveRight();
                    x = gnome.getPositionX();
                    y = gnome.getPositionY();
                }

                Map[y].erase(Map[y].begin() + x);
                Map[y].insert(Map[y].begin() + x, pawn);
                validKeyPress = 1;
            }
            break;
        case KEY_UP:
            valid = checkCollision(x, y - 1);
            checkGameState(x, y - 1, pawn);
            if (valid == 1){
                Map[y].erase(Map[y].begin() + x);
                // Checking if the pawn is a monster and if it is and its standing on a scoll or jewel, it makes the jewel or scroll reappear when the monster is gone from the position
                if (pawn == 'T'){
                    for (int i = 0; i < jewels.size(); i++){
                        if (traal.getPositionX() == jewels[i].getPositionX() && traal.getPositionY() == jewels[i].getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'J');
                            isJemOrScroll = 1;
                        } else if (traal.getPositionX() == scroll.getPositionX() && traal.getPositionY() == scroll.getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'S');
                            isJemOrScroll = 1;
                        }
                    }
                } else if (pawn == 'G') {
                    for (int i = 0; i < jewels.size(); i++){
                        if (gnome.getPositionX() == jewels[i].getPositionX() && gnome.getPositionY() == jewels[i].getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'J');
                            isJemOrScroll = 1;
                        } else if (gnome.getPositionX() == scroll.getPositionX() && gnome.getPositionY() == scroll.getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'S');
                            isJemOrScroll = 1;
                        }
                    }
                }

                if (isJemOrScroll == 0){
                    Map[y].insert(Map[y].begin() + x, ' ');
                }
                
                if (pawn == 'P'){
                    poter.MoveUp();
                    x = poter.getPositionX();
                    y = poter.getPositionY();
                } else if (pawn == 'T'){
                    traal.MoveUp();
                    x = traal.getPositionX();
                    y = traal.getPositionY();
                } else if (pawn == 'G'){
                    gnome.MoveUp();
                    x = gnome.getPositionX();
                    y = gnome.getPositionY();
                }

                Map[y].erase(Map[y].begin() + x);
                Map[y].insert(Map[y].begin() + x, pawn);
                validKeyPress = 1;
            }
            break;
        case KEY_DOWN:
            valid = checkCollision(x, y + 1);
            checkGameState(x, y + 1, pawn);
            if (valid == 1){
                Map[y].erase(Map[y].begin() + x);
                // Checking if the pawn is a monster and if it is and its standing on a scoll or jewel, it makes the jewel or scroll reappear when the monster is gone from the position
                if (pawn == 'T'){
                    for (int i = 0; i < jewels.size(); i++){
                        if (traal.getPositionX() == jewels[i].getPositionX() && traal.getPositionY() == jewels[i].getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'J');
                            isJemOrScroll = 1;
                        } else if (traal.getPositionX() == scroll.getPositionX() && traal.getPositionY() == scroll.getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'S');
                            isJemOrScroll = 1;
                        }
                    }
                } else if (pawn == 'G') {
                    for (int i = 0; i < jewels.size(); i++){
                        if (gnome.getPositionX() == jewels[i].getPositionX() && gnome.getPositionY() == jewels[i].getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'J');
                            isJemOrScroll = 1;
                        } else if (gnome.getPositionX() == scroll.getPositionX() && gnome.getPositionY() == scroll.getPositionY()){
                            Map[y].insert(Map[y].begin() + x, 'S');
                            isJemOrScroll = 1;
                        }
                    }
                }

                if (isJemOrScroll == 0){
                    Map[y].insert(Map[y].begin() + x, ' ');
                }
                
                if (pawn == 'P'){
                    poter.MoveDown();
                    x = poter.getPositionX();
                    y = poter.getPositionY();
                } else if (pawn == 'T'){
                    traal.MoveDown();
                    x = traal.getPositionX();
                    y = traal.getPositionY();
                } else if (pawn == 'G'){
                    gnome.MoveDown();
                    x = gnome.getPositionX();
                    y = gnome.getPositionY();
                }

                Map[y].erase(Map[y].begin() + x);
                Map[y].insert(Map[y].begin() + x, pawn);
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

void Engine::initiateWin(){
    noraw();
    clear();
    echo();
    keypad(stdscr, FALSE);

    string username;
    printw("Insert your username (Maximum 10 letters): ");
    int ch = getch();
    while (ch != '\n' && username.size() <= 10)
    {
        username.push_back(ch);
        ch = getch();
    }

    hiScore<<username<<Score;
    hiScore.startFileOperations();

    for (int i = 0; i < hiScore.getNames().size(); i++)
    {
        printw("%d. Name: ", i+1);
        printw(hiScore.getNames()[i].data());
        printw(" Score: %d", hiScore.getScores()[i]);
    }
    printw("\nPress any key to continue...");
    raw();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
    getch();
}

string Engine::inputFileName(){
    noraw();
    clear();
    echo();
    keypad(stdscr, FALSE);

    string fileName;
    printw("Insert the name of the map file (for example map.txt): ");
    refresh();
    char ch = getch();
    while (ch != '\n')
    {
        fileName.push_back(ch);
        ch = getch();
    }
    raw();
    keypad(stdscr, TRUE);
    noecho();
    clear();
    refresh();

    return fileName;
}

void Engine::nextRound(){
    coordinateMovements();
    clear();
    printMap();
    refresh();
    Round++;

    if(GameState == "Win"){
        initiateWin();
    }

    if (GameState == "Lost"){
        clear();
        printw("You Lost. Your score was %d.\nPress any key to Continue...", Score);
        refresh();
        getch();
    }
}