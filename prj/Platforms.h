#ifndef PLATFORMS
#define PLATFORMS
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <random>
#include <iostream>

class Platforms
{
public:
	Platforms() = default;
	Platforms(const Platforms&) = delete;
	Platforms(const sf::Vector2u &windowSize, const std::string& File);
	~Platforms() = default;

	void PlatformMover(const float &deltaTime, const float &accY) noexcept(false);
    float RandCoordinateX(const float &coord);
    float RandCoordinateY(const float &coord);

    const std::vector<sf::Sprite>* GetPlatform() const;
    float* GetPlatformSpeed();

private:
    static void AddTextures(const std::string& File, sf::Sprite &spr,
                     const int& X, const int& Y, const int& W, const int& H,
                     const int& platformSkin
                     );

    std::random_device rd;
    sf::Sprite sprite;
	sf::Vector2u winSize;
	std::vector<sf::Sprite> platformsList;
	const int numPlatforms = 25;
	float platformSpeed = 1.f;
};
#endif // PLATFORMS
