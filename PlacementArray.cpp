#include "PlacementArray.h"

PlacementArray::PlacementArray(float pos_X, float pos_Y) {
    square.setSize(sf::Vector2f(tileSize, tileSize));
    square.setPosition(pos_X, pos_Y);
    square.setFillColor(sf::Color::White);
    square.setOutlineThickness(2);
    square.setOutlineColor(sf::Color::Black);
    status = empty;
}

void PlacementArray::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(this->square, state);
}

float PlacementArray::getPosX() const {
    return pos_X;
}

void PlacementArray::setPosX(float posX) {
    pos_X = posX;
}

float PlacementArray::getPosY() const {
    return pos_Y;
}

void PlacementArray::setPosY(float posY) {
    pos_Y = posY;
}

sf::RectangleShape &PlacementArray::getSquare() {
    return square;
}

void PlacementArray::setSquare(const sf::RectangleShape &square) {
    PlacementArray::square = square;
}

PlacementArray::state PlacementArray::getStatus() const {
    return status;
}

void PlacementArray::setStatus(PlacementArray::state status) {
    PlacementArray::status = status;
}

float PlacementArray::getTileSize() const {
    return tileSize;
}
