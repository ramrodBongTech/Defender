#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "MenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

class SceneManager {
public:
	SceneManager(int width, int height);
	~SceneManager();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void switchScene(std::string name);
	void nextScene();
	void previousScene();

	Scene* getCurrentScene();

	void addScene(Scene* scene);

private:
	Scene*					m_currScene;
	std::vector<Scene*>		m_scenes;

};

#endif