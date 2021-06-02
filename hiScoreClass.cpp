#include "hiScoreClass.h"

HiScore::HiScore(){

}

HiScore::~HiScore(){
    
}

vector<string> HiScore::getNames(){
    return Names;
}

vector<int> HiScore::getScores(){
    return Scores;
}

HiScore &operator << (HiScore &hiScore, string &name){
    hiScore.Names.push_back(name);
    return hiScore;
}

HiScore &operator << (HiScore &hiScore, int &score){
    hiScore.Scores.push_back(score);
    return hiScore;
}