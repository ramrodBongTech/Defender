#include "stdafx.h"
#include "AlienNestManager.h"

AlienNestManager::AlienNestManager(Player* player, std::vector<Astro>* astros, AbductorManager* abMan, BulletManager* bulletManager, std::vector<Obstacle>* obstacles)
{
	for (int i = 0; i < MAX_NESTS; i++)
		m_nests.push_back(AlienNest(player, astros, abMan, bulletManager, obstacles));
}

AlienNestManager::~AlienNestManager() {}

void AlienNestManager::update(float dt)
{
	m_spawnTimer += dt;
	if (m_spawnTimer >= MAX_SPAWN_TIME)
		spawnNest();

	for (int i = 0; i < m_nests.size(); i++)
		m_nests[i].update(dt);
}

void AlienNestManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_nests.size(); i++)
		m_nests[i].draw(window);
}

std::vector<AlienNest>*	AlienNestManager::getNests() { return &m_nests; }

void AlienNestManager::spawnNest()
{
	for (int i = 0; i < m_nests.size(); i++)
	{
		if (!m_nests[i].getAlive())
		{
			m_nests[i].setAlive(true);
			m_nests[i].setPosition(sf::Vector2f(rand() % 10800, rand() % 400));
			break;
		}
	}
	m_spawnTimer = 0;
}