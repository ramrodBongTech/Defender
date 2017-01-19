#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(int width, int height) : Scene("Game"),
m_width(width),
m_height(height),
m_gameWorldStart(0),
m_gameWorldEnd(width * 9),
m_ground(sf::VertexArray(sf::PrimitiveType::LineStrip, 10)),
m_player(Player()),
m_cam(Camera(width, height, m_gameWorldStart, m_gameWorldEnd)),
m_radarSprite(sf::Sprite(AssetLoader::getInstance()->m_background)),
m_bulletManager(BulletManager()),
m_abMan(AbductorManager(&m_astronauts, &m_player, &m_bulletManager))
{
	m_radarSprite.setScale(0.5, 0.20);
	createGround();
	createNests();
	InitialiseAstronauts();
	InitialiseRadar();
	m_player.setManager(&m_bulletManager);
}

GameScene::~GameScene()
{}

void GameScene::update(float dt)
{
	m_player.update(dt);

	if (m_player.isSmartBombActivated())
	{
		m_player.resetSmartBomb();
		smartBomb();
	}

	m_cam.move(&m_player);

	if (groundCollision())
	{
		m_player.setVelocity(sf::Vector2f(0, 0));
		m_player.setAcceleration(sf::Vector2f(0, 0));
	}

	for (int i = 0; i < m_astronauts.size(); i++)
		m_astronauts.at(i).update(dt);

	for (int i = 0; i < m_nests.size(); i++)
		m_nests.at(i).update(dt);

	m_abMan.update(dt);

	m_bulletManager.update(dt, &m_player.getPosition());
}

void GameScene::draw(sf::RenderWindow& window)
{
	m_cam.draw(window);

	drawRadar(window);

	window.draw(m_ground);

	m_player.draw(window);

	for (int i = 0; i < m_astronauts.size(); i++)
		m_astronauts.at(i).draw(window);

	for (int i = 0; i < m_nests.size(); i++)
		m_nests.at(i).draw(window);

	m_abMan.draw(window);

	m_bulletManager.draw(window);

	
}

void GameScene::createGround()
{
	for (int i = 0; i < m_ground.getVertexCount(); i++)
	{
		int _randY = (rand() % 150) + 400;
		m_ground[i].position = sf::Vector2f(m_gameWorldStart + (m_width * i), _randY);
		m_ground[i].color = sf::Color::Yellow;
	}
}

void GameScene::createNests()
{
	for (int i = 0; i < MAX_NUMBER_NESTS; i++)
		m_nests.push_back(AlienNest(&m_player, &m_astronauts, &m_abMan, &m_bulletManager));
}

