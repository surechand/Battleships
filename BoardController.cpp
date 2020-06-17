
#include "BoardController.h"

void BoardController::setShipPosition(sf::Event &action, Ship &ship, Board &background) {
    if(!ship.isLocked()) {
        pickManually(action, ship, background);

        rotate(action, ship);

        placeManuallyOnBoard(action, ship, background);

        if (!ship.isOnBoard() && !ship.isOnStartPos() && action.type == sf::Event::MouseButtonReleased &&
            action.mouseButton.button == sf::Mouse::Left) {
            resetShipPlacement(ship);
        }

        dragShipManually(action, ship);
    }
}

void BoardController::pickManually(sf::Event &action, Ship &ship, Board &background){
    if (ship.getRectangle().getGlobalBounds().contains(action.mouseButton.x, action.mouseButton.y)) {
        if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left) {
            ship.setOnBoard(false);
            ship.setOnStartPos(false);
            ship.setShipClicked(true);
            ship.setCanRotate(true);
            ship.setCanDrag(true);
            background.userPlacementMatrix[ship.getPlacementBoardPosX()][ship.getPlacementBoardPosY()].setStatus(PlacementArray::empty);
            ship.getRectangle().setOutlineThickness(2);
            ship.getRectangle().setOutlineColor(sf::Color::Red);
            ship.clearPositions();
        }
    }
}

void BoardController::rotate(sf::Event &action, Ship &ship) {
    if (ship.isCanRotate()) {
        if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Right) {
            if (ship.isShipHorizontal()) {
                ship.setShipHorizontal(false);
                ship.setRotation(0);
            } else {
                ship.setShipHorizontal(true);
                ship.setRotation(90);
            }
        }
    }
}

void BoardController::placeManuallyOnBoard(sf::Event &action, Ship &ship, Board &background){
    if (ship.isCanDrag()) {
        if (action.type == sf::Event::MouseButtonReleased && action.mouseButton.button == sf::Mouse::Left) {
            for (auto j = 0; j < background.placementArraySize; j++) {
                for (auto i = 0; i < background.placementArraySize; i++) {
                    if (background.userPlacementMatrix[i][j].getSquare().getGlobalBounds().contains(action.mouseButton.x,
                                                                                                    action.mouseButton.y) &&
                        (background.userPlacementMatrix[i][j].getStatus() == PlacementArray::empty) &&
                        checkPlace(ship, background.userPlacementMatrix, i, j)) {
                        ship.getRectangle().setPosition(sf::Vector2f(
                                background.userPlacementMatrix[i][j].getPosX() +
                                (background.userPlacementMatrix[i][j].getTileSize() / 2),
                                background.userPlacementMatrix[i][j].getPosY() +
                                (background.userPlacementMatrix[i][j].getTileSize() / 2)));
                        ship.setPlacementBoardPosX(i);
                        ship.setPlacementBoardPosY(j);
                        ship.setOnBoard(true);
                        ship.setOnStartPos(false);
                    }
                }
            }
            ship.setShipClicked(false);
            ship.setCanRotate(false);
            ship.setCanDrag(false);
            ship.getRectangle().setOutlineThickness(0);
        }
    }
}

void BoardController::dragShipManually(sf::Event &action, Ship &ship){
    if (action.type == sf::Event::MouseMoved) {
        mouseX = action.mouseMove.x;
        mouseY = action.mouseMove.y;
    }
    
    if (ship.isCanDrag()) {
        ship.getRectangle().setPosition(static_cast<float>(mouseX) - shipMovement.x,
                                        static_cast<float>(mouseY) - shipMovement.y);
    }
}

