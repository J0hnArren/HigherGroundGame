#ifndef HIGHERGROUND_CPP_GAMEMENU_H
#define HIGHERGROUND_CPP_GAMEMENU_H
#include <iostream>
#include <iosfwd>
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <Button.h>
#include "Player.h"

class GameMenu {
public:
    GameMenu() = default;
    explicit GameMenu(const sf::Vector2u &windowSize);
    GameMenu(const GameMenu&) = default;
    ~GameMenu() = default;

    bool Menu(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player);
    bool Exit();

private:
    sf::Vector2u winSize;

    sf::Clock clock;
    sf::Text text;
    bool exit = false;

    Button playButton, settingsButton, exitButton;
    std::vector<Button> buttons;
    sf::RectangleShape menuSquare;
};


#endif //HIGHERGROUND_CPP_GAMEMENU_H
