#ifndef ASTRO_H
#define ASTRO_H

#include "Player.h"

class Astro : public GameEntity {
public:
	Astro();
	Astro(sf::Vector2f position, int direction, int gameWorldStart, int gameWorldEnd, Player* player);
	~Astro();

	void update(float dt);
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

	sf::Vector2f	m_direction;
	float			m_speed;
	sf::Vector2f	m_velocity;

	bool			m_isCaught;
	bool			m_isMutant;

	int				m_worldStart;
	int				m_worldEnd;

	sf::Texture*	m_texLeft;
	sf::Texture*	m_texRight;
	sf::Texture*	m_mutantLeft;
	sf::Texture*	m_mutantRight;
	Player*			m_player;

	void Wander(float dt);
	void Pause(float dt);
	void Evade();
	void Rise();
	void MutantBehaviour();
	void Swarm();
	void WrapAround();
	bool enemyDetected();
};

#endif