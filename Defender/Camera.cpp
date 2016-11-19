#include "stdafx.h"
#include "Camera.h"

Camera::Camera(float width, float height)
{
	m_width = width;
	m_height = height;

	// Test texture to see if the camera works
	if (!texture.loadFromFile("Assets/Textures/grid.png")) { std::cout << "Error Loading Grid Textures" << std::endl; }
	texture.setSmooth(true);
	m_sprite.setTexture(texture);
	m_sprite.setPosition(-(width*4), 0);
	m_sprite.scale(9, 1);

	m_view.setSize(m_width, m_height);
	m_view.setCenter(sf::Vector2f(m_width / 2, m_height / 2));
}

Camera::~Camera() { }

void Camera::draw(sf::RenderWindow &window)
{
	window.setView(m_view);
	window.draw(m_sprite);
}

void Camera::update(sf::RenderWindow &window) { window.setView(m_view); }

void Camera::move(Player* player)
{
	if (player->getPosition().x <= -((m_width * 4)))
	{
		player->setPosition(sf::Vector2f((m_width * 5), player->getPosition().y));
		m_view.setCenter(sf::Vector2f(((m_width * 5) - m_width / 2), m_height / 2));
	}

	if (player->getPosition().x > (m_width * 5))
	{
		player->setPosition(sf::Vector2f(-((m_width * 4)), player->getPosition().y));
		m_view.setCenter(sf::Vector2f((-(m_width * 4) + m_width / 2), m_height / 2));
	}

	if (player->getPosition().x < (-(m_width*4) + m_width / 2) || player->getPosition().x > ((m_width * 5) - m_width / 2))
		m_view.setCenter(m_view.getCenter());
	else
		m_view.setCenter(sf::Vector2f(player->getPosition().x, m_height / 2));
}

sf::View Camera::getView() { return m_view; }

void Camera::setViewCenter(sf::Vector2f* pos) { m_view.setCenter(*pos); }