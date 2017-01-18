#ifndef ABDUCTOR_H
#define ABDUCTOR_H

#include "GameEntity.h"
#include "BulletManager.h"
#include "Astro.h"
#include "Player.h"

class Abductor : public GameEntity {
public:
	Abductor(Player* player, std::vector<Astro>* astros, BulletManager* bulletManager);
	~Abductor();

	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	float						m_speed;
	float						m_firingDelay;
	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;

	std::vector<Astro>*			m_astronauts;
	Player*						m_player;
	BulletManager*				m_bulletManager;

	sf::Texture*				m_texLeft;
	sf::Texture*				m_texRight;

	void updatePosition();
	void chase();
	void flock();
	void shoot(float dis);

	const int MAX_SHOOTING_DISTANCE = 300;
	const int MAX_FIRING_DELAY = 3;
};

#endif