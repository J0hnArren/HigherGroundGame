#ifndef PLATFORMS
#define PLATFORMS
#include <iosfwd>
#include <vector>
#include <SFML/Graphics.hpp>

class Platforms
{
public:
	Platforms() = default;
	Platforms(const Platforms&) = default;
	Platforms(const sf::Vector2u& windowSize);
	~Platforms() = default;

	void PlatformGenerator(sf::RenderWindow& window);

	sf::RectangleShape* GetPlatform();

private:
	sf::RectangleShape platform;
	sf::Vector2u windowSize;
	std::vector<sf::RectangleShape> platformsList;
};
#endif // PLATFORMS
