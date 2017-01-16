#include "stdafx.h"
#include "Player.h"

Player::Player() : GameEntity(),
m_direction(sf::Vector2f(-1, 0)),
m_velocity(sf::Vector2f((m_direction.x * m_acceleration.x), (m_direction.y * m_acceleration.y))),
m_acceleration(sf::Vector2f(0.0f, 0.0f)),
m_speed(0.1f),
m_firingDelay(2.0f),
m_maxFiringDelay(2.0f),
m_texLeft(&AssetLoader::getInstance()->m_playerLeft),
m_texRight(&AssetLoader::getInstance()->m_playerRight),
m_bullets(std::vector<Bullet*>(100, nullptr))
{
	m_position = sf::Vector2f(400, 300);
	
	m_sprite.setTexture(*m_texLeft);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);
}

/*Player::Player(float speed, sf::Vector2f pos) : GameEntity()
{
	m_position = pos;
	m_speed = speed;
	m_acceleration = sf::Vector2f(0.0f, 0.0f);
	m_direction = sf::Vector2f(-1, 0);
	m_velocity = sf::Vector2f((m_direction.x * m_acceleration.x), (m_direction.y * m_acceleration.y));

	m_texLeft = &AssetLoader::getInstance()->m_playerLeft;
	m_texRight = &AssetLoader::getInstance()->m_playerRight;
	m_sprite.setTexture(*m_texLeft);

	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);

	m_firingDelay = 0;
	m_maxFiringDelay = 50.0f;
	m_bullets = std::vector<Bullet*>(100, nullptr);
}*/

Player::~Player()
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets.at(i) != nullptr)
		{
			delete m_bullets.at(i);
			m_bullets.at(i) = nullptr;
		}
	}
}

void Player::update(float dt)
{
  	m_firingDelay += dt;

	processInput();

	m_position += m_velocity;
	m_sprite.setPosition(m_position);

	updateBullets(dt);

	wrapAround();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	for (int i = 0; i < m_bullets.size(); i++)
		if(m_bullets.at(i) != nullptr)
			m_bullets.at(i)->draw(window);
}

void Player::processInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveRight();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveLeft();
	else
		slowX();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveUp();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveDown();
	else
		slowY();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::milliseconds(m_firingDelay) >= sf::milliseconds(m_maxFiringDelay))
		shoot();

	m_velocity = sf::Vector2f((m_direction.x * m_acceleration.x), (m_direction.y * m_acceleration.y));
}

void Player::moveLeft()
{
	m_direction.x = -1;
	m_sprite.setTexture(*m_texLeft);
	if (m_acceleration.x < MAX_SPEED)
		m_acceleration.x += m_speed;

}

void Player::moveRight()
{
	m_direction.x = 1;
	m_sprite.setTexture(*m_texRight);
	if (m_acceleration.x < MAX_SPEED)
		m_acceleration.x += m_speed;
}

void Player::moveUp()
{
	m_direction.y = -1;

	if (m_acceleration.y < MAX_SPEED)
		m_acceleration.y += m_speed;
}

void Player::moveDown()
{
	m_direction.y = 1;

	if (m_acceleration.y < MAX_SPEED)
		m_acceleration.y += m_speed;
}

void Player::slowX()
{
	if (m_acceleration.x > 0)
		m_acceleration.x -= m_speed;
	else if (m_acceleration.x < 0)
		m_acceleration.x = 0;
}

void Player::slowY()
{
	if (m_acceleration.y > 0)
		m_acceleration.y -= m_speed;
	else if (m_acceleration.y < 0)
		m_acceleration.y = 0;
}

void Player::shoot()
{
	Bullet* _bullet = BulletFactory::getInstance()->getBullet();
	_bullet->setAlive(true);
	_bullet->setDirection(sf::Vector2f(m_direction.x, 0));
	_bullet->setPosition(sf::Vector2f(m_position.x + 20, m_position.y + 5));
	_bullet->setSpeed();
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets.at(i) == nullptr)
		{
			m_bullets.at(i) = _bullet;
			break;
		}
	}
	m_firingDelay = 0;
}

void Player::updateBullets(float dt)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets.at(i) != nullptr)
		{
			m_bullets.at(i)->update(dt);
			if (!m_bullets.at(i)->getAlive())
			{
   				delete m_bullets.at(i);
				m_bullets.at(i) = nullptr;
			}
		}
	}
}

void Player::wrapAround()
{
	if (m_position.y > 600 - m_texLeft->getSize().y)
		m_position.y = 600 - m_texLeft->getSize().y;
	if (m_position.y < m_texLeft->getSize().y)
		m_position.y = m_texLeft->getSize().y;
}

void Player::setVelocity(sf::Vector2f vel) { m_velocity = vel; }

void Player::setAcceleration(sf::Vector2f accel) { m_acceleration = accel; }

float Player::getWidth() { return m_texLeft->getSize().x / 2; }