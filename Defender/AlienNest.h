#ifndef ALIENNEST_H
#define ALIENNEST_H

#include "Missile.h"
//#include "Player.h"
#include "AbductorManager.h"
#include "Astro.h"

class AlienNest : public GameEntity {
public:
	AlienNest(Player* player, std::vector<Astro>* astros, AbductorManager* abMan, BulletManager* bulletManager, std::vector<Obstacle>* obstacles);
	~AlienNest();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void reset();

	int getDamage();
	void takeDamage(int damage);

private:
	float						m_speed;
	float						m_firingDelay;
	float						m_abductorDelay;
	int							m_damage;
	int							m_health;
	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;

	sf::Texture*				m_texLeft;
	sf::Texture*				m_texRight;
	Player*						m_player;
	AbductorManager*			m_abMan;
	BulletManager*				m_bulletManager;
	std::vector<Obstacle>*		m_obstacles;
	Obstacle*					m_closestObstacle;

	void updatePosition();
	void spawnAbductor();
	void wander();
	void evade();
	void shoot(float dis);
	void evadeObstacle();
	void checkClosestObstacle();

	const int MAX_SHOOTING_DISTANCE = 300;
	const int MAX_EVADE_DISTANCE = 600;
	const int MAX_OBSTACLE_DISTANCE = 400;
	const int MAX_FIRING_DELAY = 10;
	const int MAX_NUM_ABDUCTORS = 5;
	const int MAX_ABDUCTOR_DELAY = 5;
	const int MAX_MISSILES = 2;
};

#endif