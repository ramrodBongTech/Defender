#include "stdafx.h"
#include "Missile.h"

Missile::Missile(): Bullet(),
m_acceleration(sf::Vector2f(0.0f, 0.0f))
{
	m_sprite = sf::Sprite(AssetLoader::getInstance()->m_missile);

	m_width = m_sprite.getTexture()->getSize().y / 2;
	m_height = m_sprite.getTexture()->getSize().y / 2;

	m_speed = 0.1f;
	m_ttl = 0;
	m_maxTTL = 10;
	m_damage = 3;
	m_direction = sf::Vector2f(-1, 0);
	m_orientation = atan2(m_direction.x, m_direction.y) * (180 / 3.141592654),
	m_velocity = sf::Vector2f((m_direction.x * m_acceleration.x), (m_direction.y * m_acceleration.y));
}

Missile::~Missile() {}

void Missile::update(float dt) {}

void Missile::update(float dt, sf::Vector2f* playerPos) 
{
	if (m_alive)
	{
		m_ttl += dt;

		if (m_acceleration.x <= MAX_SPEED)
		{
			m_acceleration.x += m_speed;
			m_acceleration.y += m_speed;
		}

		track(playerPos);
		updatePosition();

		if (sf::milliseconds(m_ttl) >= sf::milliseconds(m_maxTTL))
			reset();
	}
}

void Missile::draw(sf::RenderWindow& window)
{
	if(m_alive)
		window.draw(m_sprite);
}

void Missile::updatePosition()
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);
}

void Missile::track(sf::Vector2f* playerPos)
{
	m_direction = *playerPos - m_position;
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * m_acceleration.x, m_direction.y * m_acceleration.y);

	getNewOrientation();
}

void Missile::explode()
{

}

void Missile::reset()
{
	m_direction = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_position = sf::Vector2f(-9999, -9999);
	m_ttl = 0;
	m_alive = false;
	explode();
}

void Missile::getNewOrientation()
{
	if (sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y)) >= 0)
	{
		m_orientation = atan2(m_direction.x, -m_direction.y) * (180 / 3.141592654);
		m_sprite.setRotation(m_orientation - 90);
	}
}