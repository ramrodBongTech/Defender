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

	// Load in the missile texture
	if (!m_missile.loadFromFile("Assets/Textures/missile.png"))
		std::cout << "Missile image not loading" << std::endl;

	// Load in the astronaut textures
	if (!m_astronautLeft.loadFromFile("Assets/Textures/astronautLeft.png"))
		std::cout << "AstronautLeft image not loading" << std::endl;

	if (!m_astronautRight.loadFromFile("Assets/Textures/astronautRight.png"))
		std::cout << "AstronautRight image not loading" << std::endl;

	// Load in the alien nest textures
	if (!m_alienNestLeft.loadFromFile("Assets/Textures/alienNestLeft.png"))
		std::cout << "Alien Nest Left image not loading" << std::endl;

	if (!m_alienNestRight.loadFromFile("Assets/Textures/alienNestRight.png"))
		std::cout << "Alien Nest Right image not loading" << std::endl;

	// Load in the alien abductor textures
	if (!m_abductorLeft.loadFromFile("Assets/Textures/abductorLeft.png"))
		std::cout << "Abductor Left image not loading" << std::endl;

	if (!m_abductorRight.loadFromFile("Assets/Textures/abductorRight.png"))
		std::cout << "Abductor Right image not loading" << std::endl;

	// Load in the mutant textures
}

void AssetLoader::loadSounds()
{

}