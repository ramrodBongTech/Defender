#include "stdafx.h"
#include "PowerUp.h"

PowerUp::PowerUp(): GameEntity(),
m_type(PowerUpType::HYPERJUMP)
{
	int _numTypes = 1;
	if (rand() % _numTypes - 1 == 0)
		m_type = PowerUpType::HYPERJUMP;
	m_sprite = sf::Sprite(AssetLoader::getInstance()->m_powerUp);
	m_sprite.setPosition(m_position);
	m_width = m_sprite.getTexture()->getSize().x / 2;
	m_height = m_sprite.getTexture()->getSize().y / 2;
	m_sprite.setOrigin(sf::Vector2f(m_width, m_height));
}

PowerUp::~PowerUp() {}

void PowerUp::update(float dt) {}

void PowerUp::draw(sf::RenderWindow& window)
{ 
	if (m_alive) 
		window.draw(m_sprite);
}

void PowerUp::reset()
{
	m_alive = false;
	m_position = sf::Vector2f(99999, 99999);
	m_sprite.setPosition(m_position);
}