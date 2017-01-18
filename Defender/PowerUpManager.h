#ifndef POWERUPMANAGER_H
#define POWERUPMANAGER_H

#include "PowerUp.h"

class PowerUpManager
{
public:
	PowerUpManager();
	~PowerUpManager();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	std::vector<PowerUp>*	getPowerUps();

private:
	std::vector<PowerUp>	m_powerUps;
	float					m_spawnTimer;

	void spawnPowerUp();

	const int MAX_POWER_UPS = 20;
	const int MAX_SPAWN_TIME = 10;
};

#endif