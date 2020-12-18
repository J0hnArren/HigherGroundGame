#ifndef HIGHERGROUND_CPP_BUTTON_H
#define HIGHERGROUND_CPP_BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iosfwd>

class Button {
public:
    Button() = default;
    Button(const Button&) = default;
    Button(
            sf::Texture& texture_,
            sf::Vector2f textureRectSize,
            sf::Vector2f beginPosTexture,
            const sf::Vector2f &buttonSize,
            const sf::Vector2f &nextButton_,
            const std::string &buttonName,
            sf::Font& font
            );
    ~Button() = default;

    void setPos(Button& buttonAbove, const float &interval);
    void setPos(sf::RectangleShape& back, const float &interval);
    void setPos(sf::Vector2f position);
    void setSizeRelativeText();
    bool Clicked(sf::RenderWindow& window, sf::Sound& soundClick, sf::Sound& soundRoll);
private:
    sf::Clock clock;
    bool choose;
    sf::Text text;
    sf::Vector2f size;
    sf::Vector2f beginRect;
    sf::Vector2f sizeRect;
    sf::Vector2f nextButton;
    sf::IntRect container;
    sf::RectangleShape button;
    bool isClick;
};


#endif //HIGHERGROUND_CPP_BUTTON_H
