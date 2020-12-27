#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>
#include <iosfwd>
#include "FilesBank.h"

class Player {
public:
    Player() = default;
    Player(const Player&) = default;
    Player(const sf::Vector2u &windowSize, const std::string& file_1, const std::string& file_2, int& score);
    Player(
            const sf::Vector2u &windowSize,
            const std::string& file_1, const std::string& file_2,
            const int& X, const int& Y,
            const int& W, const int& H,
            const int& playerSkin, int& score
            );
    ~Player() = default;

    void UpdatePlayerAnimation(int& fps);
    void Update(float& deltaTime, sf::Vector2f &currPos, int& gameTime, bool &AFK);

    sf::RectangleShape* GetSprite();
    float* GetAcceleration();
private:
    bool turnLeft = false; // did the sprite turn
    bool fine = false; // need to take away points for the AFK
    void Controls(float& deltaTime, sf::Vector2f& currPos, int& gameTime); //Keyboard
    void Jump(float& x, float& y);
    void Initialize(const std::string& file_1, const std::string& file_2);

    float accX = 0, accY = 0;
    int X = 0, Y = 0, W = 0, H = 0, skin = 0;
    int stayingTime = 0; // time you are doing nothing
    int* totalScore {nullptr};
    sf::RectangleShape sprite;
    sf::Vector2u winSize = {0, 0};
};
#endif
