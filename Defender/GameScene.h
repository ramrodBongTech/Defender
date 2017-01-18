#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "Astro.h"
#include "Camera.h"
#include "AlienNest.h"
#include "AbductorManager.h"
#include "PowerUpManager.h"
#include "CollisionManager.h"

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
	int					m_screenSizes;
	int					m_gameWorldStart;
	int					m_gameWorldEnd;
	double				m_radarMultiplier;

	sf::VertexArray		m_ground;

	Player				m_player;
	Camera				m_cam;
	vector<Astro>		m_astronauts;
	vector<AlienNest>	m_nests;
	sf::Sprite			m_radarSprite;
	BulletManager		m_bulletManager;
	AbductorManager		m_abMan;
	PowerUpManager		m_powerMan;
	CollisionManager	m_collMan;

	void createGround();
	void createNests();
	bool groundCollision();
	void drawRadar(sf::RenderWindow& window);
	void InitialiseAstronauts();
	void smartBomb();

	const int MAX_NUMBER_NESTS = 5;
};

#endif