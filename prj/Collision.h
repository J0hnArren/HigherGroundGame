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
	Collision(const std::string &file1);
	Collision(const Collision&) = delete;
	~Collision() = default;

	bool CollisionCheck(
	        sf::Sprite &player, float &accY, const std::vector<sf::Sprite> &platforms, const float &scaleValue
	        );
	void PlatformAcceleration(float& platformSpeed, const float &currPos, const float &winSize);
private:
    std::string file;
    bool isCollided = false;
};
#endif //COLLISION