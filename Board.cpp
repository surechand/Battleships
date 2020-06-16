#include "Board.h"

Board::Board(){
    backgroundTexture.loadFromFile("../Resources/Background.jpg");
    background.setTexture(&backgroundTexture);
    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(this->backgroundWidth, this->backgroundHeight));
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(this->background, state);
    for(int j=0; j < gameArraySize; j++) {
        for (int i = 0; i < gameArraySize; i++) {
                target.draw(this->userGameMatrix[i][j], state);
        }
    }
    for(int j=0; j < gameArraySize; j++) {
        for (int i = 0; i < gameArraySize; i++) {
            target.draw(this->computerGameMatrix[i][j], state);
        }
    }
//    for(int j=0; j < placementArraySize; j++) {
//        for (int i = 0; i < placementArraySize; i++) {
//            if(j%2==0 || i%2 == 0) {
//                target.draw(this->userPlacementMatrix[i][j], state);
//            }
//        }
//    }
//    for(int j=0; j < placementArraySize; j++) {
//        for (int i = 0; i < placementArraySize; i++) {
//            if(j%2==0 || i%2 == 0) {
//                target.draw(this->computerPlacementMatrix[i][j], state);
//            }
//        }
//    }
}

void Board::initPlacementMatrix(std::vector< std::vector<PlacementArray>> &matrix, float tileStartPos_X, float tileStartPos_Y) const {
    for(int i=0; i < placementArraySize; i++){
        std::vector<PlacementArray> column;
        if(i%2==0) {
            for (int j = 0; j < placementArraySize; j++) {
                column.emplace_back(PlacementArray(tileStartPos_X + static_cast<float>(i) * 20,
                                          tileStartPos_Y + static_cast<float>(j) * 20));
                column[j].setPosX(tileStartPos_X + static_cast<float>(i) * 20);
                column[j].setPosY(tileStartPos_Y + static_cast<float>(j) * 20);
            }
            matrix.push_back(column);
        } else if (i%2==1){
            for (int j = 0; j < placementArraySize; j++) {
                if(j%2==0) {
                    column.emplace_back(PlacementArray(tileStartPos_X + static_cast<float>(i) * 20,
                                              tileStartPos_Y + static_cast<float>(j) * 20));
                    column[j].setPosX(tileStartPos_X + static_cast<float>(i) * 20);
                    column[j].setPosY(tileStartPos_Y + static_cast<float>(j) * 20);
                } else {
                    column.emplace_back(PlacementArray(-1,
                                                       -1));
                    column[j].setPosX(-1);
                    column[j].setPosY(-1);
                    column[j].setStatus(PlacementArray::forbidden);
                }
            }
            matrix.push_back(column);
        }
    }
    if(matrix.size() > placementArraySize){
        throw std::out_of_range("User/Computer matrix out of range");
    }
}

void Board::initUserCompPlacementMatrix(){
    initPlacementMatrix(userPlacementMatrix, userTileStartPos_X, userTileStartPos_Y);
    initPlacementMatrix(computerPlacementMatrix, computerTileStartPos_X, computerTileStartPos_Y);
}

void Board::initGameMatrix(std::vector< std::vector<GameArray>> &matrix, float tileStartPos_X, float tileStartPos_Y) const {
    for(int i=0; i < gameArraySize; i++) {
        std::vector<GameArray> column;
        for (int j = 0; j < gameArraySize; j++) {
            column.emplace_back(GameArray(tileStartPos_X + static_cast<float>(i) * 40,
                                          tileStartPos_Y + static_cast<float>(j) * 40));
            column[j].setPosX(tileStartPos_X + static_cast<float>(i) * 40);
            column[j].setPosY(tileStartPos_Y + static_cast<float>(j) * 40);
        }
        matrix.push_back(column);
    }
    if(matrix.size() > gameArraySize){
        throw std::out_of_range("User/Computer matrix out of range");
    }
}

void Board::initUserCompGameMatrix(){
    initGameMatrix(userGameMatrix, userGridPos_X, userGridPos_Y);
    initGameMatrix(computerGameMatrix, computerGridPos_X, computerGridPos_Y);
}

