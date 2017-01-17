#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet() : GameEntity(),
m_direction(sf::Vector2f(0, 0)),
m_velocity(sf::Vector2f(0, 0)),
m_ttl(0),
m_radius(0),
m_damage(1),
m_color(sf::Color::Red)
{
	m_sprite.setTexture(AssetLoader::getInstance()->m_bullet);
	m_radius = m_sprite.getTexture()->getSize().y / 2;

	setSprite();
}

Bullet::~Bullet() {}

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
	{
		int tempX = m_position.x;
		int tempAlpha = 255;
		for(int i = 1; i < 9; i++)
		{ 
			window.draw(m_sprite);

			m_sprite.setPosition(sf::Vector2f(tempX, m_position.y));
			m_sprite.setColor(sf::Color(m_color.r, 0, 0, tempAlpha));

			if (m_direction.x > 0)
				tempX -= m_radius;
			else
				tempX += m_radius;
		
			tempAlpha -= tempAlpha / 2;
		}

		m_sprite.setPosition(m_position);
		m_sprite.setColor(m_color);
	}
}

void Bullet::reset()
{
	m_direction = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_position = sf::Vector2f(-99999, -99999);
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
	m_sprite.setColor(sf::Color(255, 0, 0, 255));
	m_sprite.setScale(0.25f, 1.0f);

	m_color = m_sprite.getColor();
}

void Bullet::checkBorder()
{
	if (m_position.x + m_radius <= -4800)
	{				// From left to right
		m_position.x = 6000;
		m_sprite.setPosition(m_position);
	}
	if (m_position.x - m_radius >= 6000)
	{				// From right to left
		m_position.x = -4800;
		m_sprite.setPosition(m_position);
	}
}
