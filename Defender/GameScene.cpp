#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() : Scene("Game")
{}

GameScene::~GameScene()
{}

void GameScene::update(float dt)
{}

void GameScene::draw(sf::RenderWindow& window)
{
	if (m_alive)
	{
		std::cout << "GAME SCREEN!!" << std::endl;
	}
	m_alive = false;
}