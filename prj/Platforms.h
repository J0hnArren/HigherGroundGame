#ifndef PLATFORMS
#define PLATFORMS
#include <SFML/Graphics.hpp>
#include "FilesBank.h"

class Platforms
{
public:
	Platforms() = default;
	Platforms(const Platforms&) = default;
	Platforms(const sf::Vector2u &windowSize, const std::string& File, const int& X, const int& Y, const int& W, const int& H, const int& platformSkin);
	~Platforms() = default;

	void PlatformMover(const float &deltaTime) noexcept(false);

	sf::Sprite* GetPlatform();

private:
	sf::RectangleShape platform;
	sf::Vector2u window;
	std::vector<sf::RectangleShape> platformsList;
    sf::Sprite sprite;
};
#endif // PLATFORMS
