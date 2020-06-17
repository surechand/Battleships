#ifndef BATTLESHIPS_BOARDCONTROLLER_H
#define BATTLESHIPS_BOARDCONTROLLER_H
#include "Ship.h"
#include "Board.h"
#include "Fleet.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <functional>

class BoardController {
    /*Zmienne obsługujące ruch myszki na ekranie gry*/
    int mouseX = 0;
    int mouseY = 0;
    sf::Vector2f shipMovement;
public:
    /*Konstruktor*/
    BoardController() = default;
    /*Metoda obsługująca ręczny ruch statków na planszy*/
    void setShipPosition(sf::Event &action, Ship &ship, Board &background);
    /*Metoda odpowiedzialna za podniesienie statu po wciśnięciu LPM i umożliwienie dalszych operacji*/
    void pickManually(sf::Event &action, Ship &ship, Board &background);
    /*Metoda odpowiedzialna za obrót statku o 90 stopni po wciśnięciu PPM*/
    void rotate (sf::Event &action, Ship &ship);
    /*Metoda kładąca statek na macierzy umieszczania na środku jednego z wybranych wskaźnikiem myszy kwadratów*/
    void placeManuallyOnBoard(sf::Event &action, Ship &ship, Board &background);
    /*Metoda przemieszczająca wybrany statek zgodnie z ruchem myszy*/
    void dragShipManually(sf::Event &action, Ship &ship);
    /*Metoda kolorująca kwadraty macierzy rozgrywki w zależności od podejmowanych przez graczy decyzji*/
    static void checkBoard(sf::Event &action, Board &background);
    /*Metoda pozwalająca na sprawdzenie możliwości umieszczenia statku na macierzy umieszczania.
     * Pobiera statek i w zależności od jego parametrów, oraz obecnego stanu macierzy zwraca true, jeżeli umieszczenie
     * statku w obecnej pozycji jest możliwe lub false, jeżeli taka możliwość nie zachodzi*/
    static bool checkPlace(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix, int column, int row);
    /*Metoda blokująca pola na macierzy umieszczania uniemożliwiając umieszczenie kolejnych statków bezpośrednio przy statku
     * Głównymi parametrami funkcji jest kąt położenia statku oraz jego rozmiar*/
    static void blockTiles(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix, int column, int row);
    /*Metoda przy ciągłym wywołaniu odświeża stan obu macierzy i uzupełnia blokady oraz dane o pozycjach statków dla całęj floty*/
    static void updateBlockade(Fleet &fleet, std::vector< std::vector<PlacementArray>> &matrix1, std::vector< std::vector<GameArray>> &matrix2);
    /*Metoda zerująca stany obu macierzy, działa w połączeniu z metodą updateBlockade i razem odpowiadają za odświeżanie stanu macierzy*/
    static void resetBoard(std::vector< std::vector<PlacementArray>> &matrix, std::vector< std::vector<GameArray>> &matrix2);
    /*Metoda usuwająca statek z planszy i stawiający w miejscu początkowym. Resetuje ona zapisane zajmowane pozycje na planszy*/
    static void resetShipPlacement(Ship &ship);
    /*Metoda resetująca ustawienie całej floty*/
    static void resetFleetPlacement(Fleet &fleet);
    /*Metoda przyporządkowujaca otrzymanym indeksom macierzy umieszczania losowe wartości otrzymane algorytmem Mersenne Twister'a*/
    static void positionGenerator(int &i, int &j);
    /*Metoda przyporządkowujaca otrzymanymemu stanowi obrotu losową wartość otrzymane algorytmem Mersenne Twister'a*/
    static void rotationGenerator(int &rotation);
    /*Metoda umieszczająca statek na losowo wygenerowanej pozycji*/
    static void randomizeShipPosition(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix);
    /*Metoda umieszczająca flotę na losowowo wygenerowanych pozycjach w kolejności od największego statku do najmniejszego*/
    static void randomizeFleetPosition(Fleet &fleet, std::vector< std::vector<PlacementArray>> &matrix, std::vector< std::vector<GameArray>> &matrix2);
    /*Metoda rezerwująca miejsce na macierzy umieszczania dla statku*/
    static void setPlacementArrayToShip(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix);
    /*Metoda przypisująca statkowi pozycje zajmowane na macierzy rozgrywki*/
    static void addGameArrayPositionsToShip(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix);
};


#endif //BATTLESHIPS_BOARDCONTROLLER_H
