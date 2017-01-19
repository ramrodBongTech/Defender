#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(): GameEntity(),
m_speed(8.0f),
m_direction(sf::Vector2f(0.5f, 0.5f)),
m_velocity(sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed))
{
	m_sprite = sf::Sprite(AssetLoader::getInstance()->m_obstacle);
	m_width = m_sprite.getTexture()->getSize().x / 2;
	m_height = m_sprite.getTexture()->getSize().y / 2;
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(sf::Vector2f(m_width, m_height));
	m_sprite.setScale(2.0f, 2.0f);
	if (rand() % 2 == 0)
		m_velocity.x = -m_velocity.x;
}

Obstacle::~Obstacle() {}

void Obstacle::update(float dt) 
{
	if (m_alive)
	{
		m_position += m_velocity;
		m_sprite.setPosition(m_position);
		if (m_position.y + m_height > 600)
			reset();
	}
}

void Obstacle::draw(sf::RenderWindow& window) 
{
	if (m_alive)
		window.draw(m_sprite);
}

void Obstacle::reset() 
{
	m_position = sf::Vector2f(99999, 99999);
	m_alive = false;
}