bool GameScene::groundCollision()
{
	std::vector<sf::Vector2f> _playerPoints;

	_playerPoints.push_back(sf::Vector2f(m_player.getPosition().x - m_player.getWidth(), m_player.getPosition().y - m_player.getHeight()));
	_playerPoints.push_back(sf::Vector2f(m_player.getPosition().x + m_player.getWidth(), m_player.getPosition().y - m_player.getHeight()));
	_playerPoints.push_back(sf::Vector2f(m_player.getPosition().x - m_player.getWidth(), m_player.getPosition().y + m_player.getHeight()));
	_playerPoints.push_back(sf::Vector2f(m_player.getPosition().x + m_player.getWidth(), m_player.getPosition().y + m_player.getHeight()));

	for (int i = 0; i < m_ground.getVertexCount() - 1; i++)
	{
		sf::Vector2f _groundA = m_ground[i].position;
		sf::Vector2f _groundB = m_ground[i + 1].position;

		if (m_player.getPosition().x >= _groundA.x && m_player.getPosition().x <= _groundB.x)
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

void GameScene::drawRadar(sf::RenderWindow& window)
{
	int widthdiv = 9;
	double heightdiv = 0.2f;

	sf::Vector2f screenPos = sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y - window.getSize().y / 2);
	
	m_radarBounds.setPosition(sf::Vector2f(window.getView().getCenter().x - (m_radarBounds.getSize().x / 2), 1));
	window.draw(m_radarBounds);

	m_radarSprite.setPosition(m_radarBounds.getPosition());
	window.draw(m_radarSprite);

	sf::VertexArray gr = m_ground;
	for (int i = 0; i < gr.getVertexCount(); i++) {
		gr[i].position = sf::Vector2f( m_radarBounds.getPosition().x + ( (gr[i].position.x / m_radarBounds.getSize().x * 28.5)  )  , ((gr[i].position.y / m_radarBounds.getSize().y) + m_radarBounds.getPosition().y) + (0.8f * m_radarBounds.getSize().y));
	}
	window.draw(gr);

	sf::RectangleShape p = sf::RectangleShape();
	p.setPosition(sf::Vector2f( m_radarBounds.getPosition().x + (m_player.getPosition().x / m_radarBounds.getSize().x * 28.5), (m_player.getPosition().y / m_radarBounds.getSize().y * 28.5) + m_radarBounds.getPosition().y) );
	p.setSize(sf::Vector2f(m_player.getWidth() * heightdiv, m_player.getHeight() * heightdiv));
	p.setFillColor(sf::Color::Green);
	window.draw(p);

	for (int i = 0; i < m_nests.size(); i++)
	{
		if (m_nests[i].getAlive())
		{
			sf::RectangleShape n = sf::RectangleShape();
			n.setPosition(sf::Vector2f(m_radarBounds.getPosition().x + (m_nests[i].getPosition().x / m_radarBounds.getSize().x * 28.5 ), (m_nests[i].getPosition().y / m_radarBounds.getSize().y * 28.5) + m_radarBounds.getPosition().y));
			n.setFillColor(sf::Color::Red);
			n.setSize(sf::Vector2f(m_nests[i].getSprite()->getTexture()->getSize().x * heightdiv, m_nests[i].getSprite()->getTexture()->getSize().y * heightdiv));
			window.draw(n);
		}
	}

	vector<Abductor>* _abductors = m_abMan.getAbductors();
	for (int i = 0; i < _abductors->size(); i++)
	{
		if (_abductors->at(i).getAlive())
		{
			sf::RectangleShape ab = sf::RectangleShape();
			ab.setPosition(sf::Vector2f(m_radarBounds.getPosition().x + (_abductors->at(i).getPosition().x / m_radarBounds.getSize().x * 28.5), (_abductors->at(i).getPosition().y / m_radarBounds.getSize().y * 28.5) + m_radarBounds.getPosition().y));
			ab.setFillColor(sf::Color::White);
			ab.setSize(sf::Vector2f(_abductors->at(i).getSprite()->getTexture()->getSize().x * heightdiv, _abductors->at(i).getSprite()->getTexture()->getSize().y * heightdiv));
			window.draw(ab);
		}
	}

	for (int i = 0; i < m_astronauts.size(); i++)
	{
		if (m_astronauts[i].getAlive())
		{
			sf::RectangleShape a = sf::RectangleShape();
			a.setPosition(sf::Vector2f(m_radarBounds.getPosition().x + (m_astronauts[i].getPosition().x / m_radarBounds.getSize().x * 28.5), ( m_astronauts[i].getPosition().y / (m_radarBounds.getSize().y) + m_radarBounds.getPosition().y) + (0.8f * m_radarBounds.getSize().y) ));
			if (!m_astronauts[i].isMutant())
				a.setFillColor(sf::Color::Magenta);
			else
				a.setFillColor(sf::Color::Cyan);
			a.setSize(sf::Vector2f(m_astronauts[i].getSprite()->getTexture()->getSize().x * heightdiv, m_astronauts[i].getSprite()->getTexture()->getSize().y * heightdiv));
			window.draw(a);
		}
	}
}

void GameScene::InitialiseAstronauts() 
{
	const int _NUMBEROFASTRONAUTS = 10;
	for (int i = 0; i < _NUMBEROFASTRONAUTS; i++)
	{
		sf::Vector2f _position(rand() % ( (- m_gameWorldStart )+ m_gameWorldEnd) + (m_gameWorldStart), 0.9 * m_height);

		int _direction = rand() % 2;
		if (_direction == 0) _direction = -1;

		Astro _astro(_position, _direction, m_gameWorldStart, m_gameWorldEnd, &m_player);
		m_astronauts.push_back(_astro);
	}
}

void GameScene::smartBomb()
{
	for (int i = 0; i < m_astronauts.size(); i++)
	{
		if (m_astronauts[i].isMutant())
			m_astronauts[i].setAlive(false);
	}

	for (int i = 0; i < m_nests.size(); i++)
		m_nests[i].setAlive(false);

	vector<Abductor>* _abductors = m_abMan.getAbductors();
	for (int i = 0; i < _abductors->size(); i++)
		_abductors->at(i).setAlive(false);
}

void GameScene::InitialiseRadar() {
	m_radarBounds.setSize(sf::Vector2f(600, 120));
	m_radarBounds.setFillColor(sf::Color::Transparent);
	m_radarBounds.setOutlineThickness(1);
	m_radarBounds.setOutlineColor(sf::Color::White);
}