
#ifndef BATTLESHIPS_RESETBUTTON_H
#define BATTLESHIPS_RESETBUTTON_H
#include "Button.h"
#include "BoardController.h"

class ResetButton : public Button {
public:
    ResetButton(float pos_X, float pos_Y, float radius);

    void loadTexture() override;

    bool isClicked() const override;

    void action(sf::Event &action, Fleet &userFleet, Fleet &compFleet, Board &background) override;

    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

    ~ResetButton() override = default;
};

#endif //BATTLESHIPS_RESETBUTTON_H
