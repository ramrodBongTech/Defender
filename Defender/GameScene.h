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
	float									m_width;
	float									m_height;

	sf::VertexArray							m_ground;

	void createGround();
	bool groundCollision();

	Player*		m_player;
	Camera*		m_cam;

	vector<Astronaut>	m_astronauts;
	void InitialiseAstronauts(int screenHeight);

	int m_gameWorldStart;
	int m_gameWorldEnd;
};

#endif