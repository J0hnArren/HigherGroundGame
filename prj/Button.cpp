#include "Button.h"

Button::Button(
        sf::Texture &texture_, // texture with both button states
        const sf::Vector2f &buttonSize, // size of 1 rectangle
        const sf::Vector2f &beginPosTexture, // 1 texture start position in pixel
        const sf::Vector2f &textureRectSize, // 1 texture size in pixels
        const sf::Vector2f &nextButtonSize, // size of 2 rectangle
        const sf::Vector2f &nextBeginPosTexture, // 2 texture start position
        const sf::Vector2f &nextTextureRectSize, // 2 texture size in pixels
        const std::string &buttonName, // text on the button
        const sf::Font &font) {
    size1 = buttonSize;
    button.setSize(size1);
    button.setOrigin(size1.x / 2, size1.y / 2);
    button.setTexture(&texture_);
    beginRect = beginPosTexture;
    sizeRect = textureRectSize;
    button.setTextureRect(sf::IntRect(beginRect.x, beginRect.y, sizeRect.x, sizeRect.y));

    size2 = nextButtonSize * 0.75f;
    nextBeginRect = nextBeginPosTexture;
    nextSizeRect = nextTextureRectSize;

    text.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    text.setString(buttonName);
    text.setCharacterSize(80);
    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
}

//void Button::setPos(Button& buttonAbove, const float &interval) {
//    button.setPosition(buttonAbove.button.getPosition().x, buttonAbove.button.getPosition().y + size1.y + interval);
//    text.setPosition(button.getPosition().x, button.getPosition().y - interval / 2);
//    container = sf::IntRect(button.getPosition().x - size1.x / 2, button.getPosition().y - size1.y / 2, size1.x, size1.y);
//}
//
//void Button::setPos(sf::RectangleShape& back, const float &interval) {
//    button.setPosition(back.getPosition().x, back.getPosition().y - back.getSize().y / 2 + interval + size1.y / 2);
//    text.setPosition(button.getPosition().x, button.getPosition().y - interval/2);
//    container = sf::IntRect(button.getPosition().x - size1.x / 2, button.getPosition().y - size1.y / 2, size1.x, size1.y);
//}

void Button::setPos(const sf::Vector2f &position) {
    button.setPosition(position);
    text.setPosition(button.getPosition().x, button.getPosition().y - 20);
    container = sf::IntRect(button.getPosition().x - size1.x / 2,
                            button.getPosition().y - size1.y / 2,
                            size1.x, size1.y);
}

//void Button::setSizeRelativeText() {
//    button.setSize(sf::Vector2f(text.getGlobalBounds().width + 40, text.getGlobalBounds().height + 20));
//    button.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
//    size1 = button.getSize();
//    container = sf::IntRect(
//            button.getPosition().x - size1.x / 2,
//            button.getPosition().y - size1.y / 2,
//            size1.x, size1.y);
//}

bool Button::Clicked(sf::RenderWindow& window, sf::Sound& soundClick, sf::Sound& soundRoll) {
    int currentFrame = clock.getElapsedTime().asMilliseconds() / 16;
    isClick = false;
    choose = false;

    if (container.contains(sf::Mouse::getPosition(window))) {
        button.setSize(size2);
        button.setOrigin(size2.x / 2, size2.y / 2);
        button.setTextureRect(
                sf::IntRect(nextBeginRect.x, nextBeginRect.y, nextSizeRect.x, nextSizeRect.y)
        );
        text.setCharacterSize(85);
        text.setPosition(button.getPosition().x, button.getPosition().y - 20);
        soundRoll.play();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentFrame > 20) {
            isClick = true;
            soundClick.play();
            clock.restart();
        }
    } else {
        button.setSize(size1);
        button.setOrigin(size1.x / 2, size1.y / 2);
        button.setTextureRect(
                sf::IntRect(beginRect.x, beginRect.y, sizeRect.x, sizeRect.y)
        );
        text.setCharacterSize(80);
        text.setPosition(button.getPosition().x, button.getPosition().y - 20);
        choose = false;
    }

    return isClick;
}
