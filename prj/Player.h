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
    Player(const sf::Vector2u &windowSize, const std::string& file_1, const std::string& file_2);
    Player(
            const sf::Vector2u &windowSize,
            const std::string& file_1, const std::string& file_2,
            const int& X, const int& Y,
            const int& W, const int& H,
            const int& playerSkin
            );
    ~Player() = default;

    void UpdatePlayerAnimation(int& fps);
    void Update(float& deltaTime, sf::Vector2f& currPos);

    sf::Sprite* GetSprite();
    float* GetAcceleration();
private:
    bool turnLeft = false;
    void Controls(float& deltaTime, sf::Vector2f& currPos); //Keyboard
    void Jump(float& x, float& y);

    float accX = 0, accY = 0;
    int X = 0, Y = 0, W = 0, H = 0, skin = 0;
    sf::Sprite sprite;
    sf::Vector2u winSize = {0, 0};
};
#endif
