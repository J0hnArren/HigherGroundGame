#ifndef COLLISION
#define COLLISION
#include <iostream>
#include <iosfwd>
#include <SFML/Graphics.hpp>
#include "FilesBank.h"

class Collision
{
public:
	Collision() = default;
	explicit Collision(const std::string &file1);
	Collision(const Collision&) = delete;
	~Collision() = default;

	bool CollisionCheck(
	        sf::RectangleShape &player, float &accY,
	        const std::vector<sf::RectangleShape> &platforms,
	        const float &scaleValue
	        );
private:
    void Acceleration(float &accY, const sf::RectangleShape &platform) const;

    const float speed = -20;
    std::string file;
    bool isCollided = false;
};
#endif //COLLISION