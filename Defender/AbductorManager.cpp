#include "stdafx.h"
#include "AbductorManager.h"

AbductorManager::AbductorManager(std::vector<Astro>* astros, Player* player, BulletManager* bulletManager, std::vector<Obstacle>* obstacles)
{
	for (int i = 0; i < MAX_ABDUCTORS; i++)
		m_abductors.push_back(Abductor(player, astros, bulletManager, obstacles));
}

AbductorManager::~AbductorManager() {}

void AbductorManager::update(float dt) 
{
	for (int i = 0; i < m_abductors.size(); i++) {
		m_abductors[i].Flock(m_abductors);
		m_abductors[i].update(dt);
	}
}

void AbductorManager::draw(sf::RenderWindow& window) 
{
	for (int i = 0; i < m_abductors.size(); i++)
		m_abductors[i].draw(window);
}

Abductor* AbductorManager::nextAbductor()
{
	for (int i = 0; i < m_abductors.size(); i++) 
	{
		if (!m_abductors[i].getAlive())
			return &m_abductors[i];
	}
	return nullptr;
}

std::vector<Abductor>*	AbductorManager::getAbductors() { return &m_abductors; }