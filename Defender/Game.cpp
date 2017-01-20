#include "stdafx.h"
#include "Game.h"

Game::Game() : m_running(false),
m_window(sf::VideoMode(1400, 700, 32), "Defender"),
m_sceneMgr(nullptr)
{}

Game::~Game() {
	delete m_sceneMgr;
	m_window.close();
}

void Game::Initialise() {
	m_window.setFramerateLimit(60);
	m_sceneMgr = new SceneManager(m_window.getSize().x, m_window.getSize().y);
	m_running = true;
}

void Game::Update() {
	m_time = m_clock.restart();
	m_sceneMgr->update(m_time.asSeconds());
}

void Game::Draw() {
	m_window.clear();

	m_sceneMgr->draw(m_window);

	m_window.display();
}

void Game::CheckInput() {
	sf::Event Event;
	while (m_window.pollEvent(Event)){
		if (Event.type == sf::Event::Closed	||
			(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape))
			m_running = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_sceneMgr->getCurrentScene()->getTitle() == "Menu")
			m_sceneMgr->nextScene();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_sceneMgr->getCurrentScene()->getTitle() == "GameOver")
			m_sceneMgr->previousScene();
	}
}

bool Game::IsRunning() {
	return m_running;
}