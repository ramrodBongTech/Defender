#include "stdafx.h"
#include "Abductor.h"

Abductor::Abductor(Player* player, std::vector<Astro>* astros, BulletManager* bulletManager, std::vector<Obstacle>* obstacles) : GameEntity(),
m_speed(1.0f),
m_firingDelay(3.0f),
m_signalTimer(0),
m_direction(sf::Vector2f(-1, 0)),
m_velocity(sf::Vector2f((m_direction.x * m_speed), (m_direction.y * m_speed))),
m_signalPos(sf::Vector2f(0, 0)),
m_abductorCaught(false),
m_signal(false),
m_damage(10),
m_health(2),
m_texLeft(&AssetLoader::getInstance()->m_abductorLeft),
m_texRight(&AssetLoader::getInstance()->m_abductorRight),
m_astronauts(astros),
m_player(player),
m_bulletManager(bulletManager),
m_caughtAstro(nullptr),
m_obstacles(obstacles),
m_closestObstacle(nullptr)
{
	m_sprite.setTexture(*m_texLeft);
	m_sprite.setPosition(m_position);
	m_width = m_texLeft->getSize().x / 2;
	m_height = m_texLeft->getSize().y / 2;
	m_sprite.setOrigin(m_width, m_height);
}

Abductor::~Abductor() 
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
}

void Abductor::update(float dt) 
{
	if (m_alive)
	{
		m_firingDelay += dt;

		checkClosestObstacle();

		sf::Vector2f BA = m_closestObstacle->getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));

		if (dis < MAX_EVADE_DISTANCE)
			evadeObstacle();
		else if (!m_abductorCaught)
			chase();
		else
			rise();

		BA = m_player->getPosition() - m_position;
		dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));

		if (dis < MAX_SHOOTING_DISTANCE && m_firingDelay >= MAX_FIRING_DELAY)
			shoot(dis);

		if (m_health <= 0)
			reset();

		if (m_signal)
		{
			m_signalTimer += dt;

			if (m_signalTimer >= 2.0f)
			{
				m_signalTimer = 0;
				m_signal = false;
			}
		}
	}
}

void Abductor::draw(sf::RenderWindow& window) 
{
	if (m_alive)
		window.draw(m_sprite);

	if (m_signal)
	{
		sf::RectangleShape sr = sf::RectangleShape();
		sf::Vector2f screenPos = sf::Vector2f(window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y - window.getSize().y / 2);
		sr.setPosition(sf::Vector2f((m_signalPos.x / 9) + screenPos.x, m_signalPos.y * 0.2));
		sr.setSize(sf::Vector2f((m_width * 4) / 9, (m_height * 4) * 0.2));
		sr.setFillColor(sf::Color::Transparent);
		sr.setOutlineThickness(2);
		sr.setOutlineColor(sf::Color::Red);
		window.draw(sr);
	}
}

void Abductor::reset()
{
	m_alive = false;
	m_position = sf::Vector2f(99999, 99999);
	m_sprite.setPosition(m_position);
	m_health = 2;
	if (m_abductorCaught)
	{
		m_abductorCaught = false;
		m_caughtAstro->setFalling(true);
		m_caughtAstro->setCaught(false);
		m_caughtAstro = nullptr;
	}
}

int Abductor::getDamage() { return m_damage; }

void Abductor::takeDamage(int damage) { m_health -= damage; }

void Abductor::updatePosition() 
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);

	if (m_direction.x < 0)
		m_sprite.setTexture(*m_texLeft);
	else
		m_sprite.setTexture(*m_texRight);
}

