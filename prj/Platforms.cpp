#include "Platforms.h"

Platforms::Platforms(const sf::Vector2u &windowSize, const std::string& File) {
    winSize = windowSize;

    AddTextures(File, sprite, 0, 128, 192, 32, 0);
    for (std::size_t i = 0; i < 3; ++i) {
        sprite.setPosition(RandCoordinateX(winSize.x), RandCoordinateY(winSize.y));
        platformsList.push_back(sprite);
        std::cout << platformsList[i].getPosition().x << " " <<  platformsList[i].getPosition().y << "\n";
    }
}

void Platforms::AddTextures(const std::string& File, sf::Sprite &spr,
                            const int& X, const int& Y,
                            const int& W, const int& H,
                            const int& platformSkin){
    FilesBank::getInstance().AddTexture("platform", File);
    spr.setTexture(FilesBank::getInstance().singletonTextures["platform"][platformSkin]);
    spr.setTextureRect(sf::IntRect(X, Y, W, H));
}

float Platforms::RandCoordinateX(const float &coord){
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> urd(0, coord);
    return urd(gen);
}
float Platforms::RandCoordinateY(const float &coord){
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> urd(-coord / 4.f, coord);
    return urd(gen);
}

void Platforms::PlatformMover(const float &deltaTime) noexcept(false){
    for (sf::Sprite &platform : platformsList){
        platform.move(0, deltaTime / 15.f);

        if (platform.getPosition().y > winSize.y + 128.f) {
            platform.setPosition(RandCoordinateX(winSize.x), -128.f);
        }
    }
}

const std::vector<sf::Sprite>* Platforms::GetPlatform() const{
	return &platformsList;
}