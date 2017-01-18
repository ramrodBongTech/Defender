#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "Bullet.h"
#include "Missile.h"

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void update(float dt);
	void update(float dt, sf::Vector2f playerPos);
	void draw(sf::RenderWindow& window);

	Bullet* nextBullet();
	Missile* nextMissile();

private:
	std::vector<Bullet>			m_bullets;
	std::vector<Missile>		m_missiles;

	const int MAX_BULLETS = 200;
	const int MAX_MISSILES = 30;
};

#endif