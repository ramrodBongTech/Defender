#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet() : GameEntity(),
m_speed(12),
m_ttl(0),
m_maxTTL(5),
m_width(0),
m_height(0),
m_damage(1),
m_direction(sf::Vector2f(0, 0)),
m_velocity(sf::Vector2f(0, 0)),
m_orientation(atan2(m_direction.x, m_direction.y) * (180 / 3.141592654)),
m_isPlayerBullet(false),
m_color(sf::Color::Red)
{
	m_sprite = sf::Sprite(AssetLoader::getInstance()->m_bullet);
	m_width = m_sprite.getTexture()->getSize().x / 2;
	m_height = m_sprite.getTexture()->getSize().y / 2;
	setSprite();
	m_color = m_sprite.getColor();
}

Bullet::~Bullet() {}

void Bullet::update(float dt) 
{
	if (m_alive) 
	{
		m_position += m_velocity;
		m_sprite.setPosition(m_position);

		m_ttl += dt;

		if (sf::milliseconds(m_ttl) >= sf::milliseconds(m_maxTTL))
			reset();

		checkBorder();
	}
}

void Bullet::draw(sf::RenderWindow &window) 
{
	if (m_alive)
	{
		int tempX = m_position.x;
		int tempY = m_position.y;
		int tempAlpha = 255;
		for(int i = 1; i < 9; i++)
		{ 
			window.draw(m_sprite);

			m_sprite.setPosition(sf::Vector2f(tempX, tempY));
			m_sprite.setColor(sf::Color(m_color.r, 0, 0, tempAlpha));

			if (m_direction.x > 0)
				tempX -= m_direction.x;
			else
				tempX += m_direction.x;

			if (m_direction.y > 0)
				tempY += m_direction.y;
			else
				tempY -= m_direction.y;
		
			tempAlpha -= tempAlpha / 2;

			m_sprite.setScale(m_sprite.getScale().x * 0.95, 1.0f);
		}

		m_sprite.setPosition(m_position);
		m_sprite.setColor(m_color);
		m_sprite.setScale(0.25f, 1.0f);
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

float Bullet::getWidth() { return m_width; }

float Bullet::getHeight() { return m_height; }

int Bullet::getDamage() { return m_damage; }

void Bullet::setDirection(sf::Vector2f direction) 
{ 
	m_direction = direction; 
	getNewOrientation();
}

void Bullet::setSpeed() { m_velocity = sf::Vector2f(m_speed * m_direction.x, m_speed * m_direction.y); }

void Bullet::setIsPlayerBullet(bool ipb) { m_isPlayerBullet = ipb; }

bool Bullet::isplayerBullet() { return m_isPlayerBullet; }

void Bullet::setSprite()
{
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(sf::Vector2f(m_width, m_height));
	m_sprite.setRotation(90);
	m_sprite.setColor(sf::Color(255, 0, 0, 255));
	m_sprite.setScale(0.25f, 1.0f);
}

void Bullet::checkBorder()
{
	if (m_position.x + m_width <= 0)
	{				// From left to right
		m_position.x = 10800;
		m_sprite.setPosition(m_position);
	}
	if (m_position.x - m_width >= 10800)
	{				// From right to left
		m_position.x = 0;
		m_sprite.setPosition(m_position);
	}
}

void Bullet::getNewOrientation()
{
	if (sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y)) >= 0)
	{
		m_orientation = atan2(m_direction.x, -m_direction.y) * (180 / 3.141592654);
		m_sprite.setRotation(m_orientation);
	}
}
