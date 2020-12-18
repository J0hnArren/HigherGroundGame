#include "GameMenu.h"

GameMenu::GameMenu(const sf::Vector2u &windowSize) {
    FilesBank::getInstance().AddFiles("button", "magicButton.png");
    button_1 = Button(FilesBank::getInstance().GetFile("button", 0),
                      sf::Vector2f(winSize.x / 4.3f, winSize.y / 6.24f),
                      sf::Vector2f(winSize.x / 3.7f, winSize.y / 3.3f),
                      "Play",

                      );
    //FilesBank::getInstance().AddFiles("button", "mine.png");
    winSize = windowSize;
    menuSquare.setPosition(sf::Vector2f(winSize.x * 0.25f, 0));
    menuSquare.setSize(sf::Vector2f(winSize.x * 0.5f, winSize.y));
    menuSquare.setFillColor(sf::Color(20,20,20, 180));

    button1.setSize(sf::Vector2f(winSize.x / 3.7f, winSize.y / 3.3f)); // 519x327
    button1.setOrigin(sf::Vector2f(button1.getLocalBounds().width / 2, button1.getLocalBounds().height / 2));
    button1.setPosition(sf::Vector2f(winSize.x / 2.f, winSize.y / 3.f));
    button1.setTexture(FilesBank::getInstance().GetFile("button", 0));
}

bool GameMenu::Menu(sf::RenderWindow &window, const sf::Sprite &bgImage) {
    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        window.clear();

        window.draw(bgImage);
        window.draw(menuSquare);
        window.draw(button1);

        window.display();
    }

    return true;
}