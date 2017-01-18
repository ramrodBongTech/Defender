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
	m_playerLeft.setSmooth(true);

	if (!m_playerRight.loadFromFile("Assets/Textures/playerRight.png"))
		std::cout << "PlayerRight image not loading" << std::endl;
	m_playerRight.setSmooth(true);

	// Load in the background texture
	if (!m_background.loadFromFile("Assets/Textures/grid.png")) 
		std::cout << "Error Loading Grid Textures" << std::endl;
	m_background.setSmooth(true);

	// Load in the bullet texture
	if (!m_bullet.loadFromFile("Assets/Textures/bullet.png"))
		std::cout << "Bullet image not loading" << std::endl;
	m_bullet.setSmooth(true);

	// Load in the missile texture
	if (!m_missile.loadFromFile("Assets/Textures/missile.png"))
		std::cout << "Missile image not loading" << std::endl;
	m_missile.setSmooth(true);

	// Load in the astronaut textures
	if (!m_astronautLeft.loadFromFile("Assets/Textures/astronautLeft.png"))
		std::cout << "AstronautLeft image not loading" << std::endl;
	m_astronautLeft.setSmooth(true);

	if (!m_astronautRight.loadFromFile("Assets/Textures/astronautRight.png"))
		std::cout << "AstronautRight image not loading" << std::endl;
	m_astronautRight.setSmooth(true);

	// Load in the alien nest textures
	if (!m_alienNestLeft.loadFromFile("Assets/Textures/alienNestLeft.png"))
		std::cout << "Alien Nest Left image not loading" << std::endl;
	m_alienNestLeft.setSmooth(true);

	if (!m_alienNestRight.loadFromFile("Assets/Textures/alienNestRight.png"))
		std::cout << "Alien Nest Right image not loading" << std::endl;
	m_alienNestRight.setSmooth(true);

	// Load in the alien abductor textures
	if (!m_abductorLeft.loadFromFile("Assets/Textures/abductorLeft.png"))
		std::cout << "Abductor Left image not loading" << std::endl;
	m_abductorLeft.setSmooth(true);

	if (!m_abductorRight.loadFromFile("Assets/Textures/abductorRight.png"))
		std::cout << "Abductor Right image not loading" << std::endl;
	m_abductorRight.setSmooth(true);

	// Load in the mutant textures
	if (!m_mutantLeft.loadFromFile("Assets/Textures/mutantLeft.png"))
		std::cout << "Mutant Left image not loading" << std::endl;
	m_mutantLeft.setSmooth(true);

	if (!m_mutantRight.loadFromFile("Assets/Textures/mutantRight.png"))
		std::cout << "Mutant Right image not loading" << std::endl;
	m_mutantRight.setSmooth(true);

}

void AssetLoader::loadSounds()
{

}