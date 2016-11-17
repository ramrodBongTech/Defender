#include "stdafx.h"
#include "MenuScene.h"

MenuScene::MenuScene() : Scene("Menu")
{}

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
	}
	m_alive = false;
}