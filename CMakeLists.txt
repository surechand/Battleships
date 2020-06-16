cmake_minimum_required(VERSION 3.12)
project(Battleships)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "F:/PK4/SFML/lib/cmake/SFML")

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Battleships main.cpp Ship.cpp Ship.h Board.cpp Board.h PlacementArray.cpp PlacementArray.h BoardController.cpp BoardController.h Fleet.cpp Fleet.h Button.cpp Button.h ResetButton.cpp ResetButton.h RandomizeButton.cpp RandomizeButton.h Game.cpp Game.h PlayButton.cpp PlayButton.h GameArray.cpp GameArray.h)
target_link_libraries(Battleships sfml-graphics sfml-audio)

