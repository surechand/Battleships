#include "Ship.h"

Ship::Ship(float pos_X, float pos_Y, int size) {
    this->shipClicked = this->canDrag = this->canRotate = this->onBoard = this->locked = false;
    this->onStartPos = true;
    this->startPos_X = pos_X;
    this->startPos_Y = pos_Y;
    this->Size = size;
    this->HP_bar = size;
    this->placementBoardPosX = this->placementBoardPosY = 1;
    this->rectangle.setPosition(startPos_X, startPos_Y);
    this->rectangle.setFillColor(sf::Color::White);
    if(Size == 2) {
        if(!shipTexture.loadFromFile("../Resources/Cruiser.png")){
            throw std::runtime_error("Plik nie zaladowany");
        }
    } else if(Size == 3) {
        if(!shipTexture.loadFromFile("../Resources/Battleship.png")){
            throw std::runtime_error("Plik nie zaladowany");
        }
    } else if(Size == 4) {
        if(!shipTexture.loadFromFile("../Resources/Heavy battleship.png")){
            throw std::runtime_error("Plik nie zaladowany");
        }
    } else if(Size == 5) {
        if(!shipTexture.loadFromFile("../Resources/Aircraft carrier.png")){
            throw std::runtime_error("Plik nie zaladowany");
        }
    }
    this->rectangle.setSize(sf::Vector2f(tileSize, (Size * tileSize + Size)));
    this->rectangle.setOrigin(sf::Vector2f(tileSize / 2, (Size * tileSize + Size) / 2));
    this->defaultRotation = 0;
    this->shipHorizontal = false;
    this->rectangle.setTexture(&shipTexture);
}

void Ship::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(this->rectangle, state);
}

void Ship::loadDestroyedTexture(){
    if(this->Size == 2) {
        if(!this->shipTexture.loadFromFile("../Resources/Destroyed Cruiser.png")){
            throw std::runtime_error("Plik nie zaladowany");
        }
    } else if(this->Size == 3) {
        if(!this->shipTexture.loadFromFile("../Resources/Destroyed Battleship.png")){
            throw std::runtime_error("Plik nie zaladowany");
        }
    } else if(this->Size == 4) {
        if(!this->shipTexture.loadFromFile("../Resources/Destroyed Heavy battleship.png")){
            throw std::runtime_error("Plik nie zaladowany");
        }
    } else if(this->Size == 5) {
        if(!this->shipTexture.loadFromFile("../Resources/Destroyed Aircraft carrier.png")){
            throw std::runtime_error("Plik nie zaladowany");
        }
    }
}

bool Ship::isShipClicked() const {
    return shipClicked;
}

void Ship::setShipClicked(bool shipClicked) {
    Ship::shipClicked = shipClicked;
}

bool Ship::isShipHorizontal() const {
    return shipHorizontal;
}

void Ship::setShipHorizontal(bool shipHorizontal) {
    Ship::shipHorizontal = shipHorizontal;
}

bool Ship::isCanDrag() const {
    return canDrag;
}

void Ship::setCanDrag(bool canDrag) {
    Ship::canDrag = canDrag;
}

bool Ship::isCanRotate() const {
    return canRotate;
}

void Ship::setCanRotate(bool canRotate) {
    Ship::canRotate = canRotate;
}

float Ship::getRotation() const {
    return rotation;
}

void Ship::setRotation(float rotation) {
    Ship::rotation = rotation;
    rectangle.setRotation(rotation);
}

sf::RectangleShape &Ship::getRectangle() {
    return rectangle;
}

void Ship::setRectangle(const sf::RectangleShape &rectangle) {
    Ship::rectangle = rectangle;
}

float Ship::getStartPosX() const {
    return startPos_X;
}

float Ship::getStartPosY() const {
    return startPos_Y;
}

int Ship::getPlacementBoardPosX() const {
    return placementBoardPosX;
}

void Ship::setPlacementBoardPosX(int placementPosX) {
    Ship::placementBoardPosX = placementPosX;
}

int Ship::getPlacementBoardPosY() const {
    return placementBoardPosY;
}

void Ship::setPlacementBoardPosY(int placementPosY) {
    Ship::placementBoardPosY = placementPosY;
}

bool Ship::isOnBoard() const {
    return onBoard;
}

void Ship::setOnBoard(bool onBoard) {
    Ship::onBoard = onBoard;
}

float Ship::getDefaultRotation() const {
    return defaultRotation;
}

void Ship::setDefaultRotation(float defaultRotation) {
    Ship::defaultRotation = defaultRotation;
}

bool Ship::isOnStartPos() const {
    return onStartPos;
}

void Ship::setOnStartPos(bool onStartPos) {
    Ship::onStartPos = onStartPos;
}

int Ship::getSize() const {
    return Size;
}

bool Ship::isLocked() const {
    return locked;
}

void Ship::setLocked(bool lock) {
    Ship::locked = lock;
}

int Ship::getHpBar() const {
    return HP_bar;
}

void Ship::setHpBar(int hpBar) {
    HP_bar = hpBar;
}

void Ship::addPosition(int i, int j){
    this->positionsOnGameBoard.emplace_back(i, j);
}

void Ship::clearPositions(){
    this->positionsOnGameBoard.clear();
}

const std::vector<std::pair<int,int>> &Ship::getPositionsOnGameBoard() const {
    return positionsOnGameBoard;
}


