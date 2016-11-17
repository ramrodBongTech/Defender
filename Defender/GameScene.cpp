#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() : Scene("Game")
{
	m_player = new Player();
}

GameScene::~GameScene()
{
	delete m_player;
	m_player = nullptr;
}

void GameScene::update(float dt)
{
	m_player->update(dt);
}

void GameScene::draw(sf::RenderWindow& window)
{
	if (m_alive)
	{
		std::cout << "GAME SCREEN!!" << std::endl;
	}
	m_alive = false;

	m_player->draw(window);
}