void BoardController::checkBoard(sf::Event &action, Board &background) {
    for (auto j = 0; j < background.gameArraySize; j++) {
        for (auto i = 0; i < background.gameArraySize; i++) {
            if (background.userGameMatrix[i][j].getStatus() == GameArray::empty) {
                background.userGameMatrix[i][j].getSquare().setFillColor(sf::Color::White);
            } else if (background.userGameMatrix[i][j].getStatus() == GameArray::missed) {
                background.userGameMatrix[i][j].getSquare().setFillColor(sf::Color(169,169,169));
            } else if (background.userGameMatrix[i][j].getStatus() == GameArray::fire) {
                background.userGameMatrix[i][j].getSquare().setFillColor(sf::Color(255,69,0));
            } else if (background.userGameMatrix[i][j].getStatus() == GameArray::destroyed){
                background.userGameMatrix[i][j].getSquare().setFillColor(sf::Color(105,105,105));
            }
            if (background.computerGameMatrix[i][j].getStatus() == GameArray::empty) {
                background.computerGameMatrix[i][j].getSquare().setFillColor(sf::Color::White);
            } else if (background.computerGameMatrix[i][j].getStatus() == GameArray::missed) {
                background.computerGameMatrix[i][j].getSquare().setFillColor(sf::Color(169,169,169));
            } else if (background.computerGameMatrix[i][j].getStatus() == GameArray::fire) {
                background.computerGameMatrix[i][j].getSquare().setFillColor(sf::Color(255,69,0));
            } else if (background.computerGameMatrix[i][j].getStatus() == GameArray::destroyed){
                background.computerGameMatrix[i][j].getSquare().setFillColor(sf::Color(105,105,105));
            }
        }
    }
//    for (auto j = 0; j < background.placementArraySize; j++) {
//        for (auto i = 0; i < background.placementArraySize; i++) {
//            if (background.userPlacementMatrix[i][j].getStatus() == PlacementArray::empty) {
//                background.userPlacementMatrix[i][j].getSquare().setFillColor(sf::Color::White);
//            } else if (background.userPlacementMatrix[i][j].getStatus() == PlacementArray::ship) {
//                    background.userPlacementMatrix[i][j].getSquare().setFillColor(sf::Color::Blue);
//            } else if (background.userPlacementMatrix[i][j].getStatus() == PlacementArray::forbidden) {
//                background.userPlacementMatrix[i][j].getSquare().setFillColor(sf::Color::Red);
//            }
//        }
//    }
}

