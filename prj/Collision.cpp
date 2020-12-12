#include "Collision.h"

void Collision::CollisionCheck(sf::Sprite &player, float &accY, const std::vector<sf::Sprite> &platforms) {
    const float playerX = player.getPosition().x;
    const float playerY = player.getPosition().y;

	for (const sf::Sprite &platform : platforms){
	    if ((playerX < platform.getPosition().x + 128) && (playerX + 126 > platform.getPosition().x) &&
                (playerY + 100 > platform.getPosition().y) && (playerY + 15 < platform.getPosition().y) && (accY > 0)){
            accY = -20;
	    }

	    if (playerY + 47 < 0){
	        player.setPosition(playerX, 0);
	    }
	}
}

