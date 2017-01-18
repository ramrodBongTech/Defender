#include "stdafx.h"
#include "Abductor.h"

Abductor::Abductor(Player* player, std::vector<Astro>* astros, BulletManager* bulletManager): GameEntity(),
m_speed(1.0f),
m_firingDelay(3.0f),
m_direction(sf::Vector2f(-1,0)),
m_velocity(sf::Vector2f((m_direction.x * m_speed), (m_direction.y * m_speed))),
m_abductorCaught(false),
m_texLeft(&AssetLoader::getInstance()->m_abductorLeft),
m_texRight(&AssetLoader::getInstance()->m_abductorRight),
m_astronauts(astros),
m_player(player),
m_bulletManager(bulletManager)
{
	m_sprite.setTexture(*m_texLeft);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);
}

Abductor::~Abductor() 
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
}

void Abductor::update(float dt) 
{
	if (m_alive)
	{
		m_firingDelay += dt;

		if (!m_abductorCaught)
			chase();
		else
			rise();

		sf::Vector2f BA = m_player->getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));

		if (dis < MAX_SHOOTING_DISTANCE && m_firingDelay >= MAX_FIRING_DELAY)
			shoot(dis);
	}
}

void Abductor::draw(sf::RenderWindow& window) 
{
	if (m_alive)
		window.draw(m_sprite);
}

void Abductor::updatePosition() 
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);

	if (m_direction.x < 0)
		m_sprite.setTexture(*m_texLeft);
	else
		m_sprite.setTexture(*m_texRight);
}

void Abductor::chase() 
{
	sf::Vector2f temp = m_astronauts->at(0).getPosition() - m_position;
	float _lowestDistance = std::sqrt((temp.x*temp.x) + (temp.y*temp.y));;
	Astro* _closestAstro = &m_astronauts->at(0);
	for (int i = 1; i < m_astronauts->size(); i++)
	{
		sf::Vector2f BA = m_astronauts->at(i).getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));
		if (dis < _lowestDistance && !m_astronauts->at(i).isCaught() && !m_astronauts->at(i).isMutant())
		{
			_lowestDistance = dis;
			_closestAstro = &m_astronauts->at(i);
		}
	}

	if (_lowestDistance < m_sprite.getTexture()->getSize().x / 2)
	{
		m_abductorCaught = true;
		_closestAstro->caught();
		signalAbduction();
	}

	m_direction = _closestAstro->getPosition() - m_position;
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);

	updatePosition();
}

void Abductor::flock() 
{

}

void Abductor::shoot(float dis)
{
	Bullet* _bullet = m_bulletManager->nextBullet();
	if (_bullet != nullptr)
	{
		_bullet->setAlive(true);
		_bullet->setPosition(sf::Vector2f(m_position.x, m_position.y));
		sf::Vector2f tempDir = m_player->getPosition() - m_position;
		float length = sqrt((tempDir.x*tempDir.x) + (tempDir.y*tempDir.y));
		tempDir = sf::Vector2f(tempDir.x / length, tempDir.y / length);
		_bullet->setDirection(tempDir);
		_bullet->setSpeed();
	}
	m_firingDelay = 0;
}

void Abductor::rise()
{
	m_position.y -= m_speed;
	m_sprite.setPosition(m_position);
	if (m_position.y < 0)
		m_abductorCaught = false;
}

void Abductor::signalAbduction()
{

}
