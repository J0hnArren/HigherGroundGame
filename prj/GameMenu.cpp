#include "GameMenu.h"

GameMenu::GameMenu(const sf::Vector2u &windowSize) {
    winSize = windowSize;

    FilesBank::getInstance().AddFiles("button", "magicButtons.png");
    std::string nameOfButtons[] = { "Play", "Records", "Exit" };

    for (const std::string &nameOfButton : nameOfButtons) {
    buttons.emplace_back(
            *FilesBank::getInstance().GetFile("button", 0),
            sf::Vector2f(winSize.x / 6.45f, winSize.y / 9.36f),
            sf::Vector2f(78, 220),
            sf::Vector2f(445, 173),
            sf::Vector2f(winSize.x / 3.7f, winSize.y / 3.3f),
            sf::Vector2f(678, 151),
            sf::Vector2f(519, 326),
            nameOfButton,
            *FilesBank::getInstance().getFonts("timer", 0)
            );
    }

    menuSquare.setPosition(sf::Vector2f(winSize.x * 0.25f, 0));
    menuSquare.setSize(sf::Vector2f(winSize.x * 0.5f, winSize.y));
    menuSquare.setFillColor(sf::Color(20,20,20, 180));

    text.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    text.setString("Higher Ground");
    text.setCharacterSize(120);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(menuSquare.getGlobalBounds().width, menuSquare.getGlobalBounds().height * 0.05f);
}

bool GameMenu::Menu(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player) {
    bool MainMenu = true;
    int currFrame = 0, buttonNumber = -1;

    float interval = 0;
    for (Button &b : buttons) {
        b.setPos(sf::Vector2f(winSize.x / 2.f, winSize.y / 4.f + interval));
        interval += 200;
    }
    sf::Music track3;
    track3.openFromFile("src/audio/Track_03.ogg");
    track3.setVolume(20);
    track3.play();
    track3.setLoop(true);

    sf::Sound soundRoll(*FilesBank::getInstance().getSounds("button", 0));
    sf::Sound soundClick(*FilesBank::getInstance().getSounds("button", 1));
    soundClick.setVolume(20);
    soundRoll.setVolume(10);

    //player.GetSprite()->setPosition()

    clock.restart();
    int fps = 0;
    while (MainMenu) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        window.clear();

        window.draw(bgImage);
        window.draw(menuSquare);
        window.draw(text);
        ++fps;
        player.UpdatePlayerAnimation(fps);
        window.draw(*player.GetSprite());

        currFrame = clock.getElapsedTime().asMilliseconds() / 16;
        if (currFrame > 0) {
            for (std::ptrdiff_t i = 0; i < buttons.size(); ++i) {
                window.draw(buttons[i].button);
                window.draw(buttons[i].text);

                if (buttons[i].Clicked(window, soundClick, soundRoll)) {
                    buttonNumber = i;
                }
            }
                window.display();
                switch (buttonNumber) {
                    case -1:
                        continue;
                    case 0:
                        MainMenu = false;
                        track3.stop();
                        break;
                    case 1:
                        //Records(window);
                        clock.restart();
                        break;
                    case 2:
                        MainMenu = false;
                        exit = true;
                        Exit();
                        break;
                    default:
                        window.close();
                        return MainMenu;

                    }
        }
    }
    return MainMenu;
}

bool GameMenu::Exit() {
    return !exit;
}