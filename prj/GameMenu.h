#ifndef HIGHERGROUND_CPP_GAMEMENU_H
#define HIGHERGROUND_CPP_GAMEMENU_H
#include <iostream>
#include <iosfwd>
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <Button.h>

enum Buttons {
    Play,
    Settings,
    Exit
};

class GameMenu {
public:
    GameMenu() = default;
    GameMenu(const sf::Vector2u &windowSize);
    GameMenu(const GameMenu&) = default;
    ~GameMenu() = default;

    bool Menu(sf::RenderWindow &window, const sf::Sprite &bgImage);

private:
    sf::Vector2u winSize;

    Button button_1, button_2, button_3;
    sf::RectangleShape menuSquare;
    sf::RectangleShape button1;
    sf::RectangleShape button2;
};


#endif //HIGHERGROUND_CPP_GAMEMENU_H
