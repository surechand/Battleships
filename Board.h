#ifndef BATTLESHIPS_BOARD_H
#define BATTLESHIPS_BOARD_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "PlacementArray.h"
#include "GameArray.h"

class Board : public sf::Drawable {
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    /*Parametry wielkości tła i miejsca umieszczania elementów rozgrywki*/
    const float backgroundWidth { 1024.0 }, backgroundHeight { 768.0 };
    const float userGridPos_X {41.0}, userGridPos_Y {299.0}, computerGridPos_X {585.0}, computerGridPos_Y {299.0};
    const float userTileStartPos_X {52.0}, userTileStartPos_Y {310.0}, computerTileStartPos_X {596.0}, computerTileStartPos_Y {310.0};
public:
    const int placementArraySize = 19, gameArraySize = 10;
    /*Macierze odpowiadające za umieszczenie statku na planszy.
     * Pomimo kwadratowego krztałtu posiadają one "dziury" uniemożliwiające umieszczanie statków na połączeniu 4 kratek macierzy rozgrywki.
     * Dziury te są odkładane na pozycję (-1,-1) i blokowane. Nie jest to rozwiązanie optymalne, jednak ułatwia odwoływanie się do macierzy*/
    std::vector< std::vector<PlacementArray>> userPlacementMatrix;
    std::vector< std::vector<PlacementArray>> computerPlacementMatrix;
    /*Macierze odpowiadające za rozgrywkę*/
    std::vector< std::vector<GameArray>> userGameMatrix;
    std::vector< std::vector<GameArray>> computerGameMatrix;
    /*Konstruktor*/
    Board();
    /*Destruktor domyślny*/
    ~Board() override = default;
    /*Przeciążona metoda klasy sf::Drawable pozwalająca na narysowanie na ekranie tła wraz z macierzami rozgrywki*/
    void draw (sf::RenderTarget& target, sf::RenderStates state) const override;
    /*Metoda inicjująca macierz umieszczania*/
    void initPlacementMatrix(std::vector< std::vector<PlacementArray>> &matrix, float tileStartPos_X, float tileStartPos_Y) const;
    /*Metoda inicjująca macierz rozgrywki*/
    void initGameMatrix(std::vector< std::vector<GameArray>> &matrix, float tileStartPos_X, float tileStartPos_Y) const;
    /*Metoda inicjująca macierze umieszczania dla użytkownika i komputera*/
    void initUserCompPlacementMatrix();
    /*Metoda inicjująca macierze rozgrywki dla użytkownika i komputera*/
    void initUserCompGameMatrix();
};


#endif //BATTLESHIPS_BOARD_H
