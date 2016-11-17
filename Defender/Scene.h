#ifndef SCENE_H
#define SCENE_H

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

#include "AssetLoader.h"

class Scene {
public:
	Scene(std::string name);
	~Scene();

	virtual void start();
	virtual void stop();

	std::string getTitle();

	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	bool			m_alive;
	std::string		m_title;
};

#endif