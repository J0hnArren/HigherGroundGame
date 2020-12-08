#include "Platforms.h"

Platforms::Platforms(
        const sf::Vector2u &windowSize,
        const std::string& File,
        const int& X, const int& Y,
        const int& W, const int& H,
        const int& platformSkin) {
    window = windowSize;

    FilesBank::getInstance().AddTexture("platform", File);
    sprite.setTexture(FilesBank::getInstance().singletonTextures["platform"][platformSkin]);
    sprite.setTextureRect(sf::IntRect(X, Y, W, H));

    sprite.setPosition(RandCoordinates(window.x), RandCoordinates(window.y / 4.f));
}

float Platforms::RandCoordinates(const float &coord){
    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<float> uid(0, coord);
    return uid(gen);
}

void Platforms::PlatformMover(const float &deltaTime, sf::Vector2f &pos) noexcept(false){
    sprite.move(0, deltaTime / 15.f);

    if (pos.y > window.y + 128.f){
        sprite.setPosition(RandCoordinates(window.x), - 128.f);
    }
}

sf::Sprite* Platforms::GetPlatform() {
	return &sprite;
}

const sf::Vector2f * Platforms::GetPlatformPos() {
    return &sprite.getPosition();
}