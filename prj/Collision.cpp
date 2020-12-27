#include "Collision.h"

Collision::Collision(const std::string &file1) {
    file = file1;
}

bool Collision::CollisionCheck(
        sf::RectangleShape &player, float &accY,
        const std::vector<sf::RectangleShape> &platforms,
        const float &scaleValue) {
    isCollided = false;
    const float playerX = player.getPosition().x;
    const float playerY = player.getPosition().y;
    const int swordSize = 17;
    // if player's texture turn to left side
    if (player.getTextureRect().left % 10 == 8){
        for (const sf::RectangleShape &platform : platforms){
            if ((playerX < platform.getPosition().x + 192)
            && (playerX + (44 - swordSize) * scaleValue  > platform.getPosition().x)
            && (playerY + 40 * scaleValue > platform.getPosition().y)
            && (playerY + 40 * scaleValue < platform.getPosition().y + 32) && (accY > 0)){
                Acceleration(accY, platform);
                isCollided = true;
            }
        }
        // right side
    } else {
        for (const sf::RectangleShape &platform : platforms){
            if ((playerX + swordSize * scaleValue < platform.getPosition().x + 192)
             && (playerX + 44 * scaleValue > platform.getPosition().x)
             && (playerY + 40 * scaleValue > platform.getPosition().y)
             && (playerY + 40 * scaleValue < platform.getPosition().y + 32) && (accY > 0)){
                Acceleration(accY, platform);
                isCollided = true;
            }
        }
    }
    if (playerY + 47 < 0){
        player.setPosition(playerX, 0);
    }

    return isCollided;
}

void Collision::Acceleration(float &accY, const sf::RectangleShape &platform) const{
    if (platform.getTextureRect().top == 128){
        accY = speed;
    } else if (platform.getTextureRect().top == 64){
        accY = speed * 2.f;
    } else if (platform.getTextureRect().top == 160){
        accY = speed * 3.f;
    } else {
        accY = speed / 20.f;
    }
}