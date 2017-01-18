#include "stdafx.h"
#include "PowerUp.h"

PowerUp::PowerUp(): GameEntity(),
m_type(PowerUpType::HYPERJUMP)
{
	int _numTypes = 1;
	if (rand() % _numTypes - 1 == 0)
		m_type == PowerUpType::HYPERJUMP;
	m_sprite = sf::Sprite(AssetLoader::getInstance()->m_powerUp);
}

PowerUp::~PowerUp() {}

void PowerUp::update(float dt) {}

void PowerUp::draw(sf::RenderWindow& window)
{ 
	if (m_alive) 
		window.draw(m_sprite);
}