#include "Platforms.h"

Platforms::Platforms(const sf::Vector2u &windowSize, const std::string& File) {
    winSize = windowSize;
    W = 192, H = 32;
    lineX = winSize.x / (W * 2);
    lineY = winSize.y / (H * 6);

    AddTextures(File, sprite, 0, 128, W, H, 0);
    // The remainder that is cut off from the screen when we select the spawn areas of the platform
    startPos = sf::Vector2f(float(winSize.x % (W * 2)) / 2.f, float(H + winSize.y % (H * 6)));
    //These are the areas of spawn platforms, taking into account the halves cut off from the remainder on both sides,
    // and the previous areas needed to create a random range
    coordX = startPos.x + float(W * 2), p1 = startPos.x;
    coordY = 0, p2 = - float(H * 6);
    for (int i = 0; i < lineX * (lineY + 1); ++i) {
        platformsCoords.emplace_back(RandCoordinateX(coordX, p1), RandCoordinateY(coordY, p2));
        p1 = coordX; coordX += float(W * 2);
        if ((i + 1) % lineX == 0) {
            p1 = startPos.x, coordX = float(W * 2);
            p2 = coordY, coordY += float(H * 6);
        }
        sprite.setPosition(std::get<0>(platformsCoords[i]), std::get<1>(platformsCoords[i]));
        platformsList.push_back(sprite);
    }
    coordX = startPos.x + float(W * 2), p1 = startPos.x;
    coordY = 0, p2 = -float(H * 6);
}

void Platforms::AddTextures(const std::string& File, sf::RectangleShape &spr,
                            const int& X, const int& Y,
                            const int& W, const int& H,
                            const int& platformSkin) const{
    FilesBank::getInstance().AddFiles("platform", File);
    spr.setSize(sf::Vector2f(winSize.x / 10.f, winSize.y / 33.75f));
    spr.setTexture(FilesBank::getInstance().GetFile("platform", platformSkin));
    spr.setTextureRect(sf::IntRect(X, Y, W, H));
}

bool Platforms::RandBool() {
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> urd(0, 1);
    return urd(gen);
}

float Platforms::RandCoordinateX(const float &coord, const float &prevCoord){
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> urd(prevCoord, coord - sprite.getTextureRect().width);
    return urd(gen);
}
float Platforms::RandCoordinateY(const float &coord, const float &prevCoord){
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> urd(prevCoord, coord);
    return urd(gen);
}

void Platforms::PlatformMover(const float &deltaTime, const float &accY, const float &currTime) noexcept(false){
    if (moverCount >= lineX){
        coordX = startPos.x + float(W * 2), p1 = startPos.x;
        coordY = 0, p2 = -float(H * 6);
        moverCount = 0;
    }
    for (sf::RectangleShape &platform : platformsList){
        platform.move(0, -accY);

        if (platform.getPosition().y > winSize.y) {
            std::rotate(platformsCoords.rbegin(), platformsCoords.rbegin() + 1, platformsCoords.rend());
            platformsCoords[0] = std::tuple(RandCoordinateX(coordX, p1), RandCoordinateY(coordY, p2));
            platform.setPosition(std::get<0>(platformsCoords[0]), std::get<1>(platformsCoords[0]));
            p1 = coordX, coordX += float(W * 2);
            p2 = coordY - startPos.y, coordY -= startPos.y;
            ++moverCount;
        }
    }
}

const std::vector<sf::RectangleShape>* Platforms::GetPlatform() const{
	return &platformsList;
}