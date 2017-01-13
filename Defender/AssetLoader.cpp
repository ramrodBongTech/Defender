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
	{
		m_instance = new AssetLoader();
	}
	return m_instance;
}

void AssetLoader::loadTextures()
{
	// Load in the player textures
	if (!m_playerLeft.loadFromFile("Assets/Textures/playerLeft.png"))
		std::cout << "PlayerLeft image not loading" << std::endl;

	if (!m_playerRight.loadFromFile("Assets/Textures/playerRight.png"))
		std::cout << "PlayerRight image not loading" << std::endl;

	// Load in the astronaut textures
	if (!m_astronautLeft.loadFromFile("Assets/Textures/astronautLeft.png"))
		std::cout << "AstronautLeft image not loading" << std::endl;

	if (!m_astronautLeft.loadFromFile("Assets/Textures/astronautRight.png"))
		std::cout << "AstronautRight image not loading" << std::endl;

	// Load in the alien nest textures

	// Load in the alien abductor textures

	// Load in the mutant textures
}

void AssetLoader::loadSounds()
{

}