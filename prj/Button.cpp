#include "Button.h"

Button::Button(
        sf::Texture& texture_, sf::Vector2f textureRectSize, sf::Vector2f beginPosTexture,
        const sf::Vector2f &buttonSize, const sf::Vector2f &nextButton_, const std::string &buttonName, sf::Font& font) {
    size = buttonSize;
    button.setSize(size);
    nextButton = nextButton_;
    button.setTexture(&texture_);
    button.setOrigin(size.x / 2, size.y / 2);
    beginRect = beginPosTexture;
    sizeRect = textureRectSize;
    text.setFont(font);
    text.setString(buttonName);
    text.setCharacterSize(20);
    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
    button.setTextureRect(sf::IntRect(beginRect.x, beginRect.y, sizeRect.x, sizeRect.y));
    isClick = false;
    choose = false;
}

void Button::setPos(Button& buttonAbove, const float &interval) {
    button.setPosition(buttonAbove.button.getPosition().x, buttonAbove.button.getPosition().y + size.y + interval);
    text.setPosition(button.getPosition().x, button.getPosition().y - interval / 2);
    container = sf::IntRect(button.getPosition().x - size.x / 2, button.getPosition().y - size.y / 2, size.x, size.y);
}

void Button::setPos(sf::RectangleShape& back, const float &interval) {
    button.setPosition(back.getPosition().x, back.getPosition().y - back.getSize().y / 2 + interval + size.y / 2);
    text.setPosition(button.getPosition().x, button.getPosition().y - interval/2);
    container = sf::IntRect(button.getPosition().x - size.x / 2, button.getPosition().y - size.y / 2, size.x, size.y);
}

void Button::setPos(sf::Vector2f position) {
    button.setPosition(position);
    text.setPosition(button.getPosition().x, button.getPosition().y - 5);
    container = sf::IntRect(button.getPosition().x - size.x / 2, button.getPosition().y - size.y / 2, size.x, size.y);
}

void Button::setSizeRelativeText() {
    button.setSize(sf::Vector2f(text.getGlobalBounds().width + 40, text.getGlobalBounds().height + 20));
    button.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
    size = button.getSize();
    container = sf::IntRect(button.getPosition().x - size.x / 2, button.getPosition().y - size.y / 2, size.x, size.y);
}

bool Button::Clicked(sf::RenderWindow& window, sf::Sound& soundClick, sf::Sound& soundRoll) {
    int currentFrame = clock.getElapsedTime().asMilliseconds() / 16;

    isClick = !isClick;
    if (!container.contains(sf::Mouse::getPosition(window))) {
        choose = false;
    } else {
        isClick = false;
        button.setFillColor(sf::Color::White);
        button.setTextureRect(sf::IntRect(beginRect.x, beginRect.y, sizeRect.x, sizeRect.y));
    }

    if (container.contains(sf::Mouse::getPosition(window))) {
        if (!choose) soundRoll.play();
        button.setFillColor(sf::Color::Green);
        choose = true;
    } else {
        button.setFillColor(sf::Color::White);
        choose = false;
    }

    if (currentFrame > 20) {
        button.setTextureRect(sf::IntRect(beginRect.x, beginRect.y, sizeRect.x, sizeRect.y));
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && choose && currentFrame > 20) {
        isClick = true;
        button.setTextureRect(sf::IntRect(nextButton.x, nextButton.y, sizeRect.x, sizeRect.y - 5));
        soundClick.play();
        clock.restart();
    }

    return isClick;
}
