#include "stdafx.h"
#include "AlienNest.h"

AlienNest::AlienNest(Player* player, std::vector<Astro>* astros, AbductorManager* abMan, BulletManager* bulletManager, std::vector<Obstacle>* obstacles) : GameEntity(),
m_speed(1.0f),
m_firingDelay(10.0f),
m_abductorDelay(0.0f),
m_damage(10),
m_health(1),
m_direction(sf::Vector2f(-1, 0)),
m_velocity(sf::Vector2f((m_direction.x * m_speed), (m_direction.y * m_speed))),
m_texLeft(&AssetLoader::getInstance()->m_alienNestLeft),
m_texRight(&AssetLoader::getInstance()->m_alienNestRight),
m_player(player),
m_abMan(abMan),
m_bulletManager(bulletManager),
m_obstacles(obstacles)
{
	m_position = sf::Vector2f(rand() % 10800, rand() % 300);
	m_alive = true;
	m_sprite.setTexture(*m_texLeft);
	m_sprite.setPosition(m_position);
	m_width = m_texLeft->getSize().x / 2;
	m_height = m_texLeft->getSize().y / 2;
	m_sprite.setOrigin(m_width, m_height);
}

AlienNest::~AlienNest()
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
}

void AlienNest::update(float dt) 
{
	if (m_alive)
	{
		m_firingDelay += dt;
		m_abductorDelay += dt;

		checkClosestObstacle();

		sf::Vector2f OT = m_closestObstacle->getPosition() - m_position;
		float obstacleDis = std::sqrt((OT.x*OT.x) + (OT.y*OT.y));

		sf::Vector2f BA = m_player->getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));

		if (obstacleDis < MAX_OBSTACLE_DISTANCE)
			evadeObstacle();
		else if (dis > MAX_EVADE_DISTANCE)
			wander();
		else
			evade();

		if (dis < MAX_SHOOTING_DISTANCE && m_firingDelay >= MAX_FIRING_DELAY)
			shoot(dis);

		if (m_abductorDelay >= MAX_ABDUCTOR_DELAY)
			spawnAbductor();

		if (m_health <= 0)
			reset();
	}
}

void AlienNest::draw(sf::RenderWindow& window)
{
	if (m_alive)
		window.draw(m_sprite);
}

void AlienNest::reset()
{
	m_alive = false;
	m_position = sf::Vector2f(99999, 99999);
	m_sprite.setPosition(m_position);
}

int AlienNest::getDamage() { return m_damage; }

void AlienNest::takeDamage(int damage) { m_health -= damage; }

void AlienNest::updatePosition()
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);

	if (m_direction.x < 0)
		m_sprite.setTexture(*m_texLeft);
	else
		m_sprite.setTexture(*m_texRight);
}

void AlienNest::spawnAbductor()
{
	Abductor* _abductor = m_abMan->nextAbductor();
	if (_abductor != nullptr)
	{
		_abductor->setPosition(m_position);
		_abductor->setAlive(true);
	}
	m_abductorDelay = 0;
}

void AlienNest::wander()
{

}

void AlienNest::evade()
{
	if (m_position.y - m_sprite.getTexture()->getSize().y/2 >= 0)
	{
		m_direction = m_position - m_player->getPosition();
		float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
		m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
		m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);

		updatePosition();
	}
	else
		m_position.y = 1 + m_sprite.getTexture()->getSize().y / 2;
}

void AlienNest::shoot(float dis)
{
	Missile* _missile = m_bulletManager->nextMissile();
	if (_missile != nullptr)
	{
		_missile->setAlive(true);
		_missile->setPosition(sf::Vector2f(m_position.x, m_position.y));
	}
	m_firingDelay = 0;
}

void AlienNest::evadeObstacle()
{
	m_direction = m_position - m_closestObstacle->getPosition();
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);
	updatePosition();
}

void AlienNest::checkClosestObstacle()
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