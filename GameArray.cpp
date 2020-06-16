
#include "GameArray.h"

GameArray::GameArray(float pos_X, float pos_Y) {
    square.setSize(sf::Vector2f(tileSize, tileSize));
    square.setPosition(pos_X, pos_Y);
    square.setFillColor(sf::Color::White);
    square.setOutlineThickness(1);
    square.setOutlineColor(sf::Color::Black);
    status = empty;
}

void GameArray::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(this->square, state);
}

float GameArray::getPosX() const {
    return pos_X;
}

void GameArray::setPosX(float posX) {
    pos_X = posX;
}

float GameArray::getPosY() const {
    return pos_Y;
}

void GameArray::setPosY(float posY) {
    pos_Y = posY;
}

sf::RectangleShape &GameArray::getSquare() {
    return square;
}

void GameArray::setSquare(const sf::RectangleShape &square) {
    GameArray::square = square;
}

GameArray::state GameArray::getStatus() const {
    return status;
}

void GameArray::setStatus(GameArray::state status) {
    GameArray::status = status;
}

float GameArray::getTileSize() const {
    return tileSize;
}