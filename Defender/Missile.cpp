#include "stdafx.h"
#include "Missile.h"

Missile::Missile(Player* player): GameEntity(),
m_speed(0.1f),
m_ttl(0),
m_radius(0),
m_damage(1),
m_acceleration(sf::Vector2f(0.0f, 0.0f)),
m_direction(sf::Vector2f(-1, 0)),
m_orientation(atan2(m_direction.x, m_direction.y) * (180 / 3.141592654)),
m_velocity(sf::Vector2f((m_direction.x * m_acceleration.x), (m_direction.y * m_acceleration.y))),
m_player(player)
{
	m_sprite.setTexture(AssetLoader::getInstance()->m_missile);
	m_sprite.setRotation(m_orientation - 90);
	m_radius = m_sprite.getTexture()->getSize().y / 2;
}

Missile::~Missile() {}

void Missile::update(float dt) {}

void Missile::update(float dt, sf::Vector2f& targetPos)
{
	if (m_alive)
	{
		m_ttl += dt;

		if (m_acceleration.x <= MAX_SPEED)
		{
			m_acceleration.x += m_speed;
			m_acceleration.y += m_speed;
		}

		track(targetPos);
		updatePosition();

		if (sf::milliseconds(m_ttl) >= sf::milliseconds(MAX_TTL))
			reset();
	}
}

void Missile::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

int Missile::getRadius() { return m_radius; }

int Missile::getDamage() { return m_damage; }

void Missile::updatePosition()
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);
}

void Missile::track(sf::Vector2f& targetPos)
{
	m_direction = targetPos - m_position;
	normalize(m_direction);
	m_velocity = sf::Vector2f(m_direction.x * m_acceleration.x, m_direction.y * m_acceleration.y);

	getNewOrientation();
}

void Missile::explode()
{

}

void Missile::reset()
{
	m_direction = sf::Vector2f(0, 0);
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

void Missile::normalize(sf::Vector2f& vec)
{
	float length = sqrt((vec.x*vec.x) + (vec.y*vec.y));
	vec = sf::Vector2f(vec.x / length, vec.y / length);
}