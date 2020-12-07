#include "Platforms.h"

Platforms::Platforms(
        const sf::Vector2u &windowSize,
        const std::string& File,
        const int& X, const int& Y,
        const int& W, const int& H,
        const int& platformSkin) {
    window = windowSize;

    TextureBank::getInstance().AddTexture("platform", File);
    sprite.setTexture(TextureBank::getInstance().singletonTextures["platform"][platformSkin]);
    sprite.setTextureRect(sf::IntRect(X, Y, W, H));
}

void Platforms::PlatformMover(const float &deltaTime) noexcept(false){
    sprite.move(0, deltaTime / 10.f);
}

sf::Sprite* Platforms::GetPlatform() {
	return &sprite;
}