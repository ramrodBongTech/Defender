#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager(Player* player, std::vector<PowerUp>* powerUps, std::vector<Bullet>* bullets, std::vector<Missile>* missiles, std::vector<AlienNest>* nests):
m_player(player),
m_powerUps(powerUps),
m_bullets(bullets),
m_missiles(missiles),
m_nests(nests)
{}

CollisionManager::~CollisionManager() {}

void CollisionManager::update() 
{
	Bullet_Collisions();
	Player_PowerUp_Collision();
	Player_Missile_Collision();
	Player_Nest_Collision();
	Player_Abductor_Collision();
	Player_Mutant_Collision();
}

bool CollisionManager::collide(sf::Sprite* s1, sf::Sprite* s2)
{
	sf::FloatRect _r1 = s1->getGlobalBounds();
	sf::FloatRect _r2 = s2->getGlobalBounds();
	return _r1.intersects(_r2);
}

void CollisionManager::Bullet_Collisions()
{
	for (int i = 0; i < m_bullets->size(); i++)
	{
		Bullet* _b = &m_bullets->at(i);
		if (_b->getAlive())
		{
			if (!_b->isPlayerBullet())
			{
				if (collide(_b->getSprite(), m_player->getSprite()))
				{
					m_player->takeDamage(_b->getDamage());
					_b->reset();
				}
			}
			else
			{
				// Loop through all of the aliens
			}
		}
	}
}

void CollisionManager::Player_PowerUp_Collision()
{
	for (int i = 0; i < m_powerUps->size(); i++)
	{
		PowerUp* _p = &m_powerUps->at(i);
		if (_p->getAlive())
		{
			if (collide(_p->getSprite(), m_player->getSprite()))
			{
				m_player->pickedUpHyperJump();
				_p->reset();
			}
		}
	}
}

void CollisionManager::Player_Missile_Collision() 
{
	for (int i = 0; i < m_missiles->size(); i++)
	{
		Missile *_m = &m_missiles->at(i);
		if (_m->getAlive())
		{
			if (collide(_m->getSprite(), m_player->getSprite()))
			{
				m_player->takeDamage(_m->getDamage());
				_m->reset();
			}
		}
	}
}

void CollisionManager::Player_Nest_Collision() 
{
	for (int i = 0; i < m_nests->size(); i++)
	{
		AlienNest*_n = &m_nests->at(i);
		if (_n->getAlive())
		{
			if (collide(_n->getSprite(), m_player->getSprite()))
			{
				m_player->takeDamage(_n->getDamage());
				_n->reset();
			}
		}
	}
}

void CollisionManager::Player_Abductor_Collision() {}

void CollisionManager::Player_Mutant_Collision() {}