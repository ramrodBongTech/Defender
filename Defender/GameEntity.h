#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

#include "AssetLoader.h"

class GameEntity
{
public:
	GameEntity();
	~GameEntity();

	bool getAlive();
	sf::Vector2f getPosition();
	sf::Sprite getSprite();

	void setPosition(sf::Vector2f pos);

	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	bool			m_alive;
	sf::Vector2f	m_position;
	sf::Sprite		m_sprite;
};

#endif