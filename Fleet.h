
#ifndef BATTLESHIPS_FLEET_H
#define BATTLESHIPS_FLEET_H
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <vector>
#include <memory>
#include <deque>

class Fleet : public Ship {
    std::deque<std::unique_ptr<Ship>> fleet;
    bool PlacedOnBoard;
    bool locked;
    int HP;
public:
    Fleet();

    void initFleet(bool user);
    /*Metoda sprawdzająca czy cała flota zostałą umieszczona na planszy*/
    void checkPlacement();

    void lock();

    bool isPlacedOnBoard() const;
    void setIsPlacedOnBoard(bool isPlacedOnBoard);

    bool isLocked() const override;
    void setLocked(bool locked) override;

    void draw (sf::RenderTarget& target, sf::RenderStates state) const override;

    Ship& operator[](std::size_t index);

    const std::deque<std::unique_ptr<Ship>> &getFleet() const;

    int getHp() const;
    void setFleetHp() ;
    void setHp(int hp);
    /*Metoda wyszukująca statek znajdujący się na przekazanej do funkcji pozycji*/
    int getShipFromThatPosition(int i, int j) const;
};


#endif //BATTLESHIPS_FLEET_H
