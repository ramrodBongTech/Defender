#include "stdafx.h"
#include "GameEntity.h"

GameEntity::GameEntity() :
m_alive(false),
m_position(sf::Vector2f(-999999, -999999)),
m_sprite(sf::Sprite())
{}

GameEntity::~GameEntity() {}

bool GameEntity::getAlive() { return m_alive; }

sf::Vector2f GameEntity::getPosition() { return m_position; }

sf::Sprite* GameEntity::getSprite() { return &m_sprite; }

void GameEntity::setAlive(bool alive) { m_alive = alive; }

void GameEntity::setPosition(sf::Vector2f pos) 
{ 
	m_position = pos; 
	m_sprite.setPosition(pos);
}