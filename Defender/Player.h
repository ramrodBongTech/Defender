#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "GameEntity.h"
#include "BulletFactory.h"

class Player : public GameEntity {
public:
	Player();
	//Player(float speed, sf::Vector2f pos);
	~Player();

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
	void updateBullets(float dt);
	void wrapAround();

	sf::Vector2f			m_direction;
	sf::Vector2f			m_velocity;
	sf::Vector2f			m_acceleration;
	float					m_speed;
	float					m_firingDelay;
	float					m_maxFiringDelay;

	sf::Texture*			m_texLeft = nullptr;
	sf::Texture*			m_texRight = nullptr;

	std::vector<Bullet*>	m_bullets;

	const float				MAX_SPEED = 6.0f;
};
#endif