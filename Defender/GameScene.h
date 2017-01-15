#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "stdafx.h"
#include "Scene.h"
#include "Player.h"
#include "Astronaut.h"
#include "Camera.h"

#include <vector>

using namespace std;

class GameScene : public Scene {
public:
	GameScene(int width, int height);
	~GameScene();

	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	Player*		m_player;
	Camera*		m_cam;

	vector<Astronaut>	m_astronauts;
	void InitialiseAstronauts(int screenWidth, int screenHeight);
	void WrapAround();
};

#endif