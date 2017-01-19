#ifndef ASTRO_H
#define ASTRO_H

#include "Player.h"

class Astro : public GameEntity {
public:
	enum State {
		WANDER,
		EVADE,
		PAUSE,
		RISE,
		FALL,
		MUTANT,
	};

	Astro();
	Astro(sf::Vector2f position, int gameWorldStart, int gameWorldEnd, Player* player);
	~Astro();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void caught();
	void reset();

	bool isCaught();
	bool isMutant();

	void setState(State s);
	int getDamage();

private:
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
	int				m_damage;

	sf::Texture*	m_texLeft;
	sf::Texture*	m_texRight;
	sf::Texture*	m_mutantLeft;
	sf::Texture*	m_mutantRight;
	Player*			m_player;

	void Wander(float dt);
	void Pause(float dt);
	void Evade();
	void Rise();
	void Fall();
	void MutantBehaviour();
	void Swarm();
	void WrapAround();
	bool enemyDetected();
};

#endif