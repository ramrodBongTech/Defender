#include "stdafx.h"
#include "Astro.h"

Astro::Astro() : GameEntity()
{}

Astro::Astro(sf::Vector2f position, int direction, int gameWorldStart, int gameWorldEnd, Player* player) : GameEntity(),
m_state(State::WANDER),
m_elapsedWanderTime(0),
m_elapsedPauseTime(0),
m_direction(sf::Vector2f((rand() % 1)-1, 0)),
m_speed(0.8f),
m_velocity(sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed)),
m_isCaught(false),
m_isMutant(false),
m_worldStart(gameWorldStart),
m_worldEnd(gameWorldEnd),
m_texLeft(&AssetLoader::getInstance()->m_astronautLeft),
m_texRight(&AssetLoader::getInstance()->m_astronautRight),
m_mutantLeft(&AssetLoader::getInstance()->m_mutantLeft),
m_mutantRight(&AssetLoader::getInstance()->m_mutantRight),
m_player(player)
{
	m_position = position;
	m_alive = true;

	if (m_direction.x < 0)
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
	if (m_alive)
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
		case State::RISE:
			Rise();
			break;
		case State::MUTANT:
			MutantBehaviour();
			break;
		}

		if (enemyDetected())
			m_state = State::EVADE;

		m_sprite.setPosition(m_position);
		WrapAround();
	}
}

void Astro::draw(sf::RenderWindow & window)
{
	if (m_alive)
		window.draw(m_sprite);
}

void Astro::caught() 
{ 
	m_state = State::RISE;
	m_isCaught = true;
}

bool Astro::isCaught() { return m_isCaught; }

bool Astro::isMutant() { return m_isMutant; }

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
			m_direction.x = -m_direction.x;
			m_velocity = sf::Vector2f(m_speed * m_direction.x, 0);
			if (m_direction.x > 0)
				m_sprite.setTexture(*m_texLeft);
			else
				m_sprite.setTexture(*m_texRight);
		}
		m_elapsedWanderTime = 0;
	}

	m_position += m_velocity;
}

void Astro::Evade()
{
	m_velocity.x = (m_speed * 2) * m_direction.x;
	m_position.x += m_velocity.x;
}

void Astro::Rise()
{
	m_position.y -= 1.0f;
	m_sprite.setPosition(m_position);
	if (m_position.y < 0)
	{
		m_state = State::MUTANT;
		m_sprite.setTexture(*m_mutantLeft);
		m_isMutant = true;
		m_isCaught = false;
	}
}

void Astro::MutantBehaviour()
{
	m_direction = m_player->getPosition() - m_position;
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * (m_speed * 6), m_direction.y * (m_speed * 6));

	m_position += m_velocity;;
}

void Astro::Swarm()
{

}

void Astro::WrapAround()
{
	if (m_position.x <= m_worldStart)
		m_position = sf::Vector2f(m_worldEnd, m_position.y);
	else if (m_position.x > m_worldEnd)
		m_position = sf::Vector2f(m_worldStart, m_position.y);
}

bool Astro::enemyDetected(){ return false; }

