#include "stdafx.h"
#include "AssetLoader.h"

AssetLoader* AssetLoader::m_instance = 0;

AssetLoader::AssetLoader()
{
	loadTextures();
	loadSounds();
}

AssetLoader* AssetLoader::getInstance()
{
	if (m_instance == 0)
		m_instance = new AssetLoader();

	return m_instance;
}

void AssetLoader::loadTextures()
{
	// Load in the player textures
	if (!m_playerLeft.loadFromFile("Assets/Textures/playerLeft.png"))
		std::cout << "PlayerLeft image not loading" << std::endl;

	if (!m_playerRight.loadFromFile("Assets/Textures/playerRight.png"))
		std::cout << "PlayerRight image not loading" << std::endl;

	// Load in the background texture
	if (!m_background.loadFromFile("Assets/Textures/grid.png")) 
		std::cout << "Error Loading Grid Textures" << std::endl;

	// Load in the bullet texture
	if (!m_bullet.loadFromFile("Assets/Textures/bullet.png"))
		std::cout << "Bullet image not loading" << std::endl;

	// Load in the astronaut textures

	// Load in the alien nest textures

	// Load in the alien abductor textures

	// Load in the mutant textures
}

void AssetLoader::loadSounds()
{

}