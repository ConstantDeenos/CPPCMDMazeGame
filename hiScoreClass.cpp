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
    hiScore.organise();
    return hiScore;
}

void HiScore::organise(){
    for (int i = 0; i < Scores.size() - 1; i++)
    {
        if (Scores[i] > Scores[i+1]){
            int tempScore = Scores[i];
            Scores[i] = Scores[i+1];
            Scores[i+1] = tempScore;

            string tempName = Names[i];
            Names[i] = Names[i+1];
            Names[i+1] = tempName;
            i = 0;
        }
    }
}