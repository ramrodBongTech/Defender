#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(int width, int height) : Scene("Game"),
m_player(new Player()),
m_cam(new Camera(width, height))
{}

GameScene::~GameScene()
{
	delete m_player;
	m_player = nullptr;
	delete m_cam;
	m_cam = nullptr;
}

void GameScene::update(float dt)
{
	m_player->update(dt);
	m_cam->move(m_player);
}

void GameScene::draw(sf::RenderWindow& window)
{
	m_player->draw(window);
	m_cam->draw(window);
}