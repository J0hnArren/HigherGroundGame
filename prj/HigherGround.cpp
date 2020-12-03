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
    player1.GetSprite()->setPosition(windowSize.x * 1.0f / 2 - 80, 830); //выводим спрайт в позицию x y

    //platforms.png
    Platforms platforms;

    //background image
    sf::Sprite bgSprite;
    TextureBank::getInstance().AddTexture("bg", "bg0.png");
    TextureBank::getInstance().AddTexture("bg", "bg1.png");
    bgSprite.setTexture(TextureBank::getInstance().singletonTextures["bg"][1]);
    sf::Vector2u bgSize = TextureBank::getInstance().singletonTextures["bg"][1].getSize();

    sf::Vector2f scale;
    scale.x = windowSize.x * 1.0 / bgSize.x,
    scale.y = windowSize.y * 1.0 / bgSize.y;
    bgSprite.setScale(scale);

    int fps = 0;
    sf::Clock clock;
    sf::Vector2f currPos;
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asMicroseconds() / 800;
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

        // Cheсking movements
        currPos = player1.GetSprite()->sf::Transformable::getPosition();
        player1.Update(deltaTime, windowSize.x, currPos);
        // Updating animation
        player1.UpdatePlayerAnimation(fps);
        window.draw(*player1.GetSprite());
        // Platforms creating
//        platform.PlatformGenerator(window);
//        window.draw(*platform.GetPlatform());
        window.display();
    }

    return 0;
}