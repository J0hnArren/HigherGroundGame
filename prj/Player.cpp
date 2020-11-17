#include "Player.h"
#include "TextureBank.h"


Player::Player(const std::string& File) : Player(File, 17, 12, 47, 42, 0) {
    this->File = File;

    TextureBank::getInstance().AddTexture("player", this->File);
    sprite.setTexture(TextureBank::getInstance().singletonTextures["player"][0]);
    sprite.setTextureRect(sf::IntRect(17, 12, 47, 42));
}

Player::Player(const std::string& File, const int& X, const int& Y, const int& W, const int& H, const int& playerSkin) {
    this->File = File;
    x = X;
    y = Y;
    w = W;
    h = H;
    this->playerSkin = playerSkin;

    TextureBank::getInstance().AddTexture("player", this->File);
    sprite.setTexture(TextureBank::getInstance().singletonTextures["player"][this->playerSkin]);
    sprite.setTextureRect(sf::IntRect(17, 12, 47, 42));
    sprite.setTextureRect(sf::IntRect(x, y, h, w));
}

void Player::Update(float& deltaTime, const int& width, sf::Vector2f& currPos) {

    // Check posision on the map
    //left side
    if (currPos.x < -sprite.getTextureRect().width) {
        sprite.setPosition(width + sprite.getTextureRect().width * 0.8, currPos.y);
    }
    //right side
    else if (currPos.x > width + sprite.getTextureRect().width) {
        sprite.setPosition(-sprite.getTextureRect().width * 0.8, currPos.y);
    }

    //Keyboard
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sprite.setScale(-3, 3);
        sprite.move(-20, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.setScale(3, 3);
        sprite.move(20, 0);
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