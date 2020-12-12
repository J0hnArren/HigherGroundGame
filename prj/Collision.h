#ifndef COLLISION
#define COLLISION
#include <iosfwd>
#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision() = default;
	Collision(const Collision&) = default;
	~Collision() = default;

	void CollisionCheck(sf::Sprite &player, float &accY, const std::vector<sf::Sprite> &platforms);
private:

};
#endif //COLLISION