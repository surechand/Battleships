
#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(){
    std::ifstream scoreFile;
    scoreFile.open("../ScoreBoard.txt");
    std::string name;
    int score;
    if(scoreFile) {
        while(scoreFile >> score >> name) {
            this->scorelist.emplace(score, name);
        }
        scoreFile.close();
    }
}

void ScoreBoard::AddNewScore(int &newScore, std::string &playerName){
    this->scorelist.emplace(newScore, playerName);
    if(scorelist.size() > 10) {
        scorelist.erase(0);
    }
}

void ScoreBoard::ShowScoreBoard(){
    std::cout << "SCOREBOARD TOP 10" << std::endl;
    for(auto it = scorelist.rbegin(); it != scorelist.rend(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }
}

void ScoreBoard::SaveScoreBoard(){
    std::ofstream scoreFile;
    scoreFile.open("../ScoreBoard.txt", std::ios::trunc);
    if(scoreFile) {
        for(const auto& it : scorelist) {
            scoreFile << it.first << " " << it.second << std::endl;
        }
        scoreFile.close();
    }
}