#ifndef HIGHERGROUND_CPP_GAMEMENU_H
#define HIGHERGROUND_CPP_GAMEMENU_H
#include <iostream>
#include <iosfwd>
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include "FilesBank.h"
#include <Button.h>
#include "Player.h"
#include "Platforms.h"

class GameMenu {
public:
    GameMenu() = default;
    explicit GameMenu(const sf::Vector2u &windowSize);
    GameMenu(const GameMenu&) = default;
    ~GameMenu() = default;

    bool Menu(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player);
    bool Pause(sf::RenderWindow &window, const sf::Sprite &bgImage, Platforms &platforms, Player &player, int &pauseTime);
    bool Exit(sf::RenderWindow &window) const;

private:
    sf::Vector2u winSize;

    sf::Clock clock;
    sf::Text textLogo, textPause;
    bool exit = false;
    bool MainMenu = true;
    std::vector<Button> buttons;
    sf::RectangleShape menuSquare;
};


#endif //HIGHERGROUND_CPP_GAMEMENU_H
