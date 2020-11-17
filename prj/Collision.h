#ifndef COLLISION
#define COLLISION
#include <iosfwd>
#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision() = default;
	Collision(const Collision&) = default;
	Collision(sf::RectangleShape& body);
	~Collision() = default;

	bool CollisionCheck(Collision& other, sf::Vector2f& direction, float push);
	sf::Vector2f GetPosition();
	sf::Vector2f GetHalfSize();
private:
	sf::RectangleShape body;
};
#endif //COLLISION