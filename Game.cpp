
#include "Game.h"

void Game::init() {
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(1024, 768), "Battleships", sf::Style::Default, settings);
    window.setFramerateLimit(200);
    this->gameEnded = this->computerShot = false;
    fireGenerator(lastHiti, lastHitj); //create first coordinations
}

int Game::loop(){
    Score score;
    Board background;
    sf::Event event{};
    BoardController controller;
    Fleet userFleet, computerFleet;
    userFleet.initFleet(true);
    computerFleet.initFleet(false);
    userFleet.setFleetHp();
    computerFleet.setFleetHp();
    try {
        background.initUserCompPlacementMatrix();
        background.initUserCompGameMatrix();
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of range error:" << oor.what() << std::endl;
    }
    ResetButton resetButton(512, 340, 40);
    RandomizeButton randomizeButton(512,440,40);
    PlayButton playButton(512, 540, 40);
    try{
        resetButton.loadTexture();
        randomizeButton.loadTexture();
        playButton.loadTexture();
    }
    catch (std::runtime_error & texterr) {
        std::cerr << "Runtime error:" << texterr.what() << std::endl;
    }
    try {
        while (window.isOpen()) {
            if (!window.isOpen() && event.type != sf::Event::Closed) {
                throw std::runtime_error("Window is not opened");
            }
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || gameEnded) {
                    window.close();
                    break;
                }
                window.clear(sf::Color::White);
                window.draw(background);
                window.draw(playButton);
                window.draw(userFleet);
                if(computerFleet.isLocked() && userFleet.isLocked()) {
                    if(playerTurn(event, computerFleet, background, score)) {
                        if(computerFleet.getHp() == 0) {
                            gameEnded = true;
                            window.close();
                            return score.getCurrentScore();
                        }
                        computerTurn(event, userFleet, background, score);
                        if(userFleet.getHp() == 0) {
                            gameEnded = true;
//                            window.close();
                            return 0;
                        }
                    }
                    for (const auto & it : userFleet.getFleet()) {
                        if(it.operator*().getHpBar() == 0){
                            it.operator*().loadDestroyedTexture();
                        }
                    }
                    for (const auto & it : computerFleet.getFleet()) {
                        if(it.operator*().getHpBar() == 0){
                            window.draw(it.operator*());
                            it.operator*().loadDestroyedTexture();
                        }
                    }
                } else {
                    window.draw(resetButton);
                    window.draw(randomizeButton);
                    try {
                        resetButton.action(event, userFleet, computerFleet, background);
                        randomizeButton.action(event, userFleet, computerFleet, background);
                        playButton.action(event, userFleet, computerFleet, background);
                    }
                    catch (std::runtime_error &rnt) {
                        std::cout << "Runtime_error:" << rnt.what() << std::endl;
                    }
                    for (const auto & it : userFleet.getFleet()) {
                        controller.setShipPosition(event, it.operator*(), background);
                    }
                    userFleet.checkPlacement();
                    BoardController::resetBoard(background.userPlacementMatrix, background.userGameMatrix);
                    BoardController::updateBlockade(userFleet, background.userPlacementMatrix,
                                                    background.userGameMatrix);
                }
                BoardController::checkBoard(event, background);
            }
            window.display();
        }
    }
    catch (std::runtime_error & wno) {
        std::cerr << "Runtime error: " << wno.what() << std::endl;
    }
}

