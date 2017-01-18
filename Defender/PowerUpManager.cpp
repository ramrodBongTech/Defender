#include "stdafx.h"
#include "PowerUpManager.h"

PowerUpManager::PowerUpManager(): m_spawnTimer(0)
{
	for (int i = 0; i < MAX_POWER_UPS; i++)
		m_powerUps.push_back(PowerUp());
}

PowerUpManager::~PowerUpManager() {}

void PowerUpManager::update(float dt)
{
	m_spawnTimer += dt;
	for (int i = 0; i < m_powerUps.size(); i++)
		m_powerUps[i].update(dt);
	if (m_spawnTimer >= MAX_SPAWN_TIME)
		spawnPowerUp();
}

void PowerUpManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_powerUps.size(); i++)
		m_powerUps[i].draw(window);
}

std::vector<PowerUp>* PowerUpManager::getPowerUps() { return &m_powerUps; }

void PowerUpManager::spawnPowerUp()
{
	for (int i = 0; i < m_powerUps.size(); i++)
	{
		if (!m_powerUps[i].getAlive())
		{
			m_powerUps[i].setAlive(true);
			m_powerUps[i].setPosition(sf::Vector2f(rand() % 10800, rand() % 400));
			break;
		}
	}
	m_spawnTimer = 0;
}