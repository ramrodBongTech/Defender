#ifndef ALIENNEST_H
#define ALIENNEST_H

#include "Missile.h"
#include "Player.h"

class AlienNest : public GameEntity {
public:
	AlienNest(Player* player);
	~AlienNest();

	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	float						m_speed;
	float						m_firingDelay;
	float						m_abductorDelay;
	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;

	std::vector<Missile*>		m_missiles;
	//std::vector<Abductors*>	m_abductors;

	sf::Texture*				m_texLeft;
	sf::Texture*				m_texRight;
	Player*						m_player;

	void updatePosition();
	void spawnAbductor();
	void wander();
	void evade();
	void shoot(float dis);
	void updateMissiles(float dt);
	void updateAbductors(float dt);

	const int MAX_SHOOTING_DISTANCE = 300;
	const int MAX_EVADE_DISTANCE = 600;
	const int MAX_FIRING_DELAY = 10;
	const int MAX_NUM_ABDUCTORS = 20;
	const int MAX_ABDUCTOR_DELAY = 20;
	const int MAX_MISSILES = 2;
};

#endif