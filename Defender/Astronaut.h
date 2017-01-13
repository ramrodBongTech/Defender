#ifndef ASTRONAUT_H
#define ASTRONAUT_h

#include "stdafx.h"
#include "GameEntity.h"

class Astronaut : public GameEntity 
{
public:
	Astronaut();
	Astronaut(sf::Vector2f position, int direction);
	~Astronaut();

	void update(float dt);
	void draw(sf::RenderWindow& window);
	

private:
	void Wander();
	void Evade();
	void WrapAround();

	float	m_velocity;
	float	m_direction;
	float	m_speed;

	bool	isEnemyDetected();

	sf::Texture*	m_texLeft;
	sf::Texture*	m_texRight;
};
#endif // !ASTRONAUT_H

