
#ifndef BATTLESHIPS_RANDOMIZEBUTTON_H
#define BATTLESHIPS_RANDOMIZEBUTTON_H
#include "Button.h"
#include "BoardController.h"

class RandomizeButton : public Button {
public:
    RandomizeButton(float pos_X, float pos_Y, float radius);

    void loadTexture() override;

    bool isClicked() const override;

    void action(sf::Event &action, Fleet &userFleet, Fleet &compFleet, Board &background) override;

    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

    ~RandomizeButton() override = default;
};

#endif //BATTLESHIPS_RANDOMIZEBUTTON_H