void Abductor::chase() 
{
	sf::Vector2f temp = m_astronauts->at(0).getPosition() - m_position;
	float _lowestDistance = std::sqrt((temp.x*temp.x) + (temp.y*temp.y));;
	Astro* _closestAstro = &m_astronauts->at(0);
	for (int i = 1; i < m_astronauts->size(); i++)
	{
		sf::Vector2f BA = m_astronauts->at(i).getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));
		if (dis < _lowestDistance && !m_astronauts->at(i).isCaught() && !m_astronauts->at(i).isMutant() && m_astronauts->at(i).getAlive())
		{
			_lowestDistance = dis;
			_closestAstro = &m_astronauts->at(i);
		}
	}

	if (_lowestDistance < m_sprite.getTexture()->getSize().x / 2)
	{
		m_abductorCaught = true;
		m_caughtAstro = _closestAstro;
		_closestAstro->caught();
		m_signal = true;
		m_signalPos = m_position;
	}

	m_direction = _closestAstro->getPosition() - m_position;
	float _length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / _length, m_direction.y / _length);
	m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);

	updatePosition();
}

void Abductor::flock() 
{

}

void Abductor::shoot(float dis)
{
	Bullet* _bullet = m_bulletManager->nextBullet();
	if (_bullet != nullptr)
	{
		_bullet->setAlive(true);
		_bullet->setPosition(sf::Vector2f(m_position.x, m_position.y));
		sf::Vector2f tempDir = m_player->getPosition() - m_position;
		float length = sqrt((tempDir.x*tempDir.x) + (tempDir.y*tempDir.y));
		tempDir = sf::Vector2f(tempDir.x / length, tempDir.y / length);
		_bullet->setDirection(tempDir);
		_bullet->setSpeed();
		_bullet->setIsPlayerBullet(false);
	}
	m_firingDelay = 0;
}

void Abductor::rise()
{
	m_position.y -= m_speed;
	m_sprite.setPosition(m_position);
	if (m_position.y < 0)
	{
		m_abductorCaught = false;
		m_caughtAstro = nullptr;
	}
}

void Abductor::evadeObstacle() 
{
	m_direction = m_position - m_closestObstacle->getPosition();
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);
	updatePosition();
}

void Abductor::checkClosestObstacle()
{
	sf::Vector2f temp = m_obstacles->at(0).getPosition() - m_position;
	float _lowestDistance = std::sqrt((temp.x*temp.x) + (temp.y*temp.y));;
	m_closestObstacle = &m_obstacles->at(0);
	for (int i = 0; i < m_obstacles->size(); i++)
	{
		sf::Vector2f BA = m_obstacles->at(i).getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));
		if (dis < _lowestDistance && !m_obstacles->at(i).getAlive())
		{
			_lowestDistance = dis;
			m_closestObstacle = &m_obstacles->at(i);
		}
	}
}

void Abductor::Flock(vector<Abductor> abductors) {
	sf::Vector2f sep = Separation(abductors);
	sf::Vector2f ali = Alignment(abductors);
	sf::Vector2f coh = Cohesion(abductors);
	// Arbitrarily weight these forces
	sep = sf::Vector2f(sep.x * 1.5f, sep.y * 1.5f);
	ali = sf::Vector2f(ali.x * 1.0f, ali.y * 1.0f); // Might need to alter weights for different characteristics
	coh = sf::Vector2f(coh.x * 1.0, coh.y * 1.0f);
	// Add the force vectors to acceleration
	m_acceleration += sep + ali + coh;
}

sf::Vector2f Abductor::Separation(vector<Abductor> abductors) {
	float desiredseparation = 180;

	sf::Vector2f steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < abductors.size(); i++)
	{
		// Calculate distance from current boid to boid we're looking at
		float dx = m_position.x - abductors[i].getPosition().x;
		float dy = m_position.y - abductors[i].getPosition().y;
		float d = sqrt((dx * dx) + (dy*dy));
		// If this is a fellow boid and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation))
		{
			sf::Vector2f diff(m_position.x - abductors[i].getPosition().x, m_position.y - abductors[i].getPosition().y);
			//normalise
			float magnitude = sqrt((diff.x * diff.x) + (diff.y * diff.y));
			if (magnitude > 0)
				diff = sf::Vector2f(diff.x / magnitude, diff.y / magnitude);
			else
				diff = diff;

			diff = sf::Vector2f(diff.x / d, diff.y / d);      // Weight by distance
			steer += diff;
			count++;
		}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer = sf::Vector2f(steer.x / (float)count, steer.y / (float)count);

	float _steerMagnitude = sqrt((steer.x * steer.x) + (steer.y * steer.y));
	if (_steerMagnitude > 0)
	{
		// Steering = Desired - Velocity
		if (_steerMagnitude > 0)
			steer = sf::Vector2f(steer.x / _steerMagnitude, steer.y / _steerMagnitude);
		else
			steer = steer;

		steer = sf::Vector2f(steer.x * MAX_SPEED, steer.y * MAX_SPEED);
		steer -= m_velocity;

		double size = sqrt((steer.x * steer.x) + (steer.y * steer.y));

		if (size > 0.5)
			steer = sf::Vector2f(steer.x / size, steer.y / size);
	}
	return steer;
}

