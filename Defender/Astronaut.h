#ifndef ASTRONAUT_H
#define ASTRONAUT_h

#include "stdafx.h"
#include "GameEntity.h"

class Astronaut : public GameEntity 
{
public:
	Astronaut();
	Astronaut(sf::Vector2f position, int direction, int gameWorldStart, int gameWorldEnd);
	~Astronaut();

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

	float	m_velocity;
	float	m_direction;
	float	m_speed;

	bool	enemyDetected();

	int			m_worldStart;
	int			m_worldEnd;

	sf::Texture*	m_texLeft;
	sf::Texture*	m_texRight;
};
#endif // !ASTRONAUT_H

