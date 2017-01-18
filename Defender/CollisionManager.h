#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Player.h"
#include "PowerUp.h"
#include "Missile.h"
#include "AlienNest.h"

class CollisionManager
{
public:
	CollisionManager(Player* player, std::vector<PowerUp>* powerUps, std::vector<Bullet>* bullets, std::vector<Missile>* missiles, std::vector<AlienNest>* nests, std::vector<Abductor>* abductors);
	~CollisionManager();

	void update();
	
private:
	Player*							m_player;
	std::vector<PowerUp>*			m_powerUps;
	std::vector<Bullet>*			m_bullets;
	std::vector<Missile>*			m_missiles;
	std::vector<AlienNest>*			m_nests;
	std::vector<Abductor>*			m_abductors;
	//std::vector<Astro>*			m_astronauts;

	bool collide(sf::Sprite* s1, sf::Sprite* s2);

	void Bullet_Collisions();
	void Player_PowerUp_Collision();
	void Player_Missile_Collision();
	void Player_Nest_Collision();
	void Player_Abductor_Collision();
	void Player_Mutant_Collision();
};

#endif