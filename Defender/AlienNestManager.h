#ifndef ALIENNESTMANAGER_H
#define ALIENNESTMANAGER_H

#include "AlienNest.h"

class AlienNestManager
{
public:
	AlienNestManager(Player* player, std::vector<Astro>* astros, AbductorManager* abMan, BulletManager* bulletManager, std::vector<Obstacle>* obstacles);
	~AlienNestManager();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	std::vector<AlienNest>*	getNests();

private:
	std::vector<AlienNest>	m_nests;
	float m_spawnTimer;

	void spawnNest();

	const int MAX_NESTS = 5;
	const int MAX_SPAWN_TIME = 6;
};

#endif