bool BoardController::checkPlace(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix, int column, int row) {
    if((ship.isShipHorizontal() && column - ship.getSize() >= -1 && column + ship.getSize() <= 19) ||
       (!ship.isShipHorizontal() && row - ship.getSize() >= -1 && row + ship.getSize() <= 19)) {
        if (ship.getSize() == 2) {
            if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
                if (matrix[column - 1][row].getStatus() == PlacementArray::empty &&
                    matrix[column + 1][row].getStatus() == PlacementArray::empty) {
                    return (row % 2 == 0 && column % 2 == 1) && (column - ship.getSize() >= -1) &&
                           (column + ship.getSize() <= 19);
                } else {
                    return false;
                }
            } else { // jezeli jest ustawiony pionowo
                if (matrix[column][row - 1].getStatus() == PlacementArray::empty &&
                    matrix[column][row + 1].getStatus() == PlacementArray::empty) {
                    return (row % 2 == 1 && column % 2 == 0) && (row - ship.getSize() >= -1) &&
                           (row + ship.getSize() <= 19);
                } else {
                    return false;
                }
            }

        } else if (ship.getSize() == 4) {
            if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
                if (matrix[column - 3][row].getStatus() == PlacementArray::empty &&
                    matrix[column - 1][row].getStatus() == PlacementArray::empty &&
                    matrix[column + 1][row].getStatus() == PlacementArray::empty &&
                    matrix[column + 3][row].getStatus() == PlacementArray::empty) {
                    return (row % 2 == 0 && column % 2 == 1) && (column - ship.getSize() >= -1) &&
                           (column + ship.getSize() <= 19);
                } else {
                    return false;
                }
            } else { // jezeli jest ustawiony pionowo
                if (matrix[column][row - 3].getStatus() == PlacementArray::empty &&
                    matrix[column][row - 1].getStatus() == PlacementArray::empty &&
                    matrix[column][row + 1].getStatus() == PlacementArray::empty &&
                    matrix[column][row + 3].getStatus() == PlacementArray::empty) {
                    return (row % 2 == 1 && column % 2 == 0) && (row - ship.getSize() >= -1) &&
                           (row + ship.getSize() <= 19);
                } else {
                    return false;
                }
            }

        } else if (ship.getSize() == 3) {
            if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
                if (matrix[column - 2][row].getStatus() == PlacementArray::empty &&
                    matrix[column][row].getStatus() == PlacementArray::empty &&
                    matrix[column + 2][row].getStatus() == PlacementArray::empty) {
                    return (row % 2 == 0 && column % 2 == 0) && (column - ship.getSize() >= -1) &&
                           (column + ship.getSize() <= 19);
                } else {
                    return false;
                }
            } else { // jezeli jest ustawiony pionowo
                if (matrix[column][row - 2].getStatus() == PlacementArray::empty &&
                    matrix[column][row].getStatus() == PlacementArray::empty &&
                    matrix[column][row + 2].getStatus() == PlacementArray::empty) {
                    return (row % 2 == 0 && column % 2 == 0) && (row - ship.getSize() >= -1) &&
                           (row + ship.getSize() <= 19);
                } else {
                    return false;
                }
            }

        } else if (ship.getSize() == 5) {
            if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
                if (matrix[column - 4][row].getStatus() == PlacementArray::empty &&
                    matrix[column - 2][row].getStatus() == PlacementArray::empty &&
                    matrix[column][row].getStatus() == PlacementArray::empty &&
                    matrix[column + 2][row].getStatus() == PlacementArray::empty &&
                    matrix[column + 4][row].getStatus() == PlacementArray::empty) {
                    return (row % 2 == 0 && column % 2 == 0) && (column - ship.getSize() >= -1) &&
                           (column + ship.getSize() <= 19);
                } else {
                    return false;
                }
            } else { // jezeli jest ustawiony pionowo
                if (matrix[column][row - 4].getStatus() == PlacementArray::empty &&
                    matrix[column][row - 2].getStatus() == PlacementArray::empty &&
                    matrix[column][row].getStatus() == PlacementArray::empty &&
                    matrix[column][row + 2].getStatus() == PlacementArray::empty &&
                    matrix[column][row + 4].getStatus() == PlacementArray::empty) {
                    return (row % 2 == 0 && column % 2 == 0) && (row - ship.getSize() >= -1) &&
                           (row + ship.getSize() <= 19);
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

void BoardController::blockTiles(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix, int column, int row) {
    if (ship.isShipHorizontal()) {
        for (int j = row - 2; j <= row + 2; j++) {
            for (int i = column - ship.getSize()-1; i <= column + ship.getSize()+1; i++) {
                if (i >= 0 && j >= 0 && i <= 18 && j <= 18 && (matrix[i][j].getStatus()!= PlacementArray::forbidden)) {
                    matrix[i][j].setStatus(PlacementArray::forbidden);
                }
            }
        }
    } else {
        for (int j = row - ship.getSize()-1; j <= row + ship.getSize()+1; j++) {
            for (int i = column - 2; i <= column + 2; i++) {
                if (i >= 0 && j >= 0 && i <= 18 && j <= 18 && (matrix[i][j].getStatus()!= PlacementArray::forbidden)) {
                    matrix[i][j].setStatus(PlacementArray::forbidden);
                }
            }
        }
    }
}

void BoardController::updateBlockade(Fleet &fleet, std::vector< std::vector<PlacementArray>> &matrix1, std::vector< std::vector<GameArray>> &matrix2){
    for(auto & it : fleet.getFleet()){
        if(it.operator*().isOnBoard() && !it.operator*().isCanDrag()){
            blockTiles(it.operator*(), matrix1, it.operator*().getPlacementBoardPosX(),
                       it.operator*().getPlacementBoardPosY());
            setPlacementArrayToShip(it.operator*(), matrix1);
        }
    }
    matrix1[1][1].setStatus(PlacementArray::forbidden);
    for (auto j = 0; j < matrix2.size(); j++) {
        for (auto i = 0; i < matrix2.size(); i++) {
            if(matrix1[2*i][2*j].getStatus() == PlacementArray::ship){
                matrix2[i][j].setStatus(GameArray::ship);
            }
        }
    }
}

void BoardController::resetBoard(std::vector< std::vector<PlacementArray>> &matrix1, std::vector< std::vector<GameArray>> &matrix2){
    for (auto j = 0; j < matrix1.size(); j++) {
        for (auto i = 0; i < matrix1.size(); i++) {
            matrix1[i][j].setStatus(PlacementArray::empty);
        }
    }
    for (auto j = 0; j < matrix2.size(); j++) {
        for (auto i = 0; i < matrix2.size(); i++) {
            matrix2[i][j].setStatus(GameArray::empty);
        }
    }
}

void BoardController::resetShipPlacement(Ship &ship) {
    ship.getRectangle().setPosition(sf::Vector2f(ship.getStartPosX(), ship.getStartPosY()));
    ship.setOnStartPos(true);
    ship.setOnBoard(false);
    ship.setPlacementBoardPosX(1);
    ship.setPlacementBoardPosY(1);
    ship.getRectangle().setRotation(ship.getDefaultRotation());
    ship.setShipHorizontal(ship.getDefaultRotation() != 0); // wyzerowanie stanu obrotu
    ship.clearPositions();
}

void BoardController::resetFleetPlacement(Fleet &fleet){
    for(auto & it : fleet.getFleet()){
        if(it.operator*().isOnBoard() && !it.operator*().isCanDrag()){
            resetShipPlacement(it.operator*());
        }
    }
}

void BoardController::positionGenerator(int &i, int &j){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed);
    std::uniform_int_distribution<int> distribution(0,18);
    i = distribution(mt_rand);
    j = distribution(mt_rand);
}

void BoardController::rotationGenerator(int &rotation){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed);
    std::uniform_int_distribution<int> distribution(0,1);
    rotation = distribution(mt_rand);
}

