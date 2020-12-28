#ifndef COLLISION
#define COLLISION
#include <SFML/Graphics.hpp>
#include "FilesBank.h"

class Collision
{
public:
	Collision() = default;
	explicit Collision(int& score);
	Collision(const Collision&) = delete;
	~Collision() = default;

	bool CollisionCheck(
	        sf::RectangleShape &player, float &accY,
	        const std::vector<sf::RectangleShape> &platforms,
	        const float &scaleValue,
            sf::Sound &sound0, sf::Sound &sound1, sf::Sound &sound2
	        );
private:
    void Acceleration(
            float &accY, const sf::RectangleShape &platform,
            sf::Sound &sound0, sf::Sound &sound1, sf::Sound &sound2) const;

    const float speed = -20;
    int* totalScore {nullptr};
    bool isCollided = false;
};
#endif //COLLISION