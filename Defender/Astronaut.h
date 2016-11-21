#ifndef ASTRONAUT_H
#define ASTRONAUT_h

#include "stdafx.h"
#include "GameEntity.h"

class Astronaut : public GameEntity 
{
public:
	Astronaut();
	~Astronaut();

	void update(float dt);
	void draw(sf::RenderWindow& window);
	bool isEnemyDetected();

private:
	void Evade();

	bool m_enemyDetected;
	sf::Texture*	m_tex;
};
#endif // !ASTRONAUT_H

