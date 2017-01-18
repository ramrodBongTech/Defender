#ifndef MISSILE_H
#define MISSILE_H

#include "GameEntity.h"

class Missile : public GameEntity {
public:
	Missile();
	~Missile();

	void update(float dt);
	void update(float dt, sf::Vector2f playerPos);
	void draw(sf::RenderWindow& window);

	int getRadius();
	int getDamage();

private:
	float				m_speed;
	float				m_ttl;
	float				m_radius;
	int					m_damage;
	sf::Vector2f		m_acceleration;
	sf::Vector2f		m_direction;
	float				m_orientation;
	sf::Vector2f		m_velocity;

	void updatePosition();
	void track(sf::Vector2f playerPos);
	void explode();
	void reset();
	void getNewOrientation();

	const float			MAX_TTL = 10.0f;
	const float			MAX_SPEED = 6.0f;
};

#endif