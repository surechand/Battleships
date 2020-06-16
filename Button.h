
#ifndef BATTLESHIPS_BUTTON_H
#define BATTLESHIPS_BUTTON_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Fleet.h"
#include "Board.h"

class Button : public sf::Drawable {
protected:
    sf::CircleShape circle;
    sf::Texture buttonTexture;
    bool clicked;
public:
    Button(float pos_X, float pos_Y, float radius);

    virtual void loadTexture() = 0;

    virtual bool isClicked() const = 0;

    virtual void action(sf::Event &action, Fleet &userFleet, Fleet &compFleet, Board &background) = 0;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const = 0;

    ~Button() = default;
};


#endif //BATTLESHIPS_BUTTON_H
