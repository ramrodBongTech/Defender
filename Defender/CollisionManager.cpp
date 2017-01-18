#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager(Player* player, std::vector<PowerUp>* powerUps):
m_player(player),
m_powerUps(powerUps)
{}

CollisionManager::~CollisionManager() {}

void CollisionManager::update() 
{
	Player_PowerUp_Collision();
}

bool CollisionManager::collide(sf::Sprite* s1, sf::Sprite* s2)
{
	sf::FloatRect r1 = s1->getGlobalBounds();
	sf::FloatRect r2 = s2->getGlobalBounds();
	bool c = r1.intersects(r2);
	return c;
}

void CollisionManager::Player_PowerUp_Collision()
{
	for (int i = 0; i < m_powerUps->size(); i++)
	{
		PowerUp* p = &m_powerUps->at(i);
		if (p->getAlive())
		{
			if (collide(p->getSprite(), m_player->getSprite()))
			{
				m_player->pickedUpHyperJump();
				p->reset();
			}
		}
	}
}

void CollisionManager::Player_Ground_Collision() {}

void CollisionManager::Player_Bullet_Collision() {}

void CollisionManager::Player_Missile_Collision() {}

void CollisionManager::Player_Nest_Collision() {}

void CollisionManager::Player_Abductor_Collision() {}

void CollisionManager::Player_Mutant_Collision() {}

void CollisionManager::Bullet_Nest_Collision() {}

void CollisionManager::Bullet_Abductor_Collision() {}

void CollisionManager::Bullet_Mutant_Collision() {}