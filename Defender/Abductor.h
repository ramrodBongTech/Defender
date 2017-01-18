#ifndef ABDUCTOR_H
#define ABDUCTOR_H

#include "GameEntity.h"
#include "BulletManager.h"
#include "Astro.h"
#include "Player.h"
#include <vector>

using namespace std;

class Abductor : public GameEntity {
public:
	Abductor(Player* player, std::vector<Astro>* astros, BulletManager* bulletManager);
	~Abductor();

	void Flock(vector<Abductor> abductors);

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void reset();

	sf::Vector2f GetVelocity();

private:
	float						m_speed;
	float						m_firingDelay;
	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;
	sf::Vector2f				m_acceleration;
	bool						m_abductorCaught;

	std::vector<Astro>*			m_astronauts;
	Player*						m_player;
	BulletManager*				m_bulletManager;
	Astro*						m_caughtAstro;

	sf::Texture*				m_texLeft;
	sf::Texture*				m_texRight;

	sf::Vector2f Separation(vector<Abductor> abductors);
	sf::Vector2f Alignment(vector<Abductor> abductors);
	sf::Vector2f Cohesion(vector<Abductor> abductors);

	sf::Vector2f Seek(sf::Vector2f v);
	sf::Vector2f normalize(sf::Vector2f v);

	void updatePosition();
	void chase();
	void flock();
	void shoot(float dis);
	void rise();
	void signalAbduction();

	const int MAX_SHOOTING_DISTANCE = 300;
	const int MAX_FIRING_DELAY = 3;
	const int MAX_SPEED = 5;
};

#endif