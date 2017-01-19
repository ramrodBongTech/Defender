#include "stdafx.h"
#include "Abductor.h"

Abductor::Abductor(Player* player, std::vector<Astro>* astros, BulletManager* bulletManager): GameEntity(),
m_speed(1.0f),
m_firingDelay(3.0f),
m_direction(sf::Vector2f(-1,0)),
m_velocity(sf::Vector2f((m_direction.x * m_speed), (m_direction.y * m_speed))),
m_abductorCaught(false),
m_texLeft(&AssetLoader::getInstance()->m_abductorLeft),
m_texRight(&AssetLoader::getInstance()->m_abductorRight),
m_astronauts(astros),
m_player(player),
m_bulletManager(bulletManager)
{
	m_velocity = sf::Vector2f(0,0);
	m_sprite.setTexture(*m_texLeft);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texLeft->getSize().x / 2, m_texLeft->getSize().y / 2);
	m_flockRandomiser = rand() % 11 + 4;
	m_flocking = true;
	m_flockDelay = 0;
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
		m_flockDelay += dt;

		if (m_flockDelay < m_flockRandomiser && m_flocking)
			flock();
		else if (!m_abductorCaught)
			chase();
		else if (m_abductorCaught)
			rise();

		/*sf::Vector2f BA = m_player->getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));

		if (dis < MAX_SHOOTING_DISTANCE && m_firingDelay >= MAX_FIRING_DELAY)
			shoot(dis);*/
	}
}

void Abductor::draw(sf::RenderWindow& window) 
{
	if (m_alive)
		window.draw(m_sprite);
}

void Abductor::chase() 
{
	m_flockDelay = 0;
	m_flocking = false;

	sf::Vector2f temp = m_astronauts->at(0).getPosition() - m_position;
	float _lowestDistance = std::sqrt((temp.x*temp.x) + (temp.y*temp.y));;
	Astro* _closestAstro = &m_astronauts->at(0);
	for (int i = 1; i < m_astronauts->size(); i++)
	{
		sf::Vector2f BA = m_astronauts->at(i).getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));
		if (dis < _lowestDistance && !m_astronauts->at(i).isCaught() && !m_astronauts->at(i).isMutant())
		{
			_lowestDistance = dis;
			_closestAstro = &m_astronauts->at(i);
		}
	}

	if (_lowestDistance < m_sprite.getTexture()->getSize().x / 2)
	{
		m_abductorCaught = true;
		_closestAstro->caught();
		signalAbduction();
	}

	m_direction = _closestAstro->getPosition() - m_position;
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);
	
	updatePosition();
}

void Abductor::updatePosition()
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);

	if (m_velocity.x < 0)
		m_sprite.setTexture(*m_texLeft);
	else
		m_sprite.setTexture(*m_texRight);
}

void Abductor::flock() 
{
	m_velocity += m_acceleration;
	double size = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (size > MAX_SPEED) {
		m_velocity = normalize(m_velocity) * MAX_SPEED;
		m_velocity = sf::Vector2f(m_velocity.x * MAX_SPEED, sin(m_position.x / 15) * MAX_SPEED);
	}

	updatePosition();
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
	}
	m_firingDelay = 0;
}

void Abductor::rise()
{
	m_position.y -= m_speed;
	m_sprite.setPosition(m_position);
	if (m_position.y < 0)
		m_abductorCaught = false;
}

void Abductor::signalAbduction()
{

}

void Abductor::Flock(vector<Abductor> abductors) {
	sf::Vector2f sep = Separation(abductors);
	sf::Vector2f ali = Alignment(abductors);
	sf::Vector2f coh = Cohesion(abductors);
	// Arbitrarily weight these forces
	sep *= 3.5f;
	ali *= 2.f;// Might need to alter weights for different characteristics
	coh *= 1.f;
	// Add the force vectors to acceleration
	m_acceleration = sep + ali + coh;
}

sf::Vector2f Abductor::Separation(vector<Abductor> abductors) {
	float desiredseparation = 75;

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
			diff = normalize(diff);

			diff = sf::Vector2f(diff.x / d, diff.y / d);      // Weight by distance
			steer += diff;
			count++;
		}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer /= (float)count;

	float _steerMagnitude = sqrt((steer.x * steer.x) + (steer.y * steer.y));
	if (_steerMagnitude > 0)
	{
		steer /= _steerMagnitude;
		steer *= MAX_SPEED;
		steer -= m_velocity;

		double size = sqrt((steer.x * steer.x) + (steer.y * steer.y));
		if (size > MAX_FORCE)
			steer = normalize(steer) * MAX_FORCE;
	}

	return steer;
}

sf::Vector2f Abductor::Cohesion(vector<Abductor> abductors) {
	float neighbordist = 400;

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
		sum /= float(count);
		return Seek(sum);
	}
	else {
		sf::Vector2f temp(0, 0);
		return temp;
	}
}

sf::Vector2f Abductor::Alignment(vector<Abductor> abductors) {
	float neighbordist = 100;

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
		sum /= (float)count;
		sum = normalize(sum);		// Turn sum into a unit vector, and
		sum *= MAX_SPEED;  // Multiply by maxSpeed
																   // Steer = Desired - Velocity
		sf::Vector2f steer;//sum = desired(average)  
		steer = sf::Vector2f(sum.x - m_velocity.x, sum.y - m_velocity.y);

		double size = sqrt((steer.x * steer.x) + (steer.y * steer.y));
		if (size > MAX_FORCE)
			steer = normalize(steer) * MAX_FORCE;

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
	desired = sf::Vector2f(vector.x - m_position.x, vector.y - m_position.y);
	// A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired = normalize(desired);
	desired = sf::Vector2f(desired.x * MAX_SPEED, desired.y * MAX_SPEED);
	// Steering = Desired minus Velocity
	m_acceleration = sf::Vector2f(desired.x - m_velocity.x, desired.y - m_velocity.y);
	double size = sqrt((m_acceleration.x * m_acceleration.x) + (m_acceleration.y * m_acceleration.y));

	if (size > MAX_FORCE)
		m_acceleration = normalize(m_acceleration) * MAX_FORCE;

	return m_acceleration;
}

sf::Vector2f Abductor::GetVelocity() { return m_velocity; }
bool Abductor::isFlocking() { return m_flocking; }