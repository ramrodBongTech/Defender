#include "stdafx.h"
#include "Player.h"

Player::Player() : GameEntity(),
m_speed(0.1f),
m_firingDelay(2.0f),
m_maxFiringDelay(0.25f),
m_smartBombTimer(60.0f),
m_direction(sf::Vector2f(-1, 0)),
m_acceleration(sf::Vector2f(m_speed, m_speed)),
m_velocity(sf::Vector2f((m_direction.x * m_acceleration.x), (m_direction.y * m_acceleration.y))),
m_isSmartBombActivated(false),
m_canUseSmartBomb(false),
m_texLeft(&AssetLoader::getInstance()->m_playerLeft),
m_texRight(&AssetLoader::getInstance()->m_playerRight)
{
	m_position = sf::Vector2f(5400, 300);
	
	m_sprite.setTexture(*m_texLeft);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);
}

Player::~Player()
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
}

void Player::update(float dt)
{
  	m_firingDelay += dt;

	if (!m_canUseSmartBomb)
		m_smartBombTimer += dt;

	if (m_smartBombTimer >= MAX_BOMB_TIMER)
	{
		m_canUseSmartBomb = true;
		m_smartBombTimer = 0;
	}

	processInput();
	m_position += m_velocity;
	m_sprite.setPosition(m_position);

	wrapAround();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_firingDelay >= m_maxFiringDelay)
		shoot();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && m_canUseSmartBomb && !m_isSmartBombActivated)
		m_isSmartBombActivated = true;

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
	Bullet* _bullet = m_bulletManager->nextBullet();
	if (_bullet != nullptr)
	{
		_bullet->setAlive(true);
		_bullet->setDirection(sf::Vector2f(m_direction.x, 0));
		_bullet->setPosition(sf::Vector2f(m_position.x + 20, m_position.y + 5));
		_bullet->setSpeed();
		_bullet->setIsPlayerBullet(true);
	}
	m_firingDelay = 0;
}

void Player::wrapAround()
{
	if (m_position.y > 600 - m_texLeft->getSize().y)
		m_position.y = 600 - m_texLeft->getSize().y;
	else if (m_position.y < m_texLeft->getSize().y)
		m_position.y = m_texLeft->getSize().y;
}

void Player::setVelocity(sf::Vector2f vel) { m_velocity = vel; }
void Player::setAcceleration(sf::Vector2f accel) { m_acceleration = accel; }
void Player::setManager(BulletManager* bf) { m_bulletManager = bf; }

float Player::getWidth() { return m_texLeft->getSize().x / 2; }
float Player::getHeight() { return m_texLeft->getSize().y / 2; }
sf::Vector2f Player::getVelocity() { return m_velocity; }
bool Player::isSmartBombActivated() { return m_isSmartBombActivated; }

void Player::resetSmartBomb()
{
	m_smartBombTimer = 0;
	m_canUseSmartBomb = false;
	m_isSmartBombActivated = false;
}