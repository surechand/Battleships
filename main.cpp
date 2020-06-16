#include <iostream>
#include <SFML/Graphics.hpp>
#include "BoardController.h"
#include "Game.h"

int main(int argc,char *argv[]) {
    Game game;
    game.init();
    game.loop();
    return 0;
}