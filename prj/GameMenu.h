#ifndef HIGHERGROUND_CPP_GAMEMENU_H
#define HIGHERGROUND_CPP_GAMEMENU_H
#include "Records.h"
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <Button.h>
#include "Player.h"
#include "Platforms.h"

class GameMenu {
public:
    GameMenu() = default;
    GameMenu(const sf::Vector2u &windowSize, Records &records_);
    GameMenu(const GameMenu&) = delete;
    ~GameMenu() = default;

    bool Menu(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player);
    bool Pause(sf::RenderWindow &window, const sf::Sprite &bgImage, Platforms &platforms, Player &player, int &pauseTime);
    bool Exit(sf::RenderWindow &window) const;
    bool TryAgain(sf::RenderWindow &window, const sf::Sprite &bgImage, Platforms &platforms, Player &player);

    std::string GetNickName();
private:
    void inline InitializeText();
    void inline InitializeButtons();
    void inline InitializeLogos();

    void ShowRecords(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player);

    static sf::IntRect NickNameArea(sf::Text& text);
    static bool enterText(sf::Event& event, sf::Text& text);
    void write();
    void writeName(sf::Text &tempNick);
    const std::string path = "src/top/";
    sf::Text NickName;
    Records records;

    sf::Vector2u winSize;

    sf::Clock clock;
    sf::Text textLogo, textPause, name;
    bool exit = false;
    bool MainMenu = true;
    std::vector<Button> buttons;
    sf::RectangleShape menuSquare;
};

#endif //HIGHERGROUND_CPP_GAMEMENU_H
