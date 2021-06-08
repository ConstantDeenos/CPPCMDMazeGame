#include "gnomeClass.h"

int Gnome::determineMovement(vector<string> map){
    int movement = 0;
    vector<vector<int>> moves;

    //Map translation to int
    for (int i = 0; i<map.size(); i++){
        vector<int> line;
        for (int j = 0; j<map[0].size(); j++){
            if (map[i][j] == 'P'){
                line.push_back(0);
            } else if (map[i][j] == '*'){
                line.push_back(-1);
            } else if (map[i][j] == 'G') {
                line.push_back(-2);
            } else {
                line.push_back(-3);
            }
        }
        moves.push_back(line);
    }

    do{
        for (int i = 1; i < moves.size() - 1; i++){
            for (int j = 1; j < moves[0].size() - 1; j++){
                if (moves[i][j] >= 0){
                    if (moves[i][j - 1] == -2){
                        movement = KEY_RIGHT;
                        break;
                    } else if (moves[i][j-1] == -3){
                        moves[i][j - 1] = moves[i][j] + 1;
                    }

                    if (moves[i][j + 1] == -2){
                        movement = KEY_LEFT;
                        break;
                    } else if (moves[i][j + 1] == -3){
                        moves[i][j + 1] = moves[i][j] + 1;
                    }

                    if (moves[i - 1][j] == -2){
                        movement = KEY_DOWN;
                        break;
                    } else if (moves[i - 1][j] == -3){
                        moves[i - 1][j] = moves[i][j] + 1;
                    }

                    if (moves[i + 1][j] == -2){
                        movement = KEY_UP;
                        break;
                    } else if (moves[i + 1][j] == -3){
                        moves[i + 1][j] = moves[i][j] + 1;
                    }
                }
            }
            if (movement != 0){
                break;
            }
        }
    } while(movement == 0);
    
    return movement;
}