#ifndef ASTRO_H
#define ASTRO_H

#include "GameEntity.h"

class Astro : public GameEntity {
public:
	Astro();
	Astro(sf::Vector2f position, int direction, int gameWorldStart, int gameWorldEnd);
	~Astro();

	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	enum State {
		WANDER,
		EVADE,
		PAUSE,
	};
	State m_state;
	void Wander(float dt);
	void Pause(float dt);
	void Evade();
	void WrapAround();

	float m_elapsedWanderTime;
	float m_elapsedPauseTime;

	float	m_direction;
	float	m_speed;
	float	m_velocity;

	bool	enemyDetected();

	int			m_worldStart;
	int			m_worldEnd;

	sf::Texture*	m_texLeft;
	sf::Texture*	m_texRight;
};

#endif