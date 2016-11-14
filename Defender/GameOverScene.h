#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "stdafx.h"
#include "Scene.h"

class GameOverScene : public Scene {
public:
	GameOverScene();
	~GameOverScene();

	void update(float dt);
	void draw(sf::RenderWindow& window);
};

#endif