#include "stdafx.h"
#include "GameEntity.h"

GameEntity::GameEntity() {}

GameEntity::~GameEntity() {}

bool GameEntity::getAlive() { return m_alive; }

sf::Vector2f GameEntity::getPosition() { return m_position; }

void GameEntity::setPosition(sf::Vector2f pos) { m_position = pos; }

sf::Sprite GameEntity::getSprite() { return m_sprite; }