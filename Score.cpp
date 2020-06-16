
#include "Score.h"

Score::Score() {
    this->currentScore = 100;
}

int Score::getCurrentScore() const {
    return currentScore;
}

void Score::setCurrentScore(int currentScore) {
    Score::currentScore = currentScore;
}

void Score::userMissedShot(){
    this->currentScore -= 1;
}

void Score::userShipHit() {
    this->currentScore -=2;
}

void Score::userShipDestroyed(){
    this->currentScore -= 10;
}

void Score::computerMissedShot(){
    this->currentScore += 1;
}

void Score::computerShipHit(){
    this->currentScore += 2;
}

void Score::computerShipDestroyed(){
    this->currentScore += 10;
}
