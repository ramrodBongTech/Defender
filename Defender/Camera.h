#include "SFML/Graphics.hpp"  
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#include "Player.h"

class Camera
{
public:
	Camera(float width, float height);
	~Camera();

	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);

	void move(Player* player);

	sf::View getView();
	void setViewCenter(sf::Vector2f *position);

private:
	int			m_width;
	int			m_height;

	sf::View	m_view;
	sf::Sprite	m_sprite;
	sf::Texture	texture;
};

