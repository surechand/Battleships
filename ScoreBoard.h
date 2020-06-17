
#ifndef BATTLESHIPS_SCOREBOARD_H
#define BATTLESHIPS_SCOREBOARD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class ScoreBoard {
    std::multimap<int, std::string> scorelist;
public:
    ScoreBoard();

    /*Metoda dodająca nowy wynik wygranej do tabeli wyników*/
    void AddNewScore(int &newScore, std::string &playerName);

    /*Metoda wyświetlająca tabelę wyników*/
    void ShowScoreBoard();

    /*Metoda zapisująca aktualny stan tabeli wyników*/
    void SaveScoreBoard();
};


#endif //BATTLESHIPS_SCOREBOARD_H
