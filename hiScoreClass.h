#ifndef hiScoreClass_h
#define hiScoreClass_h

#include <vector>
#include <string>

using namespace std;

class HiScore
{
private:
    vector<string> Names;
    vector<int> Scores;
public:
    HiScore();
    ~HiScore();
};

#endif