#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H

#include "Bullet.h"

class BulletFactory
{
public:
	static BulletFactory* getInstance();

	BulletFactory();
	~BulletFactory();

	Bullet* getBullet();

private:
	static BulletFactory*		m_instance;

};

#endif