#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

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

private:
	void reset();

	sf::Vector2f		m_direction;
	sf::Vector2f		m_velocity;
	float				m_ttl;
	float				m_radius;
	int					m_damage;

	sf::Color			m_color;

	const int			MAX_TTL = 5;
	const int			MAX_SPEED = 12;

	void setSprite();
	void checkBorder();
};

#endif
