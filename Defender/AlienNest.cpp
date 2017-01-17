#include "stdafx.h"
#include "AlienNest.h"

AlienNest::AlienNest(Player* player) : GameEntity(),
m_speed(1.0f),
m_firingDelay(10.0f),
m_abductorDelay(0.0f),
m_direction(sf::Vector2f(-1, 0)),
m_velocity(sf::Vector2f((m_direction.x * m_speed), (m_direction.y * m_speed))),
m_texLeft(&AssetLoader::getInstance()->m_alienNestLeft),
m_texRight(&AssetLoader::getInstance()->m_alienNestRight),
m_player(player)
{
	m_position = sf::Vector2f(100, 100);
	m_alive = true;
	m_sprite.setTexture(*m_texLeft);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);

	for (int i = 0; i < MAX_MISSILES; i++)
	{
		m_missiles.push_back(new Missile(m_player));
	}

	/*for (int i = 0; i < MAX_ABDUCTORS; i++)
	{
		m_abductors.push_back(new Abductor());
	}*/
}

AlienNest::~AlienNest()
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
	for (int i = 0; i < m_missiles.size(); i++)
	{
		delete m_missiles.at(i);
		m_missiles.at(i) = nullptr;
	}
	/*for (int i = 0; i < m_abductors.size(); i++)
	{
		delete m_abductors.at(i);
		m_abductors.at(i) = nullptr;
	}*/
}

void AlienNest::update(float dt) 
{
	if (m_alive)
	{
		m_firingDelay += dt;
		m_abductorDelay += dt;

		updateMissiles(dt);
		updateAbductors(dt);

		sf::Vector2f BA = m_player->getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));

		if (dis > MAX_EVADE_DISTANCE)
			wander();
		else
			evade();

		if (dis < MAX_SHOOTING_DISTANCE && m_firingDelay >= MAX_FIRING_DELAY)
			shoot(dis);

		if (m_abductorDelay >= MAX_ABDUCTOR_DELAY)
			spawnAbductor();
	}
}

void AlienNest::draw(sf::RenderWindow& window)
{
	if (m_alive)
	{
		window.draw(m_sprite);

		for (int i = 0; i < m_missiles.size(); i++)
			m_missiles.at(i)->draw(window);

		/*for (int i = 0; i < m_abductors.size(); i++)
			m_abductors.at(i)->draw(window);*/
	}
}

void AlienNest::updatePosition()
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);
}

void AlienNest::spawnAbductor()
{
	/*for (int i = 0; i < m_abductors.size(); i++)
	{
		if (!m_abductors.at(i)->getAlive())
		{
			m_abductors.at(i)->setAlive(true);
			m_abductors.at(i)->setPosition();
			break;
		}
	}*/
}

void AlienNest::wander()
{

}

void AlienNest::evade()
{
	m_direction = m_position - m_player->getPosition();
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);

	updatePosition();
}

void AlienNest::shoot(float dis)
{
	for (int i = 0; i < m_missiles.size(); i++)
	{
		if (!m_missiles.at(i)->getAlive())
		{
			m_missiles.at(i)->setAlive(true);
			m_missiles.at(i)->setPosition(sf::Vector2f(m_position.x, m_position.y));
			break;
		}
	}
	m_firingDelay = 0;
}

void AlienNest::updateMissiles(float dt)
{
	for (int i = 0; i < m_missiles.size(); i++)
	{
		m_missiles.at(i)->update(dt);
	}
}

void AlienNest::updateAbductors(float dt)
{
	/*for (int i = 0; i < m_abductors.size(); i++)
	{
		m_abductors.at(i)->update(dt);
	}*/
}