#ifndef BATTLESHIPS_SHIP_H
#define BATTLESHIPS_SHIP_H
#include <SFML/Graphics.hpp>
#include <stdexcept>

class Ship : public sf::Drawable {
    sf::RectangleShape rectangle;
    sf::Texture shipTexture;
    const float tileSize {38.0};
    float startPos_X, startPos_Y;
    float rotation, defaultRotation;
    bool shipClicked;
    bool shipHorizontal;
    bool canDrag;
    bool canRotate;
    bool onBoard, onStartPos;
    bool locked;
    int placementBoardPosX, placementBoardPosY;
    int Size;
    int HP_bar;
    std::vector < std::pair <int,int> >positionsOnGameBoard;
public:
    Ship(float pos_X, float pos_Y, int size);

    Ship() = default;

    int getSize() const;

    void loadDestroyedTexture();

    int getPlacementBoardPosX() const;
    void setPlacementBoardPosX(int placementBoardPosX);

    int getPlacementBoardPosY() const;
    void setPlacementBoardPosY(int boardPosY);

    bool isOnBoard() const;
    void setOnBoard(bool onBoard);

    bool isOnStartPos() const;
    void setOnStartPos(bool onStartPos);

    void draw (sf::RenderTarget& target, sf::RenderStates state) const override;

    float getStartPosX() const;

    float getStartPosY() const;

    bool isShipClicked() const;
    void setShipClicked(bool shipClicked);

    bool isShipHorizontal() const;
    void setShipHorizontal(bool shipHorizontal);

    bool isCanDrag() const;
    void setCanDrag(bool canDrag);

    bool isCanRotate() const;
    void setCanRotate(bool canRotate);

    float getRotation() const;
    void setRotation(float rotation);

    sf::RectangleShape &getRectangle() ;
    void setRectangle(const sf::RectangleShape &rectangle);

    float getDefaultRotation() const;
    void setDefaultRotation(float defaultRotation);

    bool isLocked() const;
    void setLocked(bool locked);

    int getHpBar() const;
    void setHpBar(int hpBar);

    void addPosition(int i, int j);
    void clearPositions();
    const std::vector<std::pair<int,int>> &getPositionsOnGameBoard() const;

    ~Ship() override = default ;
};


#endif //BATTLESHIPS_SHIP_H
