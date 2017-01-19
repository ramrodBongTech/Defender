#ifndef ASTRO_H
#define ASTRO_H

#include "Player.h"
#include "Obstacle.h"

class Astro : public GameEntity {
public:
	enum State {
		WANDER,
		EVADE,
		PAUSE,
		RISE,
		FALL,
		MUTANT,
		EVADE_OBSTACLE,
	};

	Astro();
	Astro(sf::Vector2f position, int gameWorldStart, int gameWorldEnd, Player* player, std::vector<Obstacle>* obstacles);
	~Astro();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void caught();
	void reset();

	bool isCaught();
	bool isMutant();

	void setFalling(bool falling);
	void setCaught(bool caught);

	int getDamage();
	void takeDamage(int damage);

private:
	State						m_state;
	
	float						m_elapsedWanderTime;
	float						m_elapsedPauseTime;
	float						m_speed;

	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;

	bool						m_isCaught;
	bool						m_isMutant;
	bool						m_isFalling;

	int							m_worldStart;
	int							m_worldEnd;
	int							m_damage;
	int							m_health;

	sf::Texture*				m_texLeft;
	sf::Texture*				m_texRight;
	sf::Texture*				m_mutantLeft;
	sf::Texture*				m_mutantRight;
	Player*						m_player;
	std::vector<Obstacle>*		m_obstacles;
	Obstacle*					m_closestObstacle;

	void Wander(float dt);
	void Pause(float dt);
	void Evade();
	void Rise();
	void Fall();
	void MutantBehaviour();
	void Swarm();
	void WrapAround();
	bool enemyDetected();
	void evadeObstacle();
	void checkClosestObstacle();

	const int MAX_OBSTACLE_DISTANCE = 400;
};

#endif