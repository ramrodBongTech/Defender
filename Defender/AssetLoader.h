#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

class AssetLoader
{
public:
	static AssetLoader* getInstance();

	AssetLoader();

	sf::Texture		m_playerLeft;
	sf::Texture		m_playerRight;

	sf::Texture		m_bullet;
	sf::Texture		m_missile;

	sf::Texture		m_background;

	sf::Texture		m_astronautLeft;
	sf::Texture		m_astronautRight;

	sf::Texture		m_alienNestLeft;
	sf::Texture		m_alienNestRight;

	sf::Texture		m_abductorLeft;
	sf::Texture		m_abductorRight;

	sf::Texture		m_mutantLeft;
	sf::Texture		m_mutantRight;

	sf::Texture		m_powerUp;

	sf::Texture		m_explosion1;
	sf::Texture		m_explosion2;
	sf::Texture		m_explosion3;
	sf::Texture		m_explosion4;
	sf::Texture		m_explosion5;
	sf::Texture		m_explosion6;

private:
	void loadTextures();
	void loadSounds();

	static AssetLoader*		m_instance;
};

#endif