#include "traalClass.h"

int Traal::determineMovement(vector<string>map, int x, int y){
    int movement = 0;
    // vector<vector<int>> moves;
    // vector<int> temp;
    // temp.push_back(y);
    // temp.push_back(x);
    // moves.push_back(temp);

    // do{
    //     for (int i = 0; i < moves.size(); i++)
    //     {
    //         for (int j = 0; j < moves[i].size(); j = j + 2)
    //         {
    //             vector<int> tempInt;
    //             if (map[moves[i]][moves[i+1] - 1] != '*' ){
    //                 tempInt.push_back(moves[i]);
    //                 tempInt.push_back(moves[i+1] - 1);
    //             }
    //             if (map[moves[i]][moves[i+1] + 1] != '*' ){
    //                 vector<int> tempInt;
    //                 tempInt.push_back(moves[i]);
    //                 tempInt.push_back(moves[i+1] + 1);
    //             }
    //             if (map[moves[i] - 1][moves[i+1]] != '*' ){
    //                 vector<int> tempInt;
    //                 tempInt.push_back(moves[i] - 1);
    //                 tempInt.push_back(moves[i+1]);
    //             }
    //             if (map[moves[i] + 1][moves[i+1]] != '*' ){
    //                 vector<int> tempInt;
    //                 tempInt.push_back(moves[i] + 1);
    //                 tempInt.push_back(moves[i+1]);
    //             }
    //             moves.push_back(tempInt);
    //             for (int k = 0; k < tempInt.size(); k = k + 2)
    //             {
    //                 if (PositionX + 1 == tempInt[k+1] && PositionY == tempInt[k]){
    //                     movement = 2;
    //                     break;
    //                 } else if (PositionX - 1 == tempInt[k+1] && PositionY == tempInt[k]){
    //                     movement = 1;
    //                 } else if (PositionX == tempInt[k+1] && PositionY - 1 == tempInt[k]){
    //                     movement = 3;
    //                 } else if (PositionX == tempInt[k+1] && PositionY + 1 == tempInt[k]){
    //                     movement = 4;
    //                 }
    //             }
    //             if (movement != 0){
    //                 break;
    //             }
                
    //         }
    //         if (movement != 0){
    //             break;
    //         }
    //     }
    // } while (movement == 0);

    // char test;
    // ofstream file;
    // file.open("mapOutputTraal.txt");
    // for ( int i = 0; i < moves.size(); i++){
    //     for ( int j = 0; j < moves[i].size(); j = j + 2){
    //         file<<i<<" : ("<<moves[i][j]<<", "<<moves[i][j+1]<<")"<<endl;
    //     }
    // }
    
    return movement;
}