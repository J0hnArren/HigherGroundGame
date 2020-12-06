#include "Platforms.h"

Platforms::Platforms(
        const std::string& File,
        const int& X, const int& Y,
        const int& W, const int& H,
        const int& platformSkin) {
    TextureBank::getInstance().AddTexture("platform", File);
    sprite.setTexture(TextureBank::getInstance().singletonTextures["platform"][platformSkin]);
    sprite.setTextureRect(sf::IntRect(X, Y, W, H));
}

void Platforms::PlatformMover(sf::RenderWindow& window) noexcept(false){

}

sf::Sprite* Platforms::GetPlatform() {
	return &sprite;
}