#include "stdafx.h"
#include "Astronaut.h"

Astronaut::Astronaut() : GameEntity()
{
	
}

Astronaut::Astronaut(sf::Vector2f position, int direction, int gameWorldStart, int gameWorldEnd) : GameEntity()
{
	m_worldStart = gameWorldStart;
	m_worldEnd = gameWorldEnd;

	m_state = State::WANDER;

	m_elapsedWanderTime = 0;
	m_position = position;
	m_speed = 0.5f;
	m_direction = direction;
	m_velocity =  m_speed * m_direction;

	m_texLeft = &AssetLoader::getInstance()->m_astronautLeft;
	m_texRight = &AssetLoader::getInstance()->m_astronautRight;

	if (m_direction < 0)
		m_sprite.setTexture(*m_texLeft);
	else
		m_sprite.setTexture(*m_texRight);

	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);
}

Astronaut::~Astronaut()
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
}

void Astronaut::update(float dt)
{
	switch (m_state)
	{
		case State::WANDER:
			Wander(dt);
			break;
		case State::PAUSE:
			Pause(dt);
			break;
		case State::EVADE:
			Evade();
			break;
	}

	if (enemyDetected())
		m_state = State::EVADE;

	m_sprite.setPosition(m_position);
	WrapAround();
}

void Astronaut::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Astronaut::Pause(float dt)
{
	m_elapsedPauseTime += dt;
	if (m_elapsedPauseTime > 1000)
		m_state = WANDER;
}

void Astronaut::Wander(float dt) 
{
	m_elapsedWanderTime += dt;
	std::cout << m_elapsedWanderTime << std::endl;

	if (m_elapsedWanderTime >= 3000) 
	{
		int _rnd = rand() % 4;
		if (_rnd == 0)
			m_state = State::PAUSE;
		else if (_rnd == 1) {
			m_velocity = m_speed * -(m_direction);
			if (m_sprite.getTexture() == m_texLeft)
				m_sprite.setTexture(*m_texRight);
			else
				m_sprite.setTexture(*m_texLeft);
		}
		m_elapsedWanderTime = 0;
	}

	m_position.x += m_velocity;
}

void Astronaut::Evade()
{
	m_velocity = (m_speed * 2) * m_direction;
	m_position.x += m_velocity;
}

void Astronaut::WrapAround()
{
	if (m_position.x <= m_worldStart)
		m_position = sf::Vector2f(m_worldEnd, m_position.y);
	else if (m_position.x > m_worldEnd)
		m_position = sf::Vector2f(m_worldStart, m_position.y);
}

bool Astronaut::enemyDetected() 
{ 
	return false; 
}

