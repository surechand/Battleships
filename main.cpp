#include <iostream>
#include <SFML/Graphics.hpp>
#include "ScoreBoard.h"
#include "Game.h"
#include <string>

int main(int argc,char *argv[]) {
    ScoreBoard scoreBoard;
    std::string playerName;
    Game game;
    game.init();
    int finalScore = game.loop();
    if (finalScore != 0) {
        std::cout << "YOU WON \nYOUR SCORE : " << finalScore << std::endl;
        std::cout << "TYPE YOUR NAME :  " ;
        std::cin >> playerName;
        scoreBoard.AddNewScore(finalScore, playerName);
    } else {
        std::cout << "YOU LOST \nYOUR SCORE : " << finalScore << std::endl;
    }
    scoreBoard.ShowScoreBoard();
    scoreBoard.SaveScoreBoard();
    return 0;
}