#include "stdafx.h"
#include "MenuScene.h"

MenuScene::MenuScene() : Scene("Menu")
{
	m_logo = sf::Sprite(AssetLoader::getInstance()->m_logo);
	m_logo.setOrigin(m_logo.getTexture()->getSize().x / 2, m_logo.getTexture()->getSize().y / 2);
	m_logo.setPosition(sf::Vector2f(700, 350));
}

MenuScene::~MenuScene()
{}

void MenuScene::update(float dt)
{

}

void MenuScene::draw(sf::RenderWindow& window)
{
	if (m_alive)
	{
		std::cout << "MENU SCREEN!!" << std::endl;
		std::cout << "Press Right Key to play!!" << std::endl;
	}
	m_alive = false;
	window.draw(m_logo);
}