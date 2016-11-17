#include "stdafx.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene() : Scene("GameOver")
{}

GameOverScene::~GameOverScene()
{}

void GameOverScene::update(float dt)
{

}

void GameOverScene::draw(sf::RenderWindow& window)
{
	if (m_alive)
	{
		std::cout << "GAMEOVER SCREEN!!" << std::endl;
	}
	m_alive = false;
}