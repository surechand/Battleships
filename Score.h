
#ifndef BATTLESHIPS_SCORE_H
#define BATTLESHIPS_SCORE_H

class Score {
    int currentScore;
public:
    Score ();

    int getCurrentScore() const;
    void setCurrentScore(int currentScore);
    /*Zmienia wynik końcowy w przypadku nietrafienia przez gracza*/
    void userMissedShot();
    /*Zmienia wynik końcowy w przypadku trafionego statku gracza*/
    void userShipHit();
    /*Zmienia wynik końcowy w przypadku zniszczonego statku gracza*/
    void userShipDestroyed();

    /*Zmienia wynik końcowy w przypadku nietrafienia przez komputer*/
    void computerMissedShot();
    /*Zmienia wynik końcowy w przypadku trafionego statku komputera*/
    void computerShipHit();
    /*Zmienia wynik końcowy w przypadku zniszczonego statku komputera*/
    void computerShipDestroyed();
};

#endif //BATTLESHIPS_SCORE_H
