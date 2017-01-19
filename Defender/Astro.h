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
		SWARM,
	};

	Astro();
	Astro(sf::Vector2f position, int gameWorldStart, int gameWorldEnd, Player* player, std::vector<Obstacle>* obstacles);
	~Astro();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void Swarm(std::vector<Astro> astronaut);

	void caught();
	void reset();

	bool isCaught();
	bool isMutant();

	void setFalling(bool falling);
	void setCaught(bool caught);
	void setMutant(bool mutant);

	int getDamage();
	void takeDamage(int damage);

	sf::Vector2f GetVelocity();

private:
	State						m_state;
	
	float						m_elapsedWanderTime;
	float						m_elapsedPauseTime;
	float						m_speed;
	float						m_swarmDelay;

	int							m_worldStart;
	int							m_worldEnd;
	int							m_damage;
	int							m_health;
	int							m_swarmRandomiser;

	bool						m_isCaught;
	bool						m_isMutant;
	bool						m_isFalling;
	bool						m_isSwarming;

	sf::Vector2f				m_acceleration;
	sf::Vector2f				m_direction;
	sf::Vector2f				m_velocity;

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
	void swarm();
	void WrapAround();
	bool enemyDetected();
	void evadeObstacle();
	void checkClosestObstacle();

	sf::Vector2f Separation(std::vector<Astro> astronauts);
	sf::Vector2f Alignment(std::vector<Astro> astronauts);
	sf::Vector2f Cohesion(std::vector<Astro> astronauts);

	sf::Vector2f Seek(sf::Vector2f v);
	sf::Vector2f normalize(sf::Vector2f v);

	const int					MAX_OBSTACLE_DISTANCE = 400;
	const float					MAX_SPEED = 4.8f;
	const float					MAX_FORCE = .05f;
};

#endif