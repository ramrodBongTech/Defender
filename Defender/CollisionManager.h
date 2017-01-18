#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Player.h"
#include "PowerUp.h"

class CollisionManager
{
public:
	CollisionManager(Player* player, std::vector<PowerUp>* powerUps);
	~CollisionManager();

	void update();
	
private:
	Player*					m_player;
	std::vector<PowerUp>*	m_powerUps;

	bool collide(sf::Sprite* s1, sf::Sprite* s2);
	void Player_PowerUp_Collision();
	void Player_Ground_Collision();
	void Player_Bullet_Collision();
	void Player_Missile_Collision();
	void Player_Nest_Collision();
	void Player_Abductor_Collision();
	void Player_Mutant_Collision();
	void Bullet_Nest_Collision();
	void Bullet_Abductor_Collision();
	void Bullet_Mutant_Collision();

};

#endif