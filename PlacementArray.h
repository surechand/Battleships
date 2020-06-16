
#ifndef BATTLESHIPS_PLACEMENTARRAY_H
#define BATTLESHIPS_PLACEMENTARRAY_H
#include <SFML/Graphics.hpp>

class PlacementArray : public sf::Drawable {
    sf::RectangleShape square;
    const float tileSize {16.0};
    float pos_X, pos_Y;
public:
    enum state {
        empty,
        ship,
        forbidden
    };
    state status;

    PlacementArray() = default;

    PlacementArray(float pos_X, float pos_Y);

    void draw (sf::RenderTarget& target, sf::RenderStates state) const override;

    float getPosX() const;
    void setPosX(float posX);

    float getPosY() const;
    void setPosY(float posY);

    state getStatus() const;
    void setStatus(state status);

    float getTileSize() const;

    sf::RectangleShape &getSquare();
    void setSquare(const sf::RectangleShape &square);

    ~PlacementArray() override = default;
};


#endif //BATTLESHIPS_PLACEMENTARRAY_H
