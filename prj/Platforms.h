#ifndef PLATFORMS
#define PLATFORMS
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <random>
#include <ctime>
#include <iostream>

class Platforms
{
public:
	Platforms() = default;
	Platforms(const Platforms&) = default;
	Platforms(const sf::Vector2u &windowSize, const std::string& File,
           const int& X, const int& Y, const int& W, const int& H,
           const int& platformSkin);
	~Platforms() = default;

	void PlatformMover(const float &deltaTime, sf::Vector2f &pos) noexcept(false);
    static float RandCoordinates(const float &coord);

	sf::Sprite* GetPlatform();
    const sf::Vector2f * GetPlatformPos();

private:
	sf::RectangleShape platform;
	sf::Vector2u window;
    sf::Vector2u randCoord;
	std::vector<sf::RectangleShape> platformsList;
    sf::Sprite sprite;
};
#endif // PLATFORMS
