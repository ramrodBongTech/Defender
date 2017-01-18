#ifndef BULLET_H
#define BULLET_H

#include "GameEntity.h"

class Bullet: public GameEntity {
public:
	Bullet();
	~Bullet();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	virtual void reset();

	float getWidth();
	float getHeight();
	int getDamage();

	void setDirection(sf::Vector2f direction);
	void setSpeed();
	void setIsPlayerBullet(bool ipb);

	bool isPlayerBullet();

protected:
	float				m_speed;
	float				m_ttl;
	int					m_maxTTL;
	float				m_width;
	float				m_height;
	int					m_damage;
	sf::Vector2f		m_direction;
	sf::Vector2f		m_velocity;
	float				m_orientation;

private:
	bool				m_isPlayerBullet;
	sf::Color			m_color;

	void setSprite();
	void checkBorder();
	void getNewOrientation();
};

#endif
