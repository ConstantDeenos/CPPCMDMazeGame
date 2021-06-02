#include "hiScoreClass.h"

HiScore::HiScore(){

}

HiScore::~HiScore(){
    
}

HiScore &operator << (HiScore &hiScore, string &name){
    hiScore.Names.push_back(name);
    return hiScore;
}

HiScore &operator << (HiScore &hiScore, int &score){
    hiScore.Scores.push_back(score);
    return hiScore;
}