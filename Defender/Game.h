#ifndef GAME_H
#define GAME_h

#include "SceneManager.h"

class Game {
public:
	Game();
	~Game();

	void Initialise();
	void Update();
	void Draw();
	void CheckInput();

	bool IsRunning();
private:
	bool				m_running;
	SceneManager*		m_sceneMgr;
		
	sf::Clock			m_clock;
	sf::Time			m_time;
	sf::RenderWindow	m_window;
};

#endif // !GAME_H

