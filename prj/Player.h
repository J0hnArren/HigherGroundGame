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
    Player(const sf::Vector2u &windowSize, const std::string& File);
    Player(
            const sf::Vector2u &windowSize,
            const std::string& File,
            const int& X, const int& Y,
            const int& W, const int& H,
            const int& playerSkin
            );
    ~Player() = default;

    void UpdatePlayerAnimation(int& fps, const int& X_ = 17, const int& Y_ = 12, const int& W_ = 47, const int& H_ = 42);
    void Update(float& deltaTime, sf::Vector2f& currPos);
    void Jump(float& x, float& y);

    sf::Sprite* GetSprite();
    float* GetAcceleration();
private:
    void Controls(float& deltaTime, sf::Vector2f& currPos); //Keyboard

    float accX = 0, accY = 0;
    sf::Sprite sprite;
    sf::Vector2u windowSize = {0, 0};
};
#endif
