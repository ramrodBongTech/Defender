#ifndef BULLET_H
#define BULLET_H

#include "GameEntity.h"

class Bullet: public GameEntity {
public:
	Bullet();
	~Bullet();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	int getRadius();
	int getDamage();

	void setDirection(sf::Vector2f direction);
	void setSpeed();
	void setIsPlayerBullet(bool ipb);

	bool isplayerBullet();

private:
	float				m_ttl;
	float				m_radius;
	int					m_damage;
	sf::Vector2f		m_direction;
	sf::Vector2f		m_velocity;
	float				m_orientation;
	bool				m_isPlayerBullet;

	sf::Color			m_color;

	void reset();
	void setSprite();
	void checkBorder();
	void getNewOrientation();

	const int			MAX_TTL = 5;
	const int			MAX_SPEED = 12;
};

#endif
