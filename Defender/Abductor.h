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

	sf::Vector2f GetVelocity();
	bool isFlocking();
private:
	float						m_speed;
	float						m_firingDelay;

	float						m_flockDelay;
	bool						m_flocking;

	int							m_flockRandomiser;
	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;
	sf::Vector2f				m_acceleration;
	bool						m_abductorCaught;
	const float					MAX_SPEED = 2.f;
	const float					MAX_FORCE = .05f;

	std::vector<Astro>*			m_astronauts;
	Player*						m_player;
	BulletManager*				m_bulletManager;

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
};

#endif