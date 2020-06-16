
#ifndef BATTLESHIPS_SCORE_H
#define BATTLESHIPS_SCORE_H

class Score {
    int currentScore;
public:
    Score ();

    int getCurrentScore() const;
    void setCurrentScore(int currentScore);

    void userMissedShot();
    void userShipHit();
    void userShipDestroyed();

    void computerMissedShot();
    void computerShipHit();
    void computerShipDestroyed();
};

#endif //BATTLESHIPS_SCORE_H
