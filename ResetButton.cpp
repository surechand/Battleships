
#include "ResetButton.h"

ResetButton::ResetButton(float pos_X, float pos_Y, float radius) : Button(pos_X, pos_Y, radius) {
    this->clicked = false;
    this->circle.setPosition(sf::Vector2f(pos_X, pos_Y));
    this->circle.setRadius(radius);
    this->circle.setOrigin(sf::Vector2f(radius, radius));
    this->circle.setFillColor(sf::Color::White);
    this->circle.setOutlineThickness(2);
    this->circle.setOutlineColor(sf::Color::Black);
}

void ResetButton::loadTexture(){
    if(!this->buttonTexture.loadFromFile("../Resources/Reset.png")){
        throw std::runtime_error("Plik nie zaladowany");
    }
    circle.setTexture(&buttonTexture);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
}

bool ResetButton::isClicked() const {
    return clicked;
}

void ResetButton::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(this->circle, state);
}

void ResetButton::action(sf::Event &action, Fleet &userFleet, Fleet &compFleet, Board &background) {
    if(this->circle.getGlobalBounds().contains(action.mouseButton.x, action.mouseButton.y)){
        if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left) {
            clicked = true;
            if(!userFleet.isLocked()) {
                BoardController::resetFleetPlacement(userFleet);
            }
        }
    }
    clicked = false;
}
