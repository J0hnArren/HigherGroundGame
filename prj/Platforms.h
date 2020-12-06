#ifndef PLATFORMS
#define PLATFORMS
#include <SFML/Graphics.hpp>
#include "TextureBank.h"

class Platforms
{
public:
	Platforms() = default;
	Platforms(const Platforms&) = default;
	Platforms(const std::string& File, const int& X, const int& Y, const int& W, const int& H, const int& platformSkin);
	~Platforms() = default;

	void PlatformMover(sf::RenderWindow& window) noexcept(false);

	sf::Sprite* GetPlatform();

private:
	sf::RectangleShape platform;
	sf::Vector2u windowSize;
	std::vector<sf::RectangleShape> platformsList;
    sf::Sprite sprite;
};
#endif // PLATFORMS
