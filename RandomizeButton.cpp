
#include "RandomizeButton.h"

RandomizeButton::RandomizeButton(float pos_X, float pos_Y, float radius) : Button(pos_X, pos_Y, radius) {
    this->clicked = false;
    this->circle.setPosition(sf::Vector2f(pos_X, pos_Y));
    this->circle.setRadius(radius);
    this->circle.setOrigin(sf::Vector2f(radius, radius));
    this->circle.setFillColor(sf::Color::White);
    this->circle.setOutlineThickness(2);
    this->circle.setOutlineColor(sf::Color::Black);
}

void RandomizeButton::loadTexture(){
    if(!this->buttonTexture.loadFromFile("../Resources/Rand.png")){
        throw std::runtime_error("Plik nie zaladowany");
    }
    circle.setTexture(&buttonTexture);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
}

bool RandomizeButton::isClicked() const {
    return clicked;
}

void RandomizeButton::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(this->circle, state);
}

void RandomizeButton::action(sf::Event &action, Fleet &userFleet, Fleet &compFleet, Board &background) {
    if(this->circle.getGlobalBounds().contains(action.mouseButton.x, action.mouseButton.y)){
        if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left) {
            clicked = true;
            BoardController::randomizeFleetPosition(userFleet, background.userPlacementMatrix, background.userGameMatrix);
        }
    }
    clicked = false;
}