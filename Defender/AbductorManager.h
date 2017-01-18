#ifndef ABDUCTORMANAGER_H
#define ABDUCTORMANAGER_H

#include "Abductor.h"

class AbductorManager
{
public:
	AbductorManager(std::vector<Astro>* astros, Player* player, BulletManager* bulletManager);
	~AbductorManager();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	Abductor*				nextAbductor();
	std::vector<Abductor>*	getAbductors();

private:
	std::vector<Abductor>	m_abductors;
	std::vector<Astro>*		m_astros;
	Player*					m_player;

	const int MAX_ABDUCTORS = 20;
};

#endif