bool Game::playerTurn(sf::Event &action, Fleet &compFleet, Board &background, Score &score){
    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left) {
        for (auto j = 0; j < background.gameArraySize; j++) {
            for (auto i = 0; i < background.gameArraySize; i++) {
                if (background.computerGameMatrix[i][j].getSquare().getGlobalBounds().contains(action.mouseButton.x, action.mouseButton.y)) {
                    if (background.computerGameMatrix[i][j].getStatus() == GameArray::empty) {
                        background.computerGameMatrix[i][j].setStatus(GameArray::missed);
                        score.userMissedShot();
                        return true;
                    } else if (background.computerGameMatrix[i][j].getStatus() == GameArray::ship){
                        background.computerGameMatrix[i][j].setStatus(GameArray::fire);
                        compFleet.getFleet().operator[](compFleet.getShipFromThatPosition(i, j))->setHpBar(compFleet.getFleet().operator[](compFleet.getShipFromThatPosition(i, j))->getHpBar()-1);
                        compFleet.setHp(compFleet.getHp()-1);
                        score.computerShipHit();
                        if(compFleet.getFleet().operator[](compFleet.getShipFromThatPosition(i, j))->getHpBar() == 0){
                            score.computerShipHit();
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Game::computerTurn(sf::Event &action, Fleet &userFleet, Board &background, Score &score){
    computerShot = false;
    while(!computerShot) {
        int i, j;
        fireGenerator(i, j);
        if (background.userGameMatrix[lastHiti][lastHitj].getStatus() == GameArray::empty ||
            background.userGameMatrix[lastHiti][lastHitj].getStatus() == GameArray::missed) {
            if (background.userGameMatrix[i][j].getStatus() == GameArray::empty) {
                background.userGameMatrix[i][j].setStatus(GameArray::missed);
                score.computerMissedShot();
                computerShot = true;
            } else if (background.userGameMatrix[i][j].getStatus() == GameArray::ship) {
                background.userGameMatrix[i][j].setStatus(GameArray::fire);
                last2Hiti = i;
                last2Hitj = j;
                computerShot = true;
                userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->setHpBar(
                        userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() - 1);
                userFleet.setHp(userFleet.getHp() - 1);
                score.userShipHit();
                if(userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() == 0){
                    score.userShipHit();
                }
            }
        } else {
            int way;
            decisionGenerator(way);
            if (way == 1 && i < 8) {
                if (background.userGameMatrix[lastHiti + 1][lastHitj].getStatus() == GameArray::empty &&
                    background.userGameMatrix[lastHiti + 1][lastHitj].getStatus() != GameArray::missed
                    && background.userGameMatrix[lastHiti + 1][lastHitj].getStatus() != GameArray::fire) {
                    background.userGameMatrix[lastHiti + 1][lastHitj].setStatus(GameArray::missed);
                    score.computerMissedShot();
                    lastHiti = last2Hiti;
                    lastHitj = last2Hitj;
                    computerShot = true;
                    computerTurn(action, userFleet, background, score);
                } else if (background.userGameMatrix[lastHiti + 1][lastHitj].getStatus() == GameArray::ship) {
                    background.userGameMatrix[lastHiti + 1][lastHitj].setStatus(GameArray::fire);
                    last2Hiti = lastHiti;
                    last2Hitj = lastHitj;
                    lastHiti = i + 1;
                    lastHitj = j;
                    computerShot = true;
                    userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->setHpBar(
                            userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() - 1);
                    userFleet.setHp(userFleet.getHp() - 1);
                    score.userShipHit();
                    if(userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() == 0){
                        score.userShipHit();
                    }
                }
            } else if (way == 2 && j < 8) {
                if (background.userGameMatrix[lastHiti][lastHitj + 1].getStatus() == GameArray::empty &&
                    background.userGameMatrix[lastHiti][lastHitj+ 1].getStatus() != GameArray::missed
                    && background.userGameMatrix[lastHiti ][lastHitj+ 1].getStatus() != GameArray::fire) {
                    background.userGameMatrix[lastHiti][lastHitj + 1].setStatus(GameArray::missed);
                    score.computerMissedShot();
                    computerShot = true;
                    computerTurn(action, userFleet, background, score);
                } else if (background.userGameMatrix[lastHiti][lastHitj + 1].getStatus() == GameArray::ship) {
                    background.userGameMatrix[lastHiti][lastHitj + 1].setStatus(GameArray::fire);
                    last2Hiti = lastHiti;
                    last2Hitj = lastHitj;
                    lastHiti = i;
                    lastHitj = j + 1;
                    computerShot = true;
                    userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->setHpBar(
                            userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() - 1);
                    userFleet.setHp(userFleet.getHp() - 1);
                    score.userShipHit();
                    if(userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() == 0){
                        score.userShipHit();
                    }
                }
            } else if (way == 3 && i > 0) {
                if (background.userGameMatrix[lastHiti - 1][lastHitj].getStatus() == GameArray::empty &&
                    background.userGameMatrix[lastHiti - 1][lastHitj].getStatus() != GameArray::missed
                    && background.userGameMatrix[lastHiti - 1][lastHitj].getStatus() != GameArray::fire) {
                    background.userGameMatrix[lastHiti - 1][lastHitj].setStatus(GameArray::missed);
                    score.computerMissedShot();
                    computerShot = true;
                    computerTurn(action, userFleet, background, score);
                } else if (background.userGameMatrix[lastHiti - 1][lastHitj].getStatus() == GameArray::ship) {
                    background.userGameMatrix[lastHiti - 1][lastHitj].setStatus(GameArray::fire);
                    last2Hiti = lastHiti;
                    last2Hitj = lastHitj;
                    lastHiti = i - 1;
                    lastHitj = j;
                    computerShot = true;
                    userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->setHpBar(
                            userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() - 1);
                    userFleet.setHp(userFleet.getHp() - 1);
                    score.userShipHit();
                    if(userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() == 0){
                        score.userShipHit();
                    }
                }
            } else if (way == 4 && j > 0) {
                if (background.userGameMatrix[lastHiti][lastHitj - 1].getStatus() == GameArray::empty &&
                    background.userGameMatrix[lastHiti][lastHitj- 1].getStatus() != GameArray::missed
                    && background.userGameMatrix[lastHiti][lastHitj- 1].getStatus() != GameArray::fire) {
                    background.userGameMatrix[lastHiti][lastHitj - 1].setStatus(GameArray::missed);
                    score.computerMissedShot();
                    computerShot = true;
                    computerTurn(action, userFleet, background, score);
                } else if (background.userGameMatrix[lastHiti][lastHitj - 1].getStatus() == GameArray::ship) {
                    background.userGameMatrix[lastHiti][lastHitj - 1].setStatus(GameArray::fire);
                    last2Hiti = lastHiti;
                    last2Hitj = lastHitj;
                    lastHiti = i;
                    lastHitj = j - 1;
                    computerShot = true;
                    userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->setHpBar(
                            userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() - 1);
                    userFleet.setHp(userFleet.getHp() - 1);
                    score.userShipHit();
                    if(userFleet.getFleet().operator[](userFleet.getShipFromThatPosition(i, j))->getHpBar() == 0){
                        score.userShipHit();
                    }
                }
            }
        }
    }
}

void Game::fireGenerator(int &i, int &j){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed);
    std::uniform_int_distribution<int> distribution(0,9);
    i = distribution(mt_rand);
    j = distribution(mt_rand);
}

void Game::decisionGenerator(int &i){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed);
    std::uniform_int_distribution<int> distribution(1,4);
    i = distribution(mt_rand);
}

void Game::setGameEnded(bool isEnd) {
    Game::gameEnded = isEnd;
}
