#ifndef BATTLESHIPS_BOARD_H
#define BATTLESHIPS_BOARD_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "PlacementArray.h"
#include "GameArray.h"

class Board : public sf::Drawable {
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    const float backgroundWidth { 1024.0 }, backgroundHeight { 768.0 };
    const float userGridPos_X {41.0}, userGridPos_Y {299.0}, computerGridPos_X {585.0}, computerGridPos_Y {299.0};
    const float userTileStartPos_X {52.0}, userTileStartPos_Y {310.0}, computerTileStartPos_X {596.0}, computerTileStartPos_Y {310.0};
public:
    const int placementArraySize = 19, gameArraySize = 10;
    std::vector< std::vector<PlacementArray>> userPlacementMatrix;
    std::vector< std::vector<PlacementArray>> computerPlacementMatrix;
    std::vector< std::vector<GameArray>> userGameMatrix;
    std::vector< std::vector<GameArray>> computerGameMatrix;
    Board();
    ~Board() override = default;
    void draw (sf::RenderTarget& target, sf::RenderStates state) const override;
    void initPlacementMatrix(std::vector< std::vector<PlacementArray>> &matrix, float tileStartPos_X, float tileStartPos_Y) const;
    void initGameMatrix(std::vector< std::vector<GameArray>> &matrix, float tileStartPos_X, float tileStartPos_Y) const;
    void initUserCompPlacementMatrix();
    void initUserCompGameMatrix();
};


#endif //BATTLESHIPS_BOARD_H
