#include "stdafx.h"
#include "GameEntity.h"

GameEntity::GameEntity() :
m_alive(false),
m_position(sf::Vector2f(-999999, -999999)),
m_sprite(sf::Sprite()),
m_width(0),
m_height(0)
{}

GameEntity::~GameEntity() {}

bool GameEntity::getAlive() { return m_alive; }

sf::Vector2f GameEntity::getPosition() { return m_position; }

sf::Sprite* GameEntity::getSprite() { return &m_sprite; }

float GameEntity::getWidth() { return m_width; }

float GameEntity::getHeight() { return m_height; }

void GameEntity::setAlive(bool alive) { m_alive = alive; }

void GameEntity::setPosition(sf::Vector2f pos) 
{ 
	m_position = pos; 
	m_sprite.setPosition(pos);
}