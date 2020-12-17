﻿#include "Player.h"
#include "Collision.h"
#include "Platforms.h"
#include <sstream>

int main()
{
    sf::RenderWindow window(
            sf::VideoMode::getFullscreenModes()[0],
            "Hello there!",
            sf::Style::Fullscreen
            );
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // winSize size
    sf::Vector2u windowSize = window.getSize();
    std::cout << windowSize.x << " X " << windowSize.y;

    // Font & Text
    FilesBank::getInstance().AddFont("timer", "nightmare.otf");
    // Create a text which uses our font
    sf::Text timerText;
    timerText.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    timerText.setCharacterSize(50);
    timerText.setStyle(sf::Text::Regular);

    // Music
    sf::Music music;
    music.openFromFile("src/audio/Track_0" + std::to_string(3) + ".ogg");
    music.setVolume(30);
    //music.play();
    //const int numberOfSongs = 4;

    // Sounds
    FilesBank::getInstance().AddSound("jump", "hopper_jump.ogg"); // 0 - usual jump
    FilesBank::getInstance().AddSound("jump", "thud_jump.ogg"); // 1 - louder jump
    sf::Sound sound0(*FilesBank::getInstance().getSounds("jump", 0));
    sf::Sound sound1(*FilesBank::getInstance().getSounds("jump", 1));
    sound0.setVolume(40);

    //main hero sprite
    Player player1(windowSize, "hero.png", "hero1.png");
    const float scaleValue = 3;
    player1.GetSprite()->setScale(sf::Vector2f(scaleValue, scaleValue));

    //Platforms
    Platforms platforms(windowSize, "platforms.png"); // stone platform

    //background image
    sf::Sprite bgSprite;
    FilesBank::getInstance().AddFiles("bg", "bg0.png");
    FilesBank::getInstance().AddFiles("bg", "bg1.png");
    FilesBank::getInstance().AddFiles("bg", "bg2.png");
    bgSprite.setTexture(*FilesBank::getInstance().GetFile("bg", 2));
    sf::Vector2u bgSize = FilesBank::getInstance().GetFile("bg", 2)->getSize();

    sf::Vector2f scale;
    scale.x = windowSize.x * 1.0f / bgSize.x,
    scale.y = windowSize.y * 1.0f / bgSize.y;
    bgSprite.setScale(scale);

    // Collision
    Collision collision("hopper_jump");

    int fps = 0; // need for player animation update
    sf::Clock clock, gameTimeClock;
    sf::Vector2f currPos;
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asMicroseconds() / 750.f;
        int gameTime = int(gameTimeClock.getElapsedTime().asSeconds());
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

        // Platforms drawing
        if (player1.GetSprite()->getPosition().y < windowSize.y / 2.f) {
            player1.GetSprite()->setPosition(player1.GetSprite()->getPosition().x, windowSize.y / 2.f);
            platforms.PlatformMover(deltaTime, *player1.GetAcceleration(), gameTime);
        }
        for (const sf::RectangleShape &sp : *platforms.GetPlatform()) {
            window.draw(sp);
        }
        // Checking for movements
        currPos = player1.GetSprite()->sf::Transformable::getPosition();
        player1.Update(deltaTime, currPos);

        // Updating animation
        player1.UpdatePlayerAnimation(fps);
        window.draw(*player1.GetSprite());

        // Checking for collisions
        if (collision.CollisionCheck(
                *player1.GetSprite(), *player1.GetAcceleration(), *platforms.GetPlatform(), scaleValue
                )){
            sound0.play();
        }

        // Timer
        std::ostringstream gameTimeString;
        gameTimeString << gameTime;
        timerText.setString("Time: " + gameTimeString.str());
        timerText.setPosition(windowSize.x - timerText.getLocalBounds().width - 30, 20);
        window.draw(timerText);

        window.display();
    }

    return 0;
}