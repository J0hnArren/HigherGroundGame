#include "Player.h"

Player::Player(const sf::Vector2u &windowSize, const std::string& file_1, const std::string& file_2)
    : Player(windowSize, file_1, file_2, 17, 12, 44, 40, 0) {
    winSize = windowSize;

    Initialize(file_1, file_2);
}

Player::Player(
        const sf::Vector2u &windowSize,
        const std::string& file_1, const std::string& file_2,
        const int& x, const int& y,
        const int& w, const int& h,
        const int& playerSkin) {
    winSize = windowSize;
    X = x; Y = y; W = w; H = h; skin = playerSkin;

    Initialize(file_1, file_2);
}

void Player::Initialize(const std::string& file_1, const std::string& file_2){
    FilesBank::getInstance().AddFiles("player", file_1);
    FilesBank::getInstance().AddFiles("player", file_2);
    sprite.setTexture(*FilesBank::getInstance().GetFile("player", skin));
    sprite.setTextureRect(sf::IntRect(X, Y, H, W));
    sprite.setPosition(winSize.x * 2.3f / 5.f, winSize.y * 4.f / 5.f);
}


void Player::Controls(float& deltaTime, sf::Vector2f& currPos) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        currPos.x -= deltaTime;
        turnLeft = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        currPos.x += deltaTime;
        turnLeft = false;
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
        sprite.setPosition(winSize.x + sprite.getTextureRect().width * 0.8f, currPos.y);
    }
    // right side
    else if (currPos.x > winSize.x * 1.f + sprite.getTextureRect().width) {
        sprite.setPosition(-sprite.getTextureRect().width * 0.8f, currPos.y);
    }
}

void Player::Jump(float& x, float& y){
    accY += 0.5f; // acceleration
    //std::cout << accY << std::endl;
    y += accY;
    if (y > winSize.y - sprite.getTextureRect().width * 3.f){
        accY = -20; // high
    }
}

void Player::UpdatePlayerAnimation(int& fps) {
    int spritePos = 0;
    if (turnLeft) {
        sprite.setTexture(*FilesBank::getInstance().GetFile("player", skin + 1));
        //choose a correct part of sprite to make an animation
        if (fps > 70) { spritePos = 938; fps = 0; }
        else if (fps > 60) { spritePos = 838; }
        else if (fps > 50) { spritePos = 738; }
        else if (fps > 40) { spritePos = 638; }
        else if (fps > 30) { spritePos = 538; }
        else if (fps > 20) { spritePos = 438; }
        else if (fps > 10) { spritePos = 338; }
        else if (fps > 0) { spritePos = 238; }

        sprite.setTextureRect(sf::IntRect(spritePos, Y, W, H));
    } else{
        sprite.setTexture(*FilesBank::getInstance().GetFile("player", skin));
        if (fps > 70) { spritePos = 17; fps = 0; }
        else if (fps > 60) { spritePos = 116; }
        else if (fps > 50) { spritePos = 215; }
        else if (fps > 40) { spritePos = 315; }
        else if (fps > 30) { spritePos = 415; }
        else if (fps > 20) { spritePos = 516; }
        else if (fps > 10) { spritePos = 617; }
        else if (fps > 0) { spritePos = 717; }

        sprite.setTextureRect(sf::IntRect(spritePos, Y, W, H));
    }
}

sf::Sprite* Player::GetSprite() {
    return &sprite;
}

float* Player::GetAcceleration(){
    return &accY;
}