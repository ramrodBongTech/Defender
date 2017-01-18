#ifndef ASTRO_H
#define ASTRO_H

#include "GameEntity.h"

class Astro : public GameEntity {
public:
	Astro();
	Astro(sf::Vector2f position, int direction, int gameWorldStart, int gameWorldEnd);
	~Astro();

	void update(float dt);
	void update(float dt, sf::Vector2f playerPos);
	void draw(sf::RenderWindow& window);

	void caught();

	bool isCaught();
	bool isMutant();

private:
	enum State {
		WANDER,
		EVADE,
		PAUSE,
		RISE,
		MUTANT,
	};

	State m_state;
	
	float			m_elapsedWanderTime;
	float			m_elapsedPauseTime;

	float			m_direction;
	float			m_speed;
	float			m_velocity;

	bool			m_isCaught;
	bool			m_isMutant;

	int				m_worldStart;
	int				m_worldEnd;

	sf::Texture*	m_texLeft;
	sf::Texture*	m_texRight;
	sf::Texture*	m_mutantLeft;
	sf::Texture*	m_mutantRight;

	void Wander(float dt);
	void Pause(float dt);
	void Evade();
	void Rise();
	void MutantBehaviour(sf::Vector2f playerPos);
	void Swarm();
	void WrapAround();
	bool enemyDetected();
};

#endif