sf::Vector2f Abductor::Cohesion(vector<Abductor> abductors) {
	float neighbordist = 50;

	sf::Vector2f sum(0, 0);
	int count = 0;
	for (int i = 0; i < abductors.size(); i++)
	{
		float dx = m_position.x - abductors[i].getPosition().x;
		float dy = m_position.y - abductors[i].getPosition().y;
		float d = sqrt((dx * dx) + (dy*dy));

		if ((d > 0) && (d < neighbordist))
		{
			sum += abductors[i].getPosition();
			count++;
		}
	}
	if (count > 0)
	{
		sum = sf::Vector2f(sum.x / count, sum.y / count);
		return Seek(sum);
	}
	else {
		sf::Vector2f temp(0, 0);
		return temp;
	}
}

sf::Vector2f Abductor::Alignment(vector<Abductor> abductors) {
	float neighbordist = 50;

	sf::Vector2f sum(0, 0);
	int count = 0;
	for (int i = 0; i < abductors.size(); i++)
	{
		float dx = m_position.x - abductors[i].getPosition().x;
		float dy = m_position.y - abductors[i].getPosition().y;
		float d = sqrt((dx * dx) + (dy*dy));
		if ((d > 0) && (d < neighbordist)) // 0 < d < 50
		{
			sum += abductors[i].GetVelocity();
			count++;
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0)
	{
		sum = sf::Vector2f(sum.x / (float)count, sum.y / (float)count);
		sum = normalize(sum);		// Turn sum into a unit vector, and
		sum = sf::Vector2f(sum.x * MAX_SPEED, sum.y * MAX_SPEED);  // Multiply by maxSpeed
																   // Steer = Desired - Velocity
		sf::Vector2f steer;//sum = desired(average)  
		steer = sf::Vector2f(sum.x - m_velocity.x, sum.y - m_velocity.y);

		double size = sqrt(steer.x * steer.x + steer.y * steer.y);
		if (size > 0.5)
			steer = sf::Vector2f(steer.x / size, steer.y / size);
		return steer;
	}
	else {
		sf::Vector2f temp(0, 0);
		return temp;
	}
}

sf::Vector2f Abductor::normalize(sf::Vector2f vector) {
	sf::Vector2f tmp = vector;
	float mag = sqrt(vector.x * vector.x + vector.y * vector.y);

	if (mag > 0)
		tmp = sf::Vector2f(vector.x / mag, vector.y / mag);
	else
		tmp = tmp;

	return tmp;
}

sf::Vector2f Abductor::Seek(sf::Vector2f vector) {
	sf::Vector2f desired;
	desired = sf::Vector2f(desired.x - vector.x, desired.y - vector.y);
	// A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired = normalize(desired);
	desired = sf::Vector2f(desired.x * MAX_SPEED, desired.y * MAX_SPEED);
	// Steering = Desired minus Velocity
	m_acceleration = sf::Vector2f(desired.x - m_velocity.x, desired.y - m_velocity.y);
	double size = sqrt((m_acceleration.x * m_acceleration.x) + (m_acceleration.y * m_acceleration.y));

	if (size > 0.5)
		m_acceleration = sf::Vector2f(m_acceleration.x / size, m_acceleration.y / size);

	return m_acceleration;
}

sf::Vector2f Abductor::GetVelocity() { return m_velocity; }
