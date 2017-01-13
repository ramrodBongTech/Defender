//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

#include "SceneManager.h"

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

SceneManager* sceneMgr;
sf::Clock myClock;

int main()
{
	srand(time(NULL));
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Defender");
	window.setFramerateLimit(60);

	sceneMgr = new SceneManager(window.getSize().x, window.getSize().y);
	sf::Time time;

	// Start game loop 
	while (window.isOpen())
	{
		time = myClock.restart();

		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sceneMgr->getCurrentScene()->getTitle() == "Menu")
				sceneMgr->nextScene();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sceneMgr->getCurrentScene()->getTitle() == "GameOver")
				sceneMgr->previousScene();
		}

		sceneMgr->update(time.asSeconds());

		//prepare frame
		window.clear();

		sceneMgr->draw(window);

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}