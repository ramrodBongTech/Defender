#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "stdafx.h"
#include "Scene.h"
#include "Player.h"
#include "Camera.h"

class GameScene : public Scene {
public:
	GameScene(int width, int height);
	~GameScene();

	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	float									m_width;
	float									m_height;
	Player*									m_player;
	Camera*									m_cam;

	sf::VertexArray							m_ground;

	void createGround();
	bool groundCollision();
};

#endif