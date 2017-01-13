#include "stdafx.h"
#include "Astronaut.h"

Astronaut::Astronaut() : GameEntity()
{
	
}

Astronaut::Astronaut(sf::Vector2f position, int direction) : GameEntity()
{
	m_position = position;
	m_speed = 0.7f;
	m_direction = direction;
	m_velocity =  m_speed * m_direction;

	m_texLeft = &AssetLoader::getInstance()->m_astronautLeft;
	m_texRight = &AssetLoader::getInstance()->m_astronautRight;

	if (m_direction < 0)
		m_sprite.setTexture(*m_texLeft);
	else
		m_sprite.setTexture(*m_texRight);

	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);
}

Astronaut::~Astronaut()
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
}

void Astronaut::update(float dt)
{
	if (isEnemyDetected())
		Evade();
	else
		Wander();
}

void Astronaut::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Astronaut::Wander() 
{
	//to do : boundary checks
	m_sprite.setPosition(m_position);
	m_position.x += m_velocity;
}

void Astronaut::Evade()
{
	m_speed * 2;
}

void Astronaut::WrapAround()
{

}

bool Astronaut::isEnemyDetected() 
{ 
	return false; 
}