void BoardController::randomizeShipPosition(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix){
    auto startTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds;
    if(ship.isOnStartPos()) {
        while (!ship.isOnBoard()) {
            auto currentTime = std::chrono::system_clock::now();
            elapsed_seconds = currentTime - startTime;
            if(elapsed_seconds.count() > 1){ //jezeli czas wykonania jest za dlugi przerwij operację
                break;
            }
            int i, j, rotation;
            positionGenerator(i, j);
            rotationGenerator(rotation);
            if(rotation == 0){
                ship.setRotation(0);
                ship.setShipHorizontal(false);
            } else {
                ship.setRotation(90);
                ship.setShipHorizontal(true);
            }
            if ((matrix[i][j].getStatus() == PlacementArray::empty) && checkPlace(ship, matrix, i, j)) {
                ship.getRectangle().setPosition(sf::Vector2f(
                        matrix[i][j].getPosX() + (matrix[i][j].getTileSize() / 2),
                        matrix[i][j].getPosY() + (matrix[i][j].getTileSize() / 2)));
                ship.setPlacementBoardPosX(i);
                ship.setPlacementBoardPosY(j);

                ship.setOnBoard(true);
                ship.setOnStartPos(false);
            }
        }
    }
}

void BoardController::randomizeFleetPosition(Fleet &fleet, std::vector< std::vector<PlacementArray>> &matrix1, std::vector< std::vector<GameArray>> &matrix2){
    for(auto it = fleet.getFleet().rbegin(); it != fleet.getFleet().rend(); ++it){
        randomizeShipPosition(it->operator*(), matrix1);
        if(!it.operator*()->isOnBoard()){ // jezeli operacja zostala przerwana zresetuj ustawienie i sproboj ponownie
            BoardController::resetFleetPlacement(fleet);
            BoardController::randomizeFleetPosition(fleet, matrix1, matrix2);
        }
        updateBlockade(fleet, matrix1, matrix2);
        fleet.checkPlacement();
    }
    if(!fleet.isPlacedOnBoard()){
        throw std::runtime_error("Fleet is not placed");
    }
}

