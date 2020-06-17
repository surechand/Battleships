
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
    /*Główny inizjalizator okna oraz sposobu wyświetlania*/
    void init();
    /*Główna pętla rozgrywki odpowiedzialna za działania użytkownika i komputera oraz zarządzanie etapem przygotowania i rozgrywki*/
    int loop();
    /*Funkcja tury gracza. Pobiera od użytkownika pole do strzału*/
    bool playerTurn(sf::Event &action, Fleet &compFleet, Board &background, Score &score);
    /*Funkcja tury komputera. Losowo generuje pola do strzału. W przypadku trafienia w kolejnych rundach próbuje zniszczyć statek do końca kolejno analizując sąsiadujące pola*/
    void computerTurn(sf::Event &action, Fleet &userFleet, Board &background, Score &score);
    /*Generator pozycji do ruchu komputera*/
    void fireGenerator(int &i, int &j);
    /*Generator kierunku kolejnego ruchu komputera po odnotowanym strzale*/
    void decisionGenerator(int &i);
    void setGameEnded(bool gameEnded);
};


#endif //BATTLESHIPS_GAME_H
