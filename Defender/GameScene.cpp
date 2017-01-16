#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(int width, int height) : Scene("Game")
{
	m_gameWorldStart = -(width * 4);
	m_gameWorldEnd = width * 5;
	m_player = new Player(0.1, sf::Vector2f(400, 300), m_gameWorldStart, m_gameWorldEnd);
	m_cam = new Camera(width, height, m_gameWorldStart, m_gameWorldEnd);
	InitialiseAstronauts(height);
}

GameScene::~GameScene()
{
	delete m_player;
	m_player = nullptr;
}

void GameScene::update(float dt)
{
	m_player->update(dt);
	m_cam->move(m_player);
	for (int i = 0; i < m_astronauts.size(); i++)
		m_astronauts.at(i).update(dt);
}

void GameScene::draw(sf::RenderWindow& window)
{
	m_player->draw(window);
	m_cam->draw(window);
	for (int i = 0; i < m_astronauts.size(); i++)
		m_astronauts.at(i).draw(window);
}

void GameScene::InitialiseAstronauts(int screenHeight) 
{
	const int _NUMBEROFASTRONAUTS = 10;
	for (int i = 0; i < _NUMBEROFASTRONAUTS; i++)
	{
		sf::Vector2f _position(rand() % ( (- m_gameWorldStart )+ m_gameWorldEnd) + (m_gameWorldStart), 0.9 * screenHeight);

		int _direction = rand() % 2;
		if (_direction == 0) _direction = -1;

		Astronaut _astro(_position, _direction, m_gameWorldStart, m_gameWorldEnd);
		m_astronauts.push_back(_astro);
		cout << m_astronauts.at(i).getPosition().x << endl;
	}
}