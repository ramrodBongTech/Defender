#include "stdafx.h"
#include "Astro.h"

Astro::Astro() : GameEntity()
{}

Astro::Astro(sf::Vector2f position, int gameWorldStart, int gameWorldEnd, Player* player) : GameEntity(),
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
m_damage(10),
m_health(4),
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
	m_width = m_texLeft->getSize().x / 2;
	m_height = m_texLeft->getSize().y / 2;
	m_sprite.setOrigin(m_width, m_height);
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
		case State::FALL:
			Fall();
			break;
		case State::MUTANT:
			MutantBehaviour();
			break;
		case State::EVADE_OBSTACLE:
			evadeObstacle();
			break;
		}

		if (enemyDetected())
			m_state = State::EVADE;

		checkClosestObstacle();

		sf::Vector2f BA = m_closestObstacle->getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));

		if (dis < MAX_OBSTACLE_DISTANCE)
			m_state = State::EVADE_OBSTACLE;

		m_sprite.setPosition(m_position);
		WrapAround();

		if (m_health <= 0)
			reset();
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

void Astro::reset()
{
	m_alive = false;
	m_position = sf::Vector2f(99999, 99999);
	m_sprite.setPosition(m_position);
}

bool Astro::isCaught() { return m_isCaught; }

bool Astro::isMutant() { return m_isMutant; }

void Astro::setState(State s) { m_state = s; }

int Astro::getDamage() { return m_damage; }

void Astro::takeDamage(int damage) { m_health -= damage; }

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

void Astro::Fall()
{
	m_position.y += 1.0f;
	m_sprite.setPosition(m_position);
	if (m_position.y >= 0.9 * 600)
	{
		m_state = State::WANDER;
		if(m_direction.x < 0)
			m_sprite.setTexture(*m_texLeft);
		else
			m_sprite.setTexture(*m_texRight);

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

void Astro::evadeObstacle()
{
	m_direction = m_position - m_closestObstacle->getPosition();
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);
	m_position += m_velocity;
}

void Astro::checkClosestObstacle()
{
	sf::Vector2f temp = m_obstacles->at(0).getPosition() - m_position;
	float _lowestDistance = std::sqrt((temp.x*temp.x) + (temp.y*temp.y));;
	m_closestObstacle = &m_obstacles->at(0);
	for (int i = 0; i < m_obstacles->size(); i++)
	{
		sf::Vector2f BA = m_obstacles->at(i).getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));
		if (dis < _lowestDistance && !m_obstacles->at(i).getAlive())
		{
			_lowestDistance = dis;
			m_closestObstacle = &m_obstacles->at(i);
		}
	}
}
