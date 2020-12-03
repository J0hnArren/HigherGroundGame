#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>
#include <iosfwd>
#include "TextureBank.h"

class Player {
public:
    Player() = default;
    Player(const Player&) = default;
    Player(const std::string& File);
    Player(const std::string& File, const int& X, const int& Y, const int& W, const int& H, const int& playerSkin);
    ~Player() = default;

    void UpdatePlayerAnimation(int& fps, const int& X_ = 17, const int& Y_ = 12, const int& W_ = 47, const int& H_ = 42);
    void Update(float& deltaTime, const int& width, sf::Vector2f& currPos);

    sf::Sprite* GetSprite();
private:
    int playerSkin = 0;
    std::string File;
    sf::Sprite sprite;
};
#endif
