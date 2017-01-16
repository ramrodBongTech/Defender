#include "stdafx.h"
#include "Player.h"

Player::Player() : GameEntity()
{
	m_position = sf::Vector2f(400, 300);
	m_speed = 0.1f;
	m_acceleration = sf::Vector2f(0.0f, 0.0f);
	m_direction = sf::Vector2f(-1, 0);
	m_velocity = sf::Vector2f((m_direction.x * m_acceleration.x), (m_direction.y * m_acceleration.y));

	m_texLeft = &AssetLoader::getInstance()->m_playerLeft;
	m_texRight = &AssetLoader::getInstance()->m_playerRight;
	m_sprite.setTexture(*m_texLeft);

	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);
}

Player::Player(float speed, sf::Vector2f pos, int gameWorldStart, int gameWorldEnd) : GameEntity()
{
	m_position = pos;
	m_speed = speed;
	m_acceleration = sf::Vector2f(0.0f, 0.0f);
	m_direction = sf::Vector2f(-1, 0);
	m_velocity = sf::Vector2f((m_direction.x * m_acceleration.x), (m_direction.y * m_acceleration.y));

	m_worldStart = gameWorldStart;
	m_worldEnd = gameWorldEnd;

	m_texLeft = &AssetLoader::getInstance()->m_playerLeft;
	m_texRight = &AssetLoader::getInstance()->m_playerRight;
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
	{
		if (m_acceleration.x > 0)
			m_acceleration.x -= m_speed;
		else if (m_acceleration.x < 0)
			m_acceleration.x = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveUp();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveDown();
	else
	{
		if (m_acceleration.y > 0)
			m_acceleration.y -= m_speed;
		else if (m_acceleration.y < 0)
			m_acceleration.y = 0;
	}

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

void Player::wrapAround()
{
	if (m_position.y > 600 - m_texLeft->getSize().y)
		m_position.y = 600 - m_texLeft->getSize().y;
	else if (m_position.y < m_texLeft->getSize().y)
		m_position.y = m_texLeft->getSize().y;

	/*if (m_position.x <= m_worldStart)
		m_position = sf::Vector2f(m_worldEnd, m_position.y);
	else if (m_position.x > m_worldEnd)
		m_position = sf::Vector2f(m_worldStart, m_position.y);*/
}

sf::Vector2f Player::getVelocity() { return m_velocity; }
