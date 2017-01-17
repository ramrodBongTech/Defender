#include "stdafx.h"
#include "BulletFactory.h"

BulletFactory* BulletFactory::m_instance = 0;

BulletFactory* BulletFactory::getInstance()
{
	if (m_instance == 0)
		m_instance = new BulletFactory();

	return m_instance;
}

BulletFactory::BulletFactory() {}

BulletFactory::~BulletFactory() {}

Bullet* BulletFactory::getBullet() 
{
	Bullet* _bullet = 0;
	_bullet = new Bullet();
	return _bullet;
}