#ifndef POWERUP_H
#define POWERUP_H

#include "GameEntity.h"

class PowerUp : public GameEntity {
public:
	PowerUp();
	~PowerUp();

	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	enum PowerUpType {
		HYPERJUMP,
	};

	PowerUpType m_type;
};
#endif