#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "Astronaut.h"
#include "Camera.h"
#include "AlienNest.h"

#include <vector>

using namespace std;

class GameScene : public Scene {
public:
	GameScene(int width, int height);
	~GameScene();

	void update(float dt);
	void draw(sf::RenderWindow& window);

private:
	float				m_width;
	float				m_height;
	int					m_gameWorldStart;
	int					m_gameWorldEnd;

	sf::VertexArray		m_ground;

	Player*				m_player;
	Camera*				m_cam;
	vector<AlienNest*>	m_nests;
	sf::Sprite			m_radarSprite;

	void createGround();
	void createNests();
	bool groundCollision();
	void drawRadar(sf::RenderWindow& window);

	vector<Astronaut>	m_astronauts;
	void InitialiseAstronauts(int screenHeight);

	const int MAX_NUMBER_NESTS = 5;
};

#endif