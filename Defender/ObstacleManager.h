#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H

#include "Obstacle.h"

class ObstacleManager
{
public:
	ObstacleManager();
	~ObstacleManager();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	std::vector<Obstacle>*	getObstacles();

private:
	std::vector<Obstacle>	m_obstacles;
	float					m_spawnTimer;

	void spawnObstacle();

	const int MAX_OBSTACLES = 20;
	const int MAX_SPAWN_TIME = 2;
};

#endif