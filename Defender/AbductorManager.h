#ifndef ABDUCTORMANAGER_H
#define ABDUCTORMANAGER_H

#include "Abductor.h"

class AbductorManager
{
public:
	AbductorManager(std::vector<Astro>* astros, Player* player, BulletManager* bulletManager, std::vector<Obstacle>* obstacles);
	~AbductorManager();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	Abductor*				nextAbductor();
	std::vector<Abductor>*	getAbductors();

private:
	std::vector<Abductor>	m_abductors;

	const int MAX_ABDUCTORS = 20;
};

#endif