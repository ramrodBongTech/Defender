#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager(int width, int height) :
	m_currScene(nullptr)
{
	MenuScene* ms = new MenuScene();
	m_scenes.push_back(ms);

	GameScene* gs = new GameScene(width, height);
	m_scenes.push_back(gs);

	GameOverScene* gos = new GameOverScene();
	m_scenes.push_back(gos);

	m_currScene = ms;

	AssetLoader::getInstance();
}

SceneManager::~SceneManager()
{
	m_currScene = nullptr;
	for (int i = 0; i < m_scenes.size(); i++)
	{
		delete m_scenes.at(i);
		m_scenes.at(i) = nullptr;
	}
}

void SceneManager::update(float dt) { m_currScene->update(dt); }

void SceneManager::draw(sf::RenderWindow& window) { m_currScene->draw(window); }

void SceneManager::switchScene(std::string name)
{
	bool _found = false;
	int _i = 0;
	Scene* _nextScene = nullptr;

	while (_i < m_scenes.size() && !_found)
	{
		if (m_scenes.at(_i)->getTitle() == name)
		{
			_found = true;
			_nextScene = m_scenes.at(_i);
		}
		_i++;
	}

	if (_found)
	{
		if (m_currScene != nullptr)
			m_currScene->stop();

		m_currScene = _nextScene;
		m_currScene->start();
	}
}

void SceneManager::nextScene()
{
	bool _found = false;
	int _i = 0;
	Scene* _nextScene = nullptr;

	while (_i < m_scenes.size() && !_found)
	{
		if (m_scenes.at(_i)->getTitle() == m_currScene->getTitle() && _i + 1 < m_scenes.size())
		{
			_found = true;
			_nextScene = m_scenes.at(_i + 1);
		}
		_i++;
	}

	if (_found)
	{
		if (m_currScene != nullptr)
			m_currScene->stop();

		m_currScene = _nextScene;
		m_currScene->start();
	}
}

void SceneManager::previousScene()
{
	bool _found = false;
	int _i = 1;
	Scene* _nextScene = nullptr;

	while (_i < m_scenes.size() && !_found)
	{
		if (m_scenes.at(_i)->getTitle() == m_currScene->getTitle())
		{
			_found = true;
			_nextScene = m_scenes.at(_i - 1);
		}
		_i++;
	}

	if (_found)
	{
		if (m_currScene != nullptr)
			m_currScene->stop();

		m_currScene = _nextScene;
		m_currScene->start();
	}
}

Scene* SceneManager::getCurrentScene() { return m_currScene; }
