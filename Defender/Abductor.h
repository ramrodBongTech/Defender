#ifndef ABDUCTOR_H
#define ABDUCTOR_H

#include "GameEntity.h"
#include "BulletManager.h"
#include "Astro.h"
#include "Player.h"
#include "Obstacle.h"
#include <vector>

using namespace std;

class Abductor : public GameEntity {
public:
	Abductor(Player* player, std::vector<Astro>* astros, BulletManager* bulletManager, std::vector<Obstacle>* obstacles);
	~Abductor();

	void Flock(vector<Abductor> abductors);

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void reset();

	sf::Vector2f GetVelocity();

	int getDamage();
	void takeDamage(int damage);

private:
	float						m_speed;
	float						m_firingDelay;

	float						m_flockDelay;
	bool						m_flocking;

	float						m_signalTimer;
	bool	isFlocking();

	int							m_flockRandomiser;

	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;
	sf::Vector2f				m_acceleration;
	sf::Vector2f				m_signalPos;
	bool						m_abductorCaught;

	bool						m_signal;
	int							m_damage;
	int							m_health;

	const float					MAX_SPEED = 2.f;
	const float					MAX_FORCE = .05f;

	std::vector<Astro>*			m_astronauts;
	Player*						m_player;
	BulletManager*				m_bulletManager;
	Astro*						m_caughtAstro;
	std::vector<Obstacle>*		m_obstacles;
	Obstacle*					m_closestObstacle;

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
	void evadeObstacle();
	void checkClosestObstacle();

	const int MAX_SHOOTING_DISTANCE = 200;
	const int MAX_EVADE_DISTANCE = 400;
	const int MAX_FIRING_DELAY = 3;
};

#endif