#include "Collision.h"

Collision::Collision(sf::RectangleShape& body) {
	this->body = body;
}

//bool Collision::CollisionCheck(Collision& other, sf::Vector2f& direction, float push) {
//	return true;
//}

sf::Vector2f Collision::GetPosition() {
	return body.getPosition();
}
sf::Vector2f  Collision::GetHalfSize() {
	return body.getSize() / 2.0f;
}
