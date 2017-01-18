#include "stdafx.h"
#include "BulletManager.h"

BulletManager::BulletManager() 
{
	for (int i = 0; i < MAX_BULLETS; i++)
		m_bullets.push_back(Bullet());

	for (int i = 0; i < MAX_MISSILES; i++)
		m_missiles.push_back(Missile());
}

BulletManager::~BulletManager() {}

void BulletManager::update(float dt) {}

void BulletManager::update(float dt, sf::Vector2f* playerPos)
{
	for (int i = 0; i < m_bullets.size(); i++)
		m_bullets[i].update(dt);

	for (int i = 0; i < m_missiles.size(); i++)
		m_missiles[i].update(dt, playerPos);
}

void BulletManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_bullets.size(); i++)
		m_bullets[i].draw(window);

	for (int i = 0; i < m_missiles.size(); i++)
		m_missiles[i].draw(window);
}

Bullet* BulletManager::nextBullet()
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (!m_bullets[i].getAlive())
			return &m_bullets[i];
	}
	return nullptr;
}

Missile* BulletManager::nextMissile()
{
	for (int i = 0; i < m_missiles.size(); i++)
	{
		if (!m_missiles[i].getAlive())
			return &m_missiles[i];
	}
	return nullptr;
}

std::vector<Bullet>* BulletManager::getBullets() { return &m_bullets; }