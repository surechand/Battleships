
#ifndef BATTLESHIPS_PLAYBUTTON_H
#define BATTLESHIPS_PLAYBUTTON_H
#include "Button.h"
#include "BoardController.h"

class PlayButton : public Button {
public:
    PlayButton(float pos_X, float pos_Y, float radius);

    void loadTexture() override;

    bool isClicked() const override;

    void action(sf::Event &action, Fleet &userFleet, Fleet &compFleet, Board &background) override;

    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

    ~PlayButton() override = default;
};

#endif //BATTLESHIPS_PLAYBUTTON_H
