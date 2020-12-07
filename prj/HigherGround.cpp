#include "Player.h"
#include "TextureBank.h"
#include "Collision.h"
#include "Platforms.h"

int main()
{
    sf::RenderWindow window(
            sf::VideoMode::getFullscreenModes()[0],
            "Hello there!",
            sf::Style::Fullscreen
            );
    window.setVerticalSyncEnabled(true);

    //window size
    sf::Vector2u windowSize = window.getSize();

    //main hero sprite
    Player player1("hero.png");
    player1.GetSprite()->setScale(sf::Vector2f(3, 3));
    player1.GetSprite()->setPosition(windowSize.x * 1.f / 2 - 80, 830); //выводим спрайт в позицию x y

    //Platforms
    Platforms platforms(windowSize, "platforms.png", 0, 128, 192, 32, 0); // first stone platform
    platforms.GetPlatform()->setPosition(windowSize.x * 1.f / 2 - 80, 500);

    //background image
    sf::Sprite bgSprite;
    TextureBank::getInstance().AddTexture("bg", "bg0.png");
    TextureBank::getInstance().AddTexture("bg", "bg1.png");
    TextureBank::getInstance().AddTexture("bg", "bg2.png");
    bgSprite.setTexture(TextureBank::getInstance().singletonTextures["bg"][2]);
    sf::Vector2u bgSize = TextureBank::getInstance().singletonTextures["bg"][2].getSize();

    sf::Vector2f scale;
    scale.x = windowSize.x * 1.0f / bgSize.x,
    scale.y = windowSize.y * 1.0f / bgSize.y;
    bgSprite.setScale(scale);

    int fps = 0; // need for player animation update
    sf::Clock clock;
    sf::Vector2f currPos;
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asMicroseconds() / 750;
        //std::cout << deltaTime << "\n";
        clock.restart();


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        window.draw(bgSprite);
        ++fps;
        //std::cout << fps << "\n";

        // Cheсks movements
        currPos = player1.GetSprite()->sf::Transformable::getPosition();
        player1.Update(deltaTime, windowSize.x, currPos);
        // Updating animation
        player1.UpdatePlayerAnimation(fps);
        window.draw(*player1.GetSprite());
        // Platforms creating
        platforms.PlatformMover(deltaTime);
        window.draw(*platforms.GetPlatform());

        window.display();
    }

    return 0;
}