void BoardController::setPlacementArrayToShip(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix){
    int column = ship.getPlacementBoardPosX();
    int row = ship.getPlacementBoardPosY();
    if (ship.getSize() == 2) {
        if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
            matrix[column - 1][row].setStatus(PlacementArray::ship);
            matrix[column + 1][row].setStatus(PlacementArray::ship);
        } else { // jezeli jest ustawiony pionowo
            matrix[column][row - 1].setStatus(PlacementArray::ship);
            matrix[column][row + 1].setStatus(PlacementArray::ship);
        }
    } else if (ship.getSize() == 4) {
        if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
            matrix[column - 3][row].setStatus(PlacementArray::ship);
            matrix[column - 1][row].setStatus(PlacementArray::ship);
            matrix[column + 1][row].setStatus(PlacementArray::ship);
            matrix[column + 3][row].setStatus(PlacementArray::ship);
        } else { // jezeli jest ustawiony pionowo
            matrix[column][row - 3].setStatus(PlacementArray::ship);
            matrix[column][row - 1].setStatus(PlacementArray::ship);
            matrix[column][row + 1].setStatus(PlacementArray::ship);
            matrix[column][row + 3].setStatus(PlacementArray::ship);
        }
    } else if (ship.getSize() == 3) {
        if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
            matrix[column - 2][row].setStatus(PlacementArray::ship);
            matrix[column][row].setStatus(PlacementArray::ship);
            matrix[column + 2][row].setStatus(PlacementArray::ship);
        } else { // jezeli jest ustawiony pionowo
            matrix[column][row - 2].setStatus(PlacementArray::ship);
            matrix[column][row].setStatus(PlacementArray::ship);
            matrix[column][row + 2].setStatus(PlacementArray::ship);
        }
    } else if (ship.getSize() == 5) {
        if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
            matrix[column - 4][row].setStatus(PlacementArray::ship);
            matrix[column - 2][row].setStatus(PlacementArray::ship);
            matrix[column][row].setStatus(PlacementArray::ship);
            matrix[column + 2][row].setStatus(PlacementArray::ship);
            matrix[column + 4][row].setStatus(PlacementArray::ship);
        } else { // jezeli jest ustawiony pionowo
            matrix[column][row - 4].setStatus(PlacementArray::ship);
            matrix[column][row - 2].setStatus(PlacementArray::ship);
            matrix[column][row].setStatus(PlacementArray::ship);
            matrix[column][row + 2].setStatus(PlacementArray::ship);
            matrix[column][row + 4].setStatus(PlacementArray::ship);
        }
    }
}

void BoardController::addGameArrayPositionsToShip(Ship &ship, std::vector< std::vector<PlacementArray>> &matrix){
    int column = ship.getPlacementBoardPosX();
    int row = ship.getPlacementBoardPosY();
    if (ship.getSize() == 2) {
        if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
            ship.addPosition((column - 1 )/2, row/2);
            ship.addPosition((column + 1)/2, row/2);
        } else { // jezeli jest ustawiony pionowo
            ship.addPosition(column/2, (row - 1)/2);
            ship.addPosition(column/2, (row + 1)/2);
        }
    } else if (ship.getSize() == 4) {
        if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
            ship.addPosition((column - 3)/2, row/2);
            ship.addPosition((column - 1)/2, row/2);
            ship.addPosition((column + 1)/2, row/2);
            ship.addPosition((column + 3)/2, row/2);
        } else { // jezeli jest ustawiony pionowo
            ship.addPosition(column/2, (row - 3)/2);
            ship.addPosition(column/2, (row - 1)/2);
            ship.addPosition(column/2, (row + 1)/2);
            ship.addPosition(column/2, (row + 3)/2);
        }
    } else if (ship.getSize() == 3) {
        if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
            ship.addPosition((column - 2)/2, row/2);
            ship.addPosition(column/2, row/2);
            ship.addPosition((column + 2)/2, row/2);
        } else { // jezeli jest ustawiony pionowo
            ship.addPosition(column/2, (row - 2)/2);
            ship.addPosition(column/2, row/2);
            ship.addPosition(column/2, (row + 2)/2);
        }
    } else if (ship.getSize() == 5) {
        if (ship.isShipHorizontal()) { // jezeli jest ustawiony horyzontalnie
            ship.addPosition((column - 4)/2, row/2);
            ship.addPosition((column - 2)/2, row/2);
            ship.addPosition(column/2, row/2);
            ship.addPosition((column + 2)/2, row/2);
            ship.addPosition((column + 4)/2, row/2);
        } else { // jezeli jest ustawiony pionowo
            ship.addPosition(column/2, (row - 4)/2);
            ship.addPosition(column/2, (row - 2)/2);
            ship.addPosition(column/2, row/2);
            ship.addPosition(column/2, (row + 2)/2);
            ship.addPosition(column/2, (row + 4)/2);
        }
    }
}
