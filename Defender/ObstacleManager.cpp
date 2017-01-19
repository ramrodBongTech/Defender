#include "stdafx.h"
#include "ObstacleManager.h"

ObstacleManager::ObstacleManager() 
{
	for (int i = 0; i < MAX_OBSTACLES; i++)
		m_obstacles.push_back(Obstacle());
}

ObstacleManager::~ObstacleManager() {}

void ObstacleManager::update(float dt) 
{
	m_spawnTimer += dt;
	for (int i = 0; i < m_obstacles.size(); i++)
		//m_obstacles[i].update(dt);
	if (m_spawnTimer >= MAX_SPAWN_TIME)
		spawnObstacle();
}

void ObstacleManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i].draw(window);
}

std::vector<Obstacle>*	ObstacleManager::getObstacles() { return &m_obstacles; }

void ObstacleManager::spawnObstacle() 
{
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		if (!m_obstacles[i].getAlive())
		{
			m_obstacles[i].setAlive(true);
			//m_obstacles[i].setPosition(sf::Vector2f(rand() % 10800, (rand() % 100) - 200));
			m_obstacles[i].setPosition(sf::Vector2f(rand() % 5400, 300));
			break;
		}
	}
	m_spawnTimer = -360;
}