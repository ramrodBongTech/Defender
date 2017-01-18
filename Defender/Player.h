#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "BulletManager.h"

class Player : public GameEntity {
public:
	Player();
	~Player();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel);
	void setAcceleration(sf::Vector2f accel);
	void setManager(BulletManager* bf);

	float getWidth();
	float getHeight();

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

	float					m_speed;
	float					m_firingDelay;
	float					m_maxFiringDelay;
	sf::Vector2f			m_direction;
	sf::Vector2f			m_acceleration;
	sf::Vector2f			m_velocity;

	sf::Texture*			m_texLeft;
	sf::Texture*			m_texRight;
	BulletManager*			m_bulletManager;

	const int		MAX_SPEED = 6.0f;
	const int		MAX_BULLETS = 100;
};
#endif