#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(int width, int height) : Scene("Game"),
m_width(width),
m_height(height),
m_screenSizes(9),
m_gameWorldStart(0),
m_gameWorldEnd(width * m_screenSizes),
m_radarMultiplier(0.2),
m_ground(sf::VertexArray(sf::PrimitiveType::LineStrip, 10)),
m_player(Player()),
m_cam(Camera(width, height, m_gameWorldStart, m_gameWorldEnd)),
m_radarSprite(sf::Sprite(AssetLoader::getInstance()->m_background)),
m_bulletManager(BulletManager()),
m_abMan(AbductorManager(&m_astronauts, &m_player, &m_bulletManager)),
m_powerMan(PowerUpManager()),
m_collMan(CollisionManager(&m_player, m_powerMan.getPowerUps(), m_bulletManager.getBullets(), m_bulletManager.getMissiles(), &m_nests))
{
	m_radarSprite.setScale(1, 0.20);
	createGround();
	createNests();
	InitialiseAstronauts();
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

	m_powerMan.update(dt);

	m_collMan.update();
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

	m_powerMan.draw(window);
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
	sf::Vector2f screenPos = sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y - window.getSize().y / 2);

	m_radarSprite.setPosition(screenPos);
	window.draw(m_radarSprite);

	sf::RectangleShape sr = sf::RectangleShape();
	sr.setPosition(sf::Vector2f((screenPos.x / m_screenSizes) + screenPos.x, screenPos.y * m_radarMultiplier));
	sr.setSize(sf::Vector2f(window.getSize().x / m_screenSizes, window.getSize().y * m_radarMultiplier));
	sr.setFillColor(sf::Color::Transparent);
	sr.setOutlineThickness(1);
	sr.setOutlineColor(sf::Color::White);
	window.draw(sr);

	sf::VertexArray gr = m_ground;
	for (int i = 0; i < gr.getVertexCount(); i++)
		gr[i].position = sf::Vector2f((gr[i].position.x / m_screenSizes) + screenPos.x, (gr[i].position.y * m_radarMultiplier));
	window.draw(gr);

	sf::RectangleShape p = sf::RectangleShape();
	p.setPosition(sf::Vector2f((m_player.getPosition().x / m_screenSizes) + screenPos.x, m_player.getPosition().y * m_radarMultiplier));
	p.setSize(sf::Vector2f(m_player.getWidth() * m_radarMultiplier, m_player.getHeight() * m_radarMultiplier));
	p.setFillColor(sf::Color::Green);
	window.draw(p);

	vector<Bullet>* _bullets = m_bulletManager.getBullets();
	for (int i = 0; i < _bullets->size(); i++)
	{
		if (_bullets->at(i).getAlive())
		{
			sf::RectangleShape b = sf::RectangleShape();
			b.setPosition(sf::Vector2f((_bullets->at(i).getPosition().x / m_screenSizes) + screenPos.x, (_bullets->at(i).getPosition().y * m_radarMultiplier)));
			b.setFillColor(sf::Color(165, 42, 42, 255));
			b.setSize(sf::Vector2f(_bullets->at(i).getSprite()->getTexture()->getSize().x * m_radarMultiplier, _bullets->at(i).getSprite()->getTexture()->getSize().y * m_radarMultiplier));
			window.draw(b);
		}
	}

	for (int i = 0; i < m_nests.size(); i++)
	{
		if (m_nests[i].getAlive())
		{
			sf::RectangleShape n = sf::RectangleShape();
			n.setPosition(sf::Vector2f((m_nests[i].getPosition().x / m_screenSizes) + screenPos.x, (m_nests[i].getPosition().y * m_radarMultiplier)));
			n.setFillColor(sf::Color::Red);
			n.setSize(sf::Vector2f(m_nests[i].getSprite()->getTexture()->getSize().x * m_radarMultiplier, m_nests[i].getSprite()->getTexture()->getSize().y * m_radarMultiplier));
			window.draw(n);
		}
	}

	vector<Abductor>* _abductors = m_abMan.getAbductors();
	for (int i = 0; i < _abductors->size(); i++)
	{
		if (_abductors->at(i).getAlive())
		{
			sf::RectangleShape ab = sf::RectangleShape();
			ab.setPosition(sf::Vector2f((_abductors->at(i).getPosition().x / m_screenSizes) + screenPos.x, (_abductors->at(i).getPosition().y * m_radarMultiplier)));
			ab.setFillColor(sf::Color::White);
			ab.setSize(sf::Vector2f(_abductors->at(i).getSprite()->getTexture()->getSize().x * m_radarMultiplier, _abductors->at(i).getSprite()->getTexture()->getSize().y * m_radarMultiplier));
			window.draw(ab);
		}
	}

	for (int i = 0; i < m_astronauts.size(); i++)
	{
		if (m_astronauts[i].getAlive())
		{
			sf::RectangleShape a = sf::RectangleShape();
			a.setPosition(sf::Vector2f((m_astronauts[i].getPosition().x / m_screenSizes) + screenPos.x, (m_astronauts[i].getPosition().y * m_radarMultiplier)));
			if (!m_astronauts[i].isMutant())
				a.setFillColor(sf::Color::Magenta);
			else
				a.setFillColor(sf::Color::Cyan);
			a.setSize(sf::Vector2f(m_astronauts[i].getSprite()->getTexture()->getSize().x * m_radarMultiplier, m_astronauts[i].getSprite()->getTexture()->getSize().y * m_radarMultiplier));
			window.draw(a);
		}
	}

	vector<PowerUp>* _powerUps = m_powerMan.getPowerUps();
	for (int i = 0; i < _powerUps->size(); i++)
	{
		if (_powerUps->at(i).getAlive())
		{
			sf::RectangleShape pu = sf::RectangleShape();
			pu.setPosition(sf::Vector2f((_powerUps->at(i).getPosition().x / m_screenSizes) + screenPos.x, (_powerUps->at(i).getPosition().y * m_radarMultiplier)));
			pu.setFillColor(sf::Color::Blue);
			pu.setSize(sf::Vector2f(_powerUps->at(i).getSprite()->getTexture()->getSize().x * m_radarMultiplier, _powerUps->at(i).getSprite()->getTexture()->getSize().y * m_radarMultiplier));
			window.draw(pu);
		}
	}
}

void GameScene::InitialiseAstronauts() 
{
	const int _NUMBEROFASTRONAUTS = 10;
	for (int i = 0; i < _NUMBEROFASTRONAUTS; i++)
	{
		sf::Vector2f _position(rand() % m_gameWorldEnd, 0.9 * m_height);

		Astro _astro(_position, m_gameWorldStart, m_gameWorldEnd, &m_player);
		m_astronauts.push_back(_astro);
	}
}

void GameScene::smartBomb()
{
	for (int i = 0; i < m_astronauts.size(); i++)
	{
		if (m_astronauts[i].isMutant())
			m_astronauts[i].reset();
		else if(m_astronauts[i].isCaught())
			m_astronauts[i].setState(Astro::State::FALL);
	}

	for (int i = 0; i < m_nests.size(); i++)
		m_nests[i].reset();

	vector<Abductor>* _abductors = m_abMan.getAbductors();
	for (int i = 0; i < _abductors->size(); i++)
		_abductors->at(i).reset();
}