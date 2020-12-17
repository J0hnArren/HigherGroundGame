#ifndef PLATFORMS
#define PLATFORMS
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <random>
#include <iostream>
#include <iterator>
#include <ctime>

class Platforms
{
public:
	Platforms() = default;
	Platforms(const Platforms&) = delete;
	Platforms(const sf::Vector2u &windowSize, const std::string& File);
	~Platforms() = default;

	void PlatformMover(const float &deltaTime, const float &accY) noexcept(false);
    float RandCoordinateX(const float &coord, const float &prevCoord = 0);
    float RandCoordinateY(const float &coord, const float &prevCoord = 0);
    bool RandBool();


    const std::vector<sf::Sprite>* GetPlatform() const;

private:
    static void AddTextures(const std::string& File, sf::Sprite &spr,
                     const int& X, const int& Y, const int& W, const int& H,
                     const int& platformSkin
                     );

    std::random_device rd;
    sf::Sprite sprite;
	sf::Vector2u winSize;
	std::vector<std::vector<bool>> zones;
    std::vector<std::tuple<float, float>> platformsCoords;
	std::vector<sf::Sprite> platformsList;
    std::vector<sf::Sprite>::iterator it;
	const int numPlatforms = 20; // maximum number of existing platforms
	unsigned int lineX = 0, lineY = 0, moverCount = 0;
	int W = 0, H = 0;
    sf::Vector2f startPos;
    float coordX = 0, p1 = 0;
    float coordY = 0, p2 = 0;
};
#endif // PLATFORMS
