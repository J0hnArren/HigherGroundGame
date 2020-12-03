#include "Platforms.h"

Platforms::Platforms(
        const std::string& File,
        const int& X, const int& Y,
        const int& W, const int& H,
        const int& platformSkin) {

}

void Platforms::PlatformGenerator(sf::RenderWindow& window) {
	platform.setFillColor(sf::Color::Green);
}

sf::RectangleShape* Platforms::GetPlatform() {
	return &platform;
}