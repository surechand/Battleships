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
    int mouseX = 0;
    int mouseY = 0;
    sf::Vector2f shipMovement;
public:
    BoardController() = default;
    void setShipPosition(sf::Event &action, Ship &ship, Board &background);
    void pickManually(sf::Event &action, Ship &ship, Board &background);
    void rotate (sf::Event &action, Ship &ship);
    void placeManuallyOnBoard(sf::Event &action, Ship &ship, Board &background);
    void dragShipManually(sf::Event &action, Ship &ship);
    static void checkBoard(sf::Event &action, Board &background);
    static bool checkPlace(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix, int column, int row);
    static void blockTiles(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix, int column, int row);
    static void updateBlockade(Fleet &fleet, std::vector< std::vector<PlacementArray>> &matrix1, std::vector< std::vector<GameArray>> &matrix2);
    static void resetBoard(std::vector< std::vector<PlacementArray>> &matrix, std::vector< std::vector<GameArray>> &matrix2);
    static void resetShipPlacement(Ship &ship);
    static void resetFleetPlacement(Fleet &fleet);
    static void positionGenerator(int &i, int &j);
    static void rotationGenerator(int &rotation);
    static void randomizeShipPosition(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix);
    static void randomizeFleetPosition(Fleet &fleet, std::vector< std::vector<PlacementArray>> &matrix, std::vector< std::vector<GameArray>> &matrix2);
    static void setPlacementArrayToShip(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix);
    static void addGameArrayPositionsToShip(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix);
};


#endif //BATTLESHIPS_BOARDCONTROLLER_H
