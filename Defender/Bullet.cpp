#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	m_texture = &AssetLoader::getInstance()->m_bullet;
	m_sprite = sf::Sprite(*m_texture);
	m_radius = m_texture->getSize().y / 2;

	m_direction = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);

	m_ttl = 0;
	m_damage = 1;

	setSprite();
}

Bullet::~Bullet() 
{
	m_texture = nullptr;
}

void Bullet::update(float dt) 
{
	if (m_alive) 
	{
		m_position += m_velocity;
		m_sprite.setPosition(m_position);

		m_ttl += dt;

		if (sf::milliseconds(m_ttl) >= sf::milliseconds(MAX_TTL))
			reset();

		checkBorder();
	}
}

void Bullet::draw(sf::RenderWindow &window) 
{
	if (m_alive)
		window.draw(m_sprite);
}

void Bullet::reset()
{
	m_direction = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_position = sf::Vector2f(-9999, -9999);
	m_ttl = 0;
	m_alive = false;
}

int Bullet::getRadius() { return m_radius; }

int Bullet::getDamage() { return m_damage; }

void Bullet::setDirection(sf::Vector2f direction) { m_direction = direction; }

void Bullet::setSpeed() { m_velocity = sf::Vector2f(MAX_SPEED * m_direction.x, 0); }

void Bullet::setSprite()
{
	m_sprite.setPosition(sf::Vector2f(0, 0));
	m_sprite.setOrigin(sf::Vector2f(m_radius, m_radius));
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(90);
}

void Bullet::checkBorder()
{
	if (m_position.x + m_radius <= -3200)
	{				// From left to right
		m_position.x = 4000;
		m_sprite.setPosition(m_position);
	}
	if (m_position.x - m_radius >= 4000)
	{				// From right to left
		m_position.x = -3200;
		m_sprite.setPosition(m_position);
	}
}
