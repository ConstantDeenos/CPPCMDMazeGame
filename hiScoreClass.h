#ifndef hiScoreClass_h
#define hiScoreClass_h

#include <vector>
#include <string>
#include <ostream>

using namespace std;

class HiScore
{
private:
    vector<string> Names;
    vector<int> Scores;
public:
    HiScore();
    ~HiScore();
public:
    vector<string> getNames();
    vector<int> getScores();
public:
    friend HiScore &operator << (HiScore &hiScore, string &name);
    friend HiScore &operator << (HiScore &hiScore, int &score);
};

#endif