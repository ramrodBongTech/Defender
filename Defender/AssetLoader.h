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

	sf::Texture		m_abductorsLeft;
	sf::Texture		m_abductorsRight;

	sf::Texture		m_mutantLeft;
	sf::Texture		m_mutantRight;

private:
	void loadTextures();
	void loadSounds();

	static AssetLoader*		m_instance;
};

#endif