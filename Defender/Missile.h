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
	float				m_explosionTimer;
	bool				m_isExploding;
	sf::Sprite			m_explosionSprite;

	void updatePosition();
	void track(sf::Vector2f* playerPos);
	void explode(float dt);
	void getNewOrientation();

	const int			MAX_SPEED = 6;
	const double		MAX_EXPLOSION_TIME = 0.6;
};

#endif