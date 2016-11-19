#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "GameEntity.h"
#include "Bullet.h"

class Player : public GameEntity {
public:
	Player();
	Player(float speed, sf::Vector2f pos);
	~Player();

	sf::Vector2f getVelocity();

	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	void processInput();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void slowX();
	void slowY();
	void shoot();
	void wrapAround();

	sf::Vector2f	m_direction;
	sf::Vector2f	m_velocity;
	sf::Vector2f	m_acceleration;
	float			m_speed;
	float			m_firingDelay;

	sf::Texture*	m_texLeft = nullptr;
	sf::Texture*	m_texRight = nullptr;

	Bullet*			m_bullet = nullptr;

	const float		MAX_SPEED = 6.0f;
	const float		MAX_FIRING_DELAY = 1000.0f;
};
#endif