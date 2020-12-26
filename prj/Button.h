#ifndef HIGHERGROUND_CPP_BUTTON_H
#define HIGHERGROUND_CPP_BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iosfwd>
#include "FilesBank.h"

class Button {
public:
    Button() = default;
    Button(const Button&) = default;
    Button(
            sf::Texture &texture_,
            const sf::Vector2f &buttonSize,
            const sf::Vector2f &beginPosTexture,
            const sf::Vector2f &textureRectSize,
            const sf::Vector2f &nextButtonSize,
            const sf::Vector2f &nextBeginPosTexture,
            const sf::Vector2f &nextTextureRectSize,
            const std::string &buttonName,
            const sf::Font& font);
    ~Button() = default;

    void setPos(Button& buttonAbove, const float &interval);
    void setPos(sf::RectangleShape& back, const float &interval);
    void setPos(const sf::Vector2f &position);
    void setSizeRelativeText();
    bool Clicked(sf::RenderWindow& window, sf::Sound& soundClick, sf::Sound& soundRoll);

    sf::Text text;
    sf::RectangleShape button;
private:
    sf::Clock clock;
    sf::IntRect container;

    sf::Vector2f size1;
    sf::Vector2f beginRect;
    sf::Vector2f sizeRect;
    sf::Vector2f size2;
    sf::Vector2f nextBeginRect;
    sf::Vector2f nextSizeRect;

    bool choose = false;
    bool isClick = true;
};


#endif //HIGHERGROUND_CPP_BUTTON_H
