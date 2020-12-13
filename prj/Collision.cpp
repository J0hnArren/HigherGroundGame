#include "Collision.h"

Collision::Collision(const std::string &file1) {
    file = file1;
}

bool Collision::CollisionCheck(
        sf::Sprite &player, float &accY, const std::vector<sf::Sprite> &platforms, const float &scaleValue) {
    isCollided = false;
    const float playerX = player.getPosition().x;
    const float playerY = player.getPosition().y;
	for (const sf::Sprite &platform : platforms){
	    if ((playerX < platform.getPosition().x + 192) && (playerX + 44 * scaleValue > platform.getPosition().x) &&
                (playerY + 40 * scaleValue > platform.getPosition().y) &&
                (playerY + 40 * scaleValue < platform.getPosition().y + 32) && (accY > 0)){
            accY = -20;
            isCollided = true;
	    }

	    if (playerY + 47 < 0){
	        player.setPosition(playerX, 0);
	    }
	}
    return isCollided;
}

void Collision::PlatformAcceleration(float& platformSpeed, const float &currPos, const float &winSize){
    if (currPos > winSize - (winSize / 3)){
        platformSpeed = 15;
    } else if (currPos < winSize - (winSize / 3)){
        platformSpeed -= 1;
    } else if (currPos > winSize - (winSize * 2 / 3)){
        platformSpeed -= 1;
    } else if (currPos > winSize / 8){
        platformSpeed -= 1;
    }
}