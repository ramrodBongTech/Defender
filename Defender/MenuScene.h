#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"

class MenuScene : public Scene {
public:
	MenuScene();
	~MenuScene();

	void update(float dt);
	void draw(sf::RenderWindow& window);
};

#endif