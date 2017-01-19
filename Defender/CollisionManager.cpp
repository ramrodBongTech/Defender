#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager(Player* player, std::vector<PowerUp>* powerUps, std::vector<Bullet>* bullets, std::vector<Missile>* missiles, std::vector<AlienNest>* nests, std::vector<Abductor>* abductors, std::vector<Astro>* astronauts):
m_player(player),
m_powerUps(powerUps),
m_bullets(bullets),
m_missiles(missiles),
m_nests(nests),
m_abductors(abductors),
m_astronauts(astronauts)
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
				// Nests
				for (int i = 0; i < m_nests->size(); i++)
				{
					AlienNest*_n = &m_nests->at(i);
					if (_n->getAlive())
					{
						if (collide(_n->getSprite(), _b->getSprite()))
						{
							_n->takeDamage(_b->getDamage());
							_b->reset();
						}
					}
				}

				// Abductors
				if (_b->getAlive())
				{
					for (int i = 0; i < m_abductors->size(); i++)
					{
						Abductor* _ab = &m_abductors->at(i);
						if (_ab->getAlive())
						{
							if (collide(_ab->getSprite(), _b->getSprite()))
							{
								_ab->takeDamage(_b->getDamage());
								_b->reset();
							}
						}
					}
				}

				// Mutants
				if (_b->getAlive())
				{
					for (int i = 0; i < m_astronauts->size(); i++)
					{
						Astro* _as = &m_astronauts->at(i);
						if (_as->getAlive() && _as->isMutant())
						{
							if (collide(_as->getSprite(), _b->getSprite()))
							{
								_as->takeDamage(_b->getDamage());
								_b->reset();
							}
						}
					}
				}
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

void CollisionManager::Player_Abductor_Collision() 
{
	for (int i = 0; i < m_abductors->size(); i++)
	{
		Abductor* _ab = &m_abductors->at(i);
		if (_ab->getAlive())
		{
			if (collide(_ab->getSprite(), m_player->getSprite()))
			{
				m_player->takeDamage(_ab->getDamage());
				_ab->reset();
			}
		}
	}
}

void CollisionManager::Player_Mutant_Collision() 
{
	for (int i = 0; i < m_astronauts->size(); i++)
	{
		Astro* _as = &m_astronauts->at(i);
		if (_as->getAlive() && _as->isMutant())
		{
			if (collide(_as->getSprite(), m_player->getSprite()))
			{
				m_player->takeDamage(_as->getDamage());
				_as->reset();
			}
		}
	}
}