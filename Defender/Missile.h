#ifndef MISSILE_H
#define MISSILE_H

#include "Bullet.h"
//#include "Player.h"

class Missile : public Bullet {
public:
	Missile();
	~Missile();

	void update(float dt);
	void update(float dt, sf::Vector2f* playerPos);
	void draw(sf::RenderWindow& window);

	void reset();

private:
	sf::Vector2f		m_acceleration;

	void updatePosition();
	void track(sf::Vector2f* playerPos);
	void explode();
	void getNewOrientation();

	const float			MAX_SPEED = 6.0f;
};

#endif