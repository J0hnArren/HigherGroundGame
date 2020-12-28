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
	Platforms(const sf::Vector2u &windowSize, const std::string& file);
	~Platforms() = default;

	void PlatformMover(const float &deltaTime, const float &accY, const int &currTime) noexcept(false);
    float RandCoordinateX(const float &coord, const float &prevCoord = 0);
    float RandCoordinateY(const float &coord, const float &prevCoord = 0);
    int RandPlatform(const int& capacity);
    void Respawn();

    const std::vector<sf::RectangleShape>* GetPlatform() const;

private:
    void AddTextures(sf::RectangleShape &spr, const int& X, const int& Y, const int& platformSkin) const;
    void StartGeneration();

    std::random_device rd;
    sf::RectangleShape sprite;
	sf::Vector2u winSize;
    std::vector<std::tuple<float, float>> platformsCoords;
	std::vector<sf::RectangleShape> platformsList;
    std::vector<sf::RectangleShape>::iterator it;
	unsigned int lineX = 0, lineY = 0, moverCount = 0; // lineX * lineY = maximum number of existing platforms
	int W = 0, cW = 0, H = 0, cH = 0;
    sf::Vector2f startPos;
    float coordX = 0, p1 = 0;
    float coordY = 0, p2 = 0;
    int randPlatform = 0, timeToHide = 10;
    std::vector<int> randLines;

    std::string File;
};
#endif // PLATFORMS
