
#ifndef BATTLESHIPS_SCOREBOARD_H
#define BATTLESHIPS_SCOREBOARD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class ScoreBoard {
    std::multimap<int, std::string> scorelist;
public:
    ScoreBoard();

    void AddNewScore(int &newScore, std::string &playerName);

    void ShowScoreBoard();

    void SaveScoreBoard();
};


#endif //BATTLESHIPS_SCOREBOARD_H
