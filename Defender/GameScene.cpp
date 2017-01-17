#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(int width, int height) : Scene("Game"),
m_width(width),
m_height(height),
m_gameWorldStart(-(width * 4)),
m_gameWorldEnd(width * 5),
m_ground(sf::VertexArray(sf::PrimitiveType::LineStrip, 10))
{
	m_player = new Player();
	m_cam = new Camera(width, height, m_gameWorldStart, m_gameWorldEnd);
	createGround();
	InitialiseAstronauts(height);
}

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

	if (groundCollision())
	{
		m_player->setVelocity(sf::Vector2f(0, 0));
		m_player->setAcceleration(sf::Vector2f(0, 0));
	}

	for (int i = 0; i < m_astronauts.size(); i++)
		m_astronauts.at(i).update(dt);
}

void GameScene::draw(sf::RenderWindow& window)
{
	window.draw(m_ground);
	m_player->draw(window);
	m_cam->draw(window);
	for (int i = 0; i < m_astronauts.size(); i++)
		m_astronauts.at(i).draw(window);
}

void GameScene::createGround()
{
	int _randY = (rand() % 200) + 300;

	m_ground[0].position = sf::Vector2f(-(m_width * 4), _randY);

	_randY = (rand() % 200) + 300;

	m_ground[1].position = sf::Vector2f(-(m_width * 3), _randY);

	_randY = (rand() % 200) + 300;

	m_ground[2].position = sf::Vector2f(-(m_width * 2), _randY);

	_randY = (rand() % 200) + 300;

	m_ground[3].position = sf::Vector2f(-(m_width), _randY);

	_randY = (rand() % 200) + 300;

	m_ground[4].position = sf::Vector2f(0, _randY);

	_randY = (rand() % 200) + 300;

	m_ground[5].position = sf::Vector2f(m_width, _randY);

	_randY = (rand() % 200) + 300;

	m_ground[6].position = sf::Vector2f(m_width * 2, _randY);

	_randY = (rand() % 200) + 300;

	m_ground[7].position = sf::Vector2f(m_width * 3, _randY);

	_randY = (rand() % 200) + 300;

	m_ground[8].position = sf::Vector2f(m_width * 4, _randY);

	_randY = (rand() % 200) + 300;

	m_ground[9].position = sf::Vector2f(m_width * 5, _randY);

	for (int i = 0; i < m_ground.getVertexCount(); i++)
	{
		m_ground[i].color = sf::Color::Yellow;
	}
}

bool GameScene::groundCollision()
{
	std::vector<sf::Vector2f> _playerPoints;

	_playerPoints.push_back(sf::Vector2f(m_player->getPosition().x - m_player->getWidth(), m_player->getPosition().y - m_player->getWidth()));
	_playerPoints.push_back(sf::Vector2f(m_player->getPosition().x + m_player->getWidth(), m_player->getPosition().y - m_player->getWidth()));
	_playerPoints.push_back(sf::Vector2f(m_player->getPosition().x - m_player->getWidth(), m_player->getPosition().y + m_player->getWidth()));
	_playerPoints.push_back(sf::Vector2f(m_player->getPosition().x + m_player->getWidth(), m_player->getPosition().y + m_player->getWidth()));

	for (int i = 0; i < m_ground.getVertexCount() - 1; i++)
	{
		sf::Vector2f _groundA = m_ground[i].position;
		sf::Vector2f _groundB = m_ground[i + 1].position;

		if (m_player->getPosition().x >= _groundA.x && m_player->getPosition().x <= _groundB.x)
		{
			sf::Vector2f _B = sf::Vector2f(-(_groundB - _groundA).y, (_groundB - _groundA).x);
			_B = _B / sqrt(_B.x * _B.x + _B.y * _B.y);

			float _d = _B.x * _playerPoints[0].x + _B.y * _playerPoints[0].y;
			float _minA = _d;
			float _maxA = _d;
			for (int j = 1; j < _playerPoints.size(); j++)
			{
				_d = _B.x * _playerPoints[j].x + _B.y * _playerPoints[j].y;
				if (_minA > _d)
					_minA = _d;

				if (_maxA < _d)
					_maxA = _d;
			}
			
			_d = _B.x * _groundA.x + _B.y * _groundA.y;
			float _minB = _d;
			float _maxB = _d;

			_d = _B.x * _groundB.x + _B.y * _groundB.y;
			if (_minB > _d)
				_minB = _d;

			if (_maxB < _d)
				_maxB = _d;

			if (_minA > _maxB || _minB > _maxA)
				return false;

			break;
		}
	}
	return true;
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
	}
}