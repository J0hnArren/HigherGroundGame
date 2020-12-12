#include "Collision.h"

void Collision::CollisionCheck(sf::Sprite &player, float &accY, const std::vector<sf::Sprite> &platforms) {
    const float playerX = player.getPosition().x;
    const float playerY = player.getPosition().y;

	for (const sf::Sprite &platform : platforms){
	    if ((playerX < platform.getPosition().x + 192) && (playerX + 42 > platform.getPosition().x) &&
                (playerY + 47 > platform.getPosition().y) && (playerY + 47 < platform.getPosition().y + 32) && (accY > 0)){
            accY = -15;
	    }

	    if (playerY + 47 < 0){
	        player.setPosition(playerX, 0);
	    }
	}
}

