#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameEntity.h"

class Obstacle : public GameEntity {
public:
	Obstacle();
	~Obstacle();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void reset();

private:
	float						m_speed;
	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;
	
	void updatePosition();
};

#endif