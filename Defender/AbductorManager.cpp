#include "stdafx.h"
#include "AbductorManager.h"

AbductorManager::AbductorManager(std::vector<Astro>* astros, Player* player, BulletManager* bulletManager):
m_astros(astros),
m_player(player)
{
	for (int i = 0; i < MAX_ABDUCTORS; i++)
		m_abductors.push_back(Abductor(m_player, m_astros, bulletManager));
}

AbductorManager::~AbductorManager() {}

void AbductorManager::update(float dt) 
{
	for (int i = 0; i < m_abductors.size(); i++)
		m_abductors[i].update(dt);
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