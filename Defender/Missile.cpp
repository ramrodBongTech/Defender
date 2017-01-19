#include "stdafx.h"
#include "Missile.h"

Missile::Missile(): Bullet(),
m_acceleration(sf::Vector2f(0.0f, 0.0f)),
m_explosionTimer(0),
m_isExploding(false),
m_explosionSprite(sf::Sprite(AssetLoader::getInstance()->m_explosion1))
{
	m_sprite = sf::Sprite(AssetLoader::getInstance()->m_missile);
	m_explosionSprite.setPosition(sf::Vector2f(99999, 99999));

	m_width = m_sprite.getTexture()->getSize().x / 2;
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

		if (m_ttl >= m_maxTTL)
		{
			explode(dt);
			m_isExploding = true;
		}
		else
		{
			if (m_acceleration.x <= MAX_SPEED)
			{
				m_acceleration.x += m_speed;
				m_acceleration.y += m_speed;
			}

			track(playerPos);
			updatePosition();
		}
	}
}

void Missile::draw(sf::RenderWindow& window)
{
	if(m_alive)
		window.draw(m_sprite);
	if (m_isExploding)
		window.draw(m_explosionSprite);
}

void Missile::updatePosition()
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);
}

void Missile::track(sf::Vector2f* playerPos)
{
	m_direction = *playerPos - m_position;
	float _length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / _length, m_direction.y / _length);
	m_velocity = sf::Vector2f(m_direction.x * m_acceleration.x, m_direction.y * m_acceleration.y);

	getNewOrientation();
}

void Missile::explode(float dt)
{
	m_explosionTimer += dt;

	if (m_explosionTimer >= 0.5f && m_explosionTimer < 0.6f)
		m_sprite.setTexture(AssetLoader::getInstance()->m_explosion6);
	else if (m_explosionTimer >= 0.4f && m_explosionTimer < 0.5f)
		m_sprite.setTexture(AssetLoader::getInstance()->m_explosion5);
	else if (m_explosionTimer >= 0.3f && m_explosionTimer < 0.4f)
		m_sprite.setTexture(AssetLoader::getInstance()->m_explosion4);
	else if (m_explosionTimer >= 0.2f && m_explosionTimer < 0.3f)
		m_sprite.setTexture(AssetLoader::getInstance()->m_explosion3);
	else if (m_explosionTimer >= 0.1f && m_explosionTimer < 0.2f)
		m_sprite.setTexture(AssetLoader::getInstance()->m_explosion2);
	else if (m_explosionTimer >= 0 && m_explosionTimer < 0.1f)
        m_sprite.setTexture(AssetLoader::getInstance()->m_explosion1);

	m_sprite.setTextureRect(sf::IntRect(m_sprite.getTextureRect().left, m_sprite.getTextureRect().top, m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y));

	if (m_explosionTimer >= 0.6)
		reset();
}

void Missile::reset()
{
	m_direction = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_position = sf::Vector2f(-9999, -9999);
	m_alive = false;
	m_isExploding = false;
	m_explosionTimer = 0;
	m_sprite.setTexture(AssetLoader::getInstance()->m_missile);
	m_sprite.setTextureRect(sf::IntRect(m_sprite.getTextureRect().left, m_sprite.getTextureRect().top, m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y));
	m_ttl = 0;
}

void Missile::getNewOrientation()
{
	if (sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y)) >= 0)
	{
		m_orientation = atan2(m_direction.x, -m_direction.y) * (180 / 3.141592654);
		m_sprite.setRotation(m_orientation - 90);
	}
}