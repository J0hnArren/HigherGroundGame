#include "Player.h"

Player::Player(const sf::Vector2u &windowSize, const std::string& File)
    : Player(windowSize, File, 17, 12, 47, 42, 0) {
    this->windowSize = windowSize;

    FilesBank::getInstance().AddTexture("player", File);
    sprite.setTexture(FilesBank::getInstance().singletonTextures["player"][0]);
    sprite.setTextureRect(sf::IntRect(17, 12, 47, 42));
    sprite.setPosition(windowSize.x * 2.3f / 5.f, windowSize.y * 4.f / 5.f);
}

Player::Player(
        const sf::Vector2u &windowSize,
        const std::string& File,
        const int& X, const int& Y,
        const int& W, const int& H,
        const int& playerSkin) {
    this->windowSize = windowSize;

    FilesBank::getInstance().AddTexture("player", File);
    sprite.setTexture(FilesBank::getInstance().singletonTextures["player"][playerSkin]);
    sprite.setTextureRect(sf::IntRect(X, Y, H, W));
    sprite.setPosition(windowSize.x * 2.3f / 5.f, windowSize.y * 4.f / 5.f);
}

void Player::Controls(float& deltaTime, sf::Vector2f& currPos) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        currPos.x -= deltaTime;
        sprite.setScale(-3, 3);
        sprite.setPosition(currPos.x + 147, currPos.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        currPos.x += deltaTime;
        sprite.setScale(3, 3);
        sprite.setOrigin(currPos.x - 147, currPos.y);
    }
}

void Player::Update(float& deltaTime, sf::Vector2f& currPos) {
    // Keyboard
    Controls(deltaTime, currPos);

    Jump(currPos.x, currPos.y);
    sprite.setPosition(currPos.x, currPos.y);

    // Checks player's position at the both borders of the map
    // left side
    if (currPos.x < -sprite.getTextureRect().width) {
        sprite.setPosition(windowSize.x + sprite.getTextureRect().width * 0.8f, currPos.y);
    }
    // right side
    else if (currPos.x > windowSize.x * 1.f + sprite.getTextureRect().width) {
        sprite.setPosition(-sprite.getTextureRect().width * 0.8f, currPos.y);
    }
}

void Player::Jump(float& x, float& y){
    accY += 0.5f; // acceleration
    std::cout << accY << std::endl;
    y += accY;
    if (y > windowSize.y - sprite.getTextureRect().width * 3.f){
        accY = -15; // high
    }
}

void Player::UpdatePlayerAnimation(int& fps, const int& X_, const int& Y_, const int& W_, const int& H_) {
    int spritePos = 0;
    //choose a correct part of sprite to make an animation
    if (fps > 70) { spritePos = 17; fps = 0; }
    else if (fps > 60) { spritePos = 116; }
    else if (fps > 50) { spritePos = 215; }
    else if (fps > 40) { spritePos = 315; }
    else if (fps > 30) { spritePos = 415; }
    else if (fps > 20) { spritePos = 516; }
    else if (fps > 10) { spritePos = 617; }
    else if (fps > 0) { spritePos = 717; }

    sprite.setTextureRect(sf::IntRect(spritePos, Y_, W_, H_));
}

sf::Sprite* Player::GetSprite() {
    return &sprite;
}

float* Player::GetAcceleration(){
    return &accY;
}