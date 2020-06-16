
#ifndef BATTLESHIPS_GAME_H
#define BATTLESHIPS_GAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "BoardController.h"
#include "ResetButton.h"
#include "RandomizeButton.h"
#include "PlayButton.h"
#include "Game.h"
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
    void loop();
    bool playerTurn(sf::Event &action, Fleet &compFleet, Board &background);
    void computerTurn(sf::Event &action, Fleet &userFleet, Board &background);
    void fireGenerator(int &i, int &j);
    void decisionGenerator(int &i);
    void setGameEnded(bool gameEnded);
};


#endif //BATTLESHIPS_GAME_H
