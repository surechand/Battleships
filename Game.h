
#ifndef BATTLESHIPS_GAME_H
#define BATTLESHIPS_GAME_H
#include <SFML/Graphics.hpp>
#include "BoardController.h"
#include "ResetButton.h"
#include "RandomizeButton.h"
#include "PlayButton.h"
#include "Score.h"
#include <stdexcept>

class Game {
private:
    sf::RenderWindow window;
    sf::ContextSettings settings;
    bool gameEnded, computerShot;
    int lastHiti, lastHitj, lastWay;
    int last2Hiti, last2Hitj, last2Way;
public:
    Game() = default;
    void init();
    int loop();
    bool playerTurn(sf::Event &action, Fleet &compFleet, Board &background, Score &score);
    void computerTurn(sf::Event &action, Fleet &userFleet, Board &background, Score &score);
    void fireGenerator(int &i, int &j);
    void decisionGenerator(int &i);
    void setGameEnded(bool gameEnded);
};


#endif //BATTLESHIPS_GAME_H
