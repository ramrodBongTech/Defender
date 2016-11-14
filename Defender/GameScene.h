#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "stdafx.h"
#include "Scene.h"

class GameScene : public Scene {
public:
	GameScene();
	~GameScene();

	void update(float dt);
	void draw(sf::RenderWindow& window);
};

#endif