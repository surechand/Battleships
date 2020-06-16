
#include "Fleet.h"

Fleet::Fleet(){
    this->PlacedOnBoard = false;
    this->locked = false;
    this->HP = 0;
};

void Fleet::initFleet(bool user){
    if(user) {
        this->fleet.push_back(std::make_unique<Ship>(100, 130, 2));
        this->fleet.push_back(std::make_unique<Ship>(140, 130, 2));
        this->fleet.push_back(std::make_unique<Ship>(180, 130, 2));
        this->fleet.push_back(std::make_unique<Ship>(220, 130, 3));
        this->fleet.push_back(std::make_unique<Ship>(260, 130, 3));
        this->fleet.push_back(std::make_unique<Ship>(300, 130, 4));
        this->fleet.push_back(std::make_unique<Ship>(340, 130, 5));
    } else {
        this->fleet.push_back(std::make_unique<Ship>(652, 130, 2));
        this->fleet.push_back(std::make_unique<Ship>(692, 130, 2));
        this->fleet.push_back(std::make_unique<Ship>(732, 130, 2));
        this->fleet.push_back(std::make_unique<Ship>(772, 130, 3));
        this->fleet.push_back(std::make_unique<Ship>(812, 130, 3));
        this->fleet.push_back(std::make_unique<Ship>(852, 130, 4));
        this->fleet.push_back(std::make_unique<Ship>(892, 130, 5));
    }
}

void Fleet::checkPlacement(){
    for(auto & check : this->getFleet()) {
        if(check.operator*().isOnBoard() && !check.operator*().isOnStartPos()){
            this->setIsPlacedOnBoard(true);
        } else {
            this->setIsPlacedOnBoard(false);
            break;
        }
    }
}

void Fleet::lock(){
    for(auto & locker : this->getFleet()){
        locker.operator*().setLocked(true);
    }
    setLocked(true);
}

void Fleet::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    for(const auto& drawable : fleet) {
        drawable->draw(target, state);
    }
}

Ship& Fleet::operator[](std::size_t index) {
    return *fleet[index];
}

const std::deque<std::unique_ptr<Ship>> &Fleet::getFleet() const {
    return fleet;
}

bool Fleet::isPlacedOnBoard() const {
    return PlacedOnBoard;
}

void Fleet::setIsPlacedOnBoard(bool isPlacedOnBoard) {
    Fleet::PlacedOnBoard = isPlacedOnBoard;
}

bool Fleet::isLocked() const {
    return locked;
}

void Fleet::setLocked(bool lock) {
    Fleet::locked = lock;
}

void Fleet::setFleetHp() {
    this->HP = 0;
    for(const auto & counter : this->getFleet()){
        this->HP += counter.operator*().getHpBar();
    }
}

int Fleet::getHp() const {
    return HP;
}

void Fleet::setHp(int hp) {
    HP = hp;
}

int Fleet::getShipFromThatPosition(int i, int j) const{
    int index = 0;
    for(auto & finder : this->getFleet()){
        for(auto & finder2 : finder->getPositionsOnGameBoard()){
            if(finder2.first == i && finder2.second == j){
                return index;
            }
        }
        ++index;
    }
}

