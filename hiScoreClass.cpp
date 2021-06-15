#include "hiScoreClass.h"

HiScore::HiScore(){
    //This constructor makes an empty leaderboard, with 5 positions.
    for (int i = 0; i < 5; i++){
        Scores.push_back(0);
        Names.push_back("Empty");
    }
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
    //Overloading the << operator to insert the name to the HiScore class/
    hiScore.Names.push_back(name);
    return hiScore;
}

HiScore &operator << (HiScore &hiScore, int &score){
    //Overloading the >> operator to insert the score to the HiScore class.
    hiScore.Scores.push_back(score);
    return hiScore;
}

void HiScore::startFileOperations(){
    string fileName = inputFileName();
    string username = Names.back();
    int score  = Scores.back();
    Names.pop_back();
    Scores.pop_back();
    
    readFile(fileName);
    int boolean = attemptAddScore(score, username);
    if (boolean == 1){
        writeFile(fileName);
        printw("You made it on the leaderboard!!!\n");
    } else {
        printw("You didn't make it on the leaderboard...\n");
    }
    refresh();
}

void HiScore::readFile(string fileName){
    ifstream file (fileName, ios::in | ios::binary);
    //Attempting to read the file
    if (file.is_open()){
        file.seekg(0, std::ios::end);
        if (file.tellg() != 0){
            file.seekg(0);

            //Reading the 5 score integers and inputing them to the score vector.
            for (int i = 0; i < 5; i++){
                int tempInt;
                file.read((char *) &tempInt, sizeof(int));
                Scores[i] = tempInt;
            }

            //Since the size of the name string is lost each time we write it into the file, we need to write the size as well.
            //Reading the sizes of the 5 name strings and temporarily storing them in the scores vector.
            vector<unsigned int> sizes;
            for (int i = 0; i < 5; i++){
                unsigned int tempInt;
                file.read((char *) &tempInt, sizeof(unsigned int));
                sizes.push_back(tempInt);
            }

            //Reading the 5 name string using the sizes we read before.
            for (int i = 0; i < 5; i++){
                string tempStr;
                tempStr.resize(sizes[i]); 
                file.read(&tempStr[0], tempStr.size());
                Names[i] = tempStr;
            }
        }
        file.close();
    }
}

void HiScore::writeFile(string fileName){
    //Write the data to the file. First it writes the 5 scores. Then the sizes of the 5 usernames and then the usernames.
    ofstream file (fileName, ios::out | ios::binary);

    for (int i = 0; i < 5; i++){
        file.write((char *) &Scores[i], sizeof(int));
    }
    
    for (int i = 0; i < 5; i++){
        unsigned int temp = Names[i].size();
        file.write((char *) &temp, sizeof(unsigned int));
    }

    for (int i = 0; i < 5; i++){
        file.write(Names[i].c_str(), Names[i].size());
    }

    file.close();
}

int HiScore::attemptAddScore(int score, string username){
    //Check if the score is big enough to fit in the leaderboard and if it is, it adds the score and the username. It also makes sure there are only 5 entries.
    int boolean = 0;
    for (int i = 0; i < 5; i++){
        if (score >= Scores[i]){
            Scores.insert(Scores.begin() + i, score);
            Names.insert(Names.begin() + i, username);
            Scores.pop_back();
            Names.pop_back();
            boolean = 1;
            break;
        } else {
            boolean = 0;
        }
    }

    return boolean;
}

string HiScore::inputFileName(){
    //Asks the player to input the name of the score file.
    noraw();
    clear();
    echo();
    keypad(stdscr, FALSE);

    string fileName;
    printw("Insert the name of the score file (for example file.dat): ");
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