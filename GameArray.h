
#ifndef BATTLESHIPS_GAMEARRAY_H
#define BATTLESHIPS_GAMEARRAY_H
#include <SFML/Graphics.hpp>

class GameArray : public sf::Drawable {
    sf::RectangleShape square;
    const float tileSize {38.0};
    float pos_X, pos_Y;
public:
    enum state {
        empty,
        ship,
        missed,
        fire,
        destroyed
    };
    state status;

    GameArray() = default;

    GameArray(float pos_X, float pos_Y);

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

    ~GameArray() override = default;
};

#endif //BATTLESHIPS_GAMEARRAY_H
