#include "Player.h"
#include "Collision.h"
#include "Platforms.h"
#include <SFML/Audio/Music.hpp>

int main()
{
    sf::RenderWindow window(
            sf::VideoMode::getFullscreenModes()[0],
            "Hello there!",
            sf::Style::Fullscreen
            );
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    //winSize size
    sf::Vector2u windowSize = window.getSize();

    //Music
    sf::Music music;
    music.openFromFile("src/audio/Track-01_-Assassin_s-Creed-2-OST-Jesper-Kyd-Earth.ogg");
    music.play();
    //std::size_t numberOfSongs = 1;

    //main hero sprite
    Player player1(windowSize, "hero.png", "hero1.png");
    player1.GetSprite()->setScale(sf::Vector2f(3, 3));

    //Platforms
    Platforms platforms(windowSize, "platforms.png"); // stone platform

    //background image
    sf::Sprite bgSprite;
    FilesBank::getInstance().AddTexture("bg", "bg0.png");
    FilesBank::getInstance().AddTexture("bg", "bg1.png");
    FilesBank::getInstance().AddTexture("bg", "bg2.png");
    bgSprite.setTexture(FilesBank::getInstance().singletonTextures["bg"][2]);
    sf::Vector2u bgSize = FilesBank::getInstance().singletonTextures["bg"][2].getSize();

    sf::Vector2f scale;
    scale.x = windowSize.x * 1.0f / bgSize.x,
    scale.y = windowSize.y * 1.0f / bgSize.y;
    bgSprite.setScale(scale);

    // Collision
    Collision collision;

    int fps = 0; // need for player animation update
    sf::Clock clock;
    sf::Vector2f currPos;
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asMicroseconds() / 750.f;
        //std::cout << deltaTime << "\n";
        clock.restart();

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        window.draw(bgSprite);
        ++fps;
        //std::cout << fps << "\n";

        // Platforms creating
        platforms.PlatformMover(deltaTime);
        for (const sf::Sprite &sp : *platforms.GetPlatform()) {
            window.draw(sp);
        }

        // Checking for movements
        currPos = player1.GetSprite()->sf::Transformable::getPosition();
        player1.Update(deltaTime, currPos);
        // Updating animation
        player1.UpdatePlayerAnimation(fps);
        window.draw(*player1.GetSprite());

        // Checking for collisions
        collision.CollisionCheck(*player1.GetSprite(), *player1.GetAcceleration(), *platforms.GetPlatform());

        window.display();
    }

    return 0;
}