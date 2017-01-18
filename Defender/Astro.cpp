#include "stdafx.h"
#include "Astro.h"

Astro::Astro() : GameEntity()
{}

Astro::Astro(sf::Vector2f position, int direction, int gameWorldStart, int gameWorldEnd) : GameEntity(),
m_state(State::WANDER),
m_elapsedWanderTime(0),
m_elapsedPauseTime(0),
m_direction(direction),
m_speed(0.8f),
m_velocity(m_speed * m_direction),
m_worldStart(gameWorldStart),
m_worldEnd(gameWorldEnd),
m_texLeft(&AssetLoader::getInstance()->m_astronautLeft),
m_texRight(&AssetLoader::getInstance()->m_astronautRight)
{
	m_position = position;

	if (m_direction < 0)
		m_sprite.setTexture(*m_texLeft);
	else
		m_sprite.setTexture(*m_texRight);

	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);
}

Astro::~Astro()
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
}

void Astro::update(float dt)
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

void Astro::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Astro::Pause(float dt)
{
	m_elapsedPauseTime += dt;
	if (m_elapsedPauseTime > 1000)
		m_state = WANDER;
}

void Astro::Wander(float dt)
{
	m_elapsedWanderTime += dt;

	if (m_elapsedWanderTime >= 3000)
	{
		int _rnd = rand() % 4;
		if (_rnd == 0)
			m_state = State::PAUSE;
		else if (_rnd == 1) {
			m_direction = -m_direction;
			m_velocity = m_speed * -(m_direction);
			if (m_direction > 0)
				m_sprite.setTexture(*m_texLeft);
			else
				m_sprite.setTexture(*m_texRight);
		}
		m_elapsedWanderTime = 0;
	}

	m_position.x += m_velocity;
}

void Astro::Evade()
{
	m_velocity = (m_speed * 2) * m_direction;
	m_position.x += m_velocity;
}

void Astro::WrapAround()
{
	if (m_position.x <= m_worldStart)
		m_position = sf::Vector2f(m_worldEnd, m_position.y);
	else if (m_position.x > m_worldEnd)
		m_position = sf::Vector2f(m_worldStart, m_position.y);
}

bool Astro::enemyDetected()
{
	return false;
}

