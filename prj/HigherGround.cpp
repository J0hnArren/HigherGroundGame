#include "Player.h"
#include "Collision.h"
#include "Platforms.h"
#include "GameMenu.h"
#include <sstream>

void GameProcess(sf::RenderWindow &window, Player &player1, Collision &collision,
                 Platforms &platforms, sf::Text &timerText, const sf::Vector2u &windowSize,
                 sf::Sprite &bgSprite, sf::Sound &sound0, const float &scaleValue, GameMenu &gameMenu);

int main()
{
    sf::RenderWindow window(
            sf::VideoMode::getFullscreenModes()[0],
            "Hello there!",
            sf::Style::Fullscreen
            );
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);

    // winSize size
    sf::Vector2u windowSize = window.getSize();
    std::cout << windowSize.x << " X " << windowSize.y;

    // Music
    sf::Music track1, track2, track3, track4;
    track1.openFromFile("src/audio/Track_01.ogg");
//    track2.openFromFile("src/audio/Track_02.ogg");
//    track3.openFromFile("src/audio/Track_03.ogg");
//    track4.openFromFile("src/audio/Track_04.ogg");
    //track1.play();
    track1.setLoop(true);

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

    // Font & Text
    FilesBank::getInstance().AddFont("timer", "nightmare.otf");
    // Create a text which uses our font
    sf::Text timerText;
    timerText.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    timerText.setCharacterSize(50);
    timerText.setStyle(sf::Text::Regular);

    // Sounds
    FilesBank::getInstance().AddSound("jump", "hopper_jump.ogg"); // 0 - usual jump
    FilesBank::getInstance().AddSound("jump", "thud_jump.ogg"); // 1 - louder jump
    FilesBank::getInstance().AddSound("button", "ui_button_confirm.wav"); // 0 - rolling buttons
    FilesBank::getInstance().AddSound("button", "button.ogg"); // 1 - click
    sf::Sound sound0(*FilesBank::getInstance().getSounds("jump", 0));
    sf::Sound sound1(*FilesBank::getInstance().getSounds("jump", 1));
    sound0.setVolume(40);

    //main hero sprite
    Player player1(windowSize, "hero.png", "hero1.png");
    const float scaleValue = 3;
    player1.GetSprite()->setScale(sf::Vector2f(scaleValue, scaleValue));

    // Menu
    GameMenu gameMenu(windowSize);

    //Platforms
    Platforms platforms(windowSize, "platforms.png"); // stone platform

    // Collision
    Collision collision("hopper_jump");

    while (gameMenu.Exit(window)){
        gameMenu.Menu(window, bgSprite, player1);
        GameProcess(window, player1, collision,platforms,
                    timerText, windowSize,bgSprite, sound0, scaleValue, gameMenu);
        platforms.Respawn();
        player1.GetSprite()->setPosition(windowSize.x * 2.3f / 5.f, windowSize.y * 4.f / 5.f);
    }

    return 0;
}

void GameProcess(sf::RenderWindow &window, Player &player1, Collision &collision,
                 Platforms &platforms, sf::Text &timerText, const sf::Vector2u &windowSize,
                 sf::Sprite &bgSprite, sf::Sound &sound0, const float &scaleValue, GameMenu &gameMenu){
    // Music
    sf::Music track4;
    track4.openFromFile("src/audio/Track_04.ogg");
    track4.play();
    track4.setLoop(true);

    int fps = 0, gameTime = 0, pauseTime = 0; // fps need for player animation update and total time in the game/pause
    sf::Clock clock, gameTimeClock;
    sf::Vector2f currPos;
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asMicroseconds() / 750.f;
        clock.restart();
        gameTime = int(gameTimeClock.getElapsedTime().asSeconds()) - pauseTime;

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        window.draw(bgSprite);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
            track4.pause();
            if (gameMenu.Pause(window, bgSprite, platforms, player1, pauseTime)){
                gameTimeClock.restart();
                return;
            }
            track4.play();
        } else {
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
        }

        window.display();
    }
}