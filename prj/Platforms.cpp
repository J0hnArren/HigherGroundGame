#include "Platforms.h"

Platforms::Platforms(const sf::Vector2u& windowSize) {
	this->windowSize = windowSize;
	platform.setPosition(sf::Vector2f(1000, 900));
}

void Platforms::PlatformGenerator(sf::RenderWindow& window) {
	platform.setFillColor(sf::Color::Green);
}

sf::RectangleShape* Platforms::GetPlatform() {
	return &platform;
}