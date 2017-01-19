#include "stdafx.h"
#include "Astro.h"

Astro::Astro() : GameEntity()
{}

Astro::Astro(sf::Vector2f position, int gameWorldStart, int gameWorldEnd, Player* player, std::vector<Obstacle>* obstacles) : GameEntity(),
m_state(State::WANDER),
m_elapsedWanderTime(0),
m_elapsedPauseTime(0),
m_speed(0.8f),
m_swarmDelay(0.0f),
m_worldStart(gameWorldStart),
m_worldEnd(gameWorldEnd),
m_damage(10),
m_health(4),
m_swarmRandomiser(rand() % 11 + 4),
m_isCaught(false),
m_isMutant(false),
m_isFalling(false),
m_isSwarming(false),
m_acceleration(sf::Vector2f(0, 0)),
m_direction(sf::Vector2f((rand() % 1)-1, 0)),
m_velocity(sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed)),
m_texLeft(&AssetLoader::getInstance()->m_astronautLeft),
m_texRight(&AssetLoader::getInstance()->m_astronautRight),
m_mutantLeft(&AssetLoader::getInstance()->m_mutantLeft),
m_mutantRight(&AssetLoader::getInstance()->m_mutantRight),
m_player(player),
m_obstacles(obstacles)
{
	m_position = position;
	m_alive = true;

	if (m_direction.x < 0)
		m_sprite.setTexture(*m_texLeft);
	else
		m_sprite.setTexture(*m_texRight);

	m_sprite.setPosition(m_position);
	m_width = m_texLeft->getSize().x / 2;
	m_height = m_texLeft->getSize().y / 2;
	m_sprite.setOrigin(m_width, m_height);
}

Astro::~Astro()
{
	m_texLeft = nullptr;
	m_texRight = nullptr;
}

void Astro::update(float dt) 
{
	if (m_alive)
	{
		switch (m_state)
		{
		case State::WANDER:
			Wander(dt);
			break;
		case State::PAUSE:
			Pause(dt);
			break;
		case State::EVADE:
			Evade();
			break;
		case State::RISE:
			Rise();
			break;
		case State::FALL:
			Fall();
			break;
		case State::MUTANT:
			MutantBehaviour();
			break;
		case State::EVADE_OBSTACLE:
			evadeObstacle();
			break;
		case State::SWARM:
			swarm();
			break;
		}
		checkClosestObstacle();

		sf::Vector2f BA = m_closestObstacle->getPosition() - m_position;
		float dis = std::sqrt((BA.x*BA.x) + (BA.y*BA.y));

		if (dis < MAX_OBSTACLE_DISTANCE && m_isMutant)
			m_state = State::EVADE_OBSTACLE;
		else if (m_swarmDelay < m_swarmRandomiser && m_isSwarming)
			m_state = State::SWARM;
		else if (dis > MAX_OBSTACLE_DISTANCE && m_isMutant)
			m_state = State::MUTANT;
		else if (m_isCaught)
			m_state = State::RISE;
		else if (m_isFalling)
			m_state = State::FALL;
		else if (!m_isCaught && !m_isMutant && !m_isFalling)
			m_state = State::WANDER;
		else if (enemyDetected())
			m_state = State::EVADE;

		m_sprite.setPosition(m_position);
		WrapAround();

		if (m_health <= 0)
			reset();
	}
}

void Astro::draw(sf::RenderWindow & window)
{
	if (m_alive)
		window.draw(m_sprite);
}

void Astro::caught() 
{ 
	m_state = State::RISE;
	m_isCaught = true;
}

void Astro::reset()
{
	m_alive = false;
	m_position = sf::Vector2f(99999, 99999);
	m_sprite.setPosition(m_position);
	m_health = 4;
}

bool Astro::isCaught() { return m_isCaught; }

bool Astro::isMutant() { return m_isMutant; }

void Astro::setFalling(bool falling) { m_isFalling = falling; }

void Astro::setCaught(bool caught) { m_isCaught = caught; }

void Astro::setMutant(bool mutant) 
{ 
	m_isMutant = mutant;
	m_state = State::MUTANT;
}

int Astro::getDamage() { return m_damage; }

void Astro::takeDamage(int damage) { m_health -= damage; }

sf::Vector2f Astro::GetVelocity() { return m_velocity; }

void Astro::Pause(float dt)
{
	m_elapsedPauseTime += dt;
	if (m_elapsedPauseTime > 1000)
		m_state = WANDER;
}

void Astro::Wander(float dt)
{
	m_elapsedWanderTime += dt;

	if (m_elapsedWanderTime >= 3000)
	{
		int _rnd = rand() % 4;
		if (_rnd == 0)
			m_state = State::PAUSE;
		else if (_rnd == 1) {
			m_direction.x = -m_direction.x;
			m_velocity = sf::Vector2f(m_speed * m_direction.x, 0);
			if (m_direction.x > 0)
				m_sprite.setTexture(*m_texLeft);
			else
				m_sprite.setTexture(*m_texRight);
		}
		m_elapsedWanderTime = 0;
	}

	m_position += m_velocity;
}

void Astro::Evade()
{
	m_velocity.x = (m_speed * 2) * m_direction.x;
	m_position.x += m_velocity.x;
}

void Astro::Rise()
{
	m_position.y -= 1.0f;
	m_sprite.setPosition(m_position);
	if (m_position.y < 0)
	{
		m_state = State::MUTANT;
		m_sprite.setTexture(*m_mutantLeft);
		m_isMutant = true;
		m_isCaught = false;
		m_isSwarming = true;
	}
}

void Astro::Fall()
{
	if (m_position.y >= 0.9 * 600)
	{
		m_state = State::WANDER;
		if(m_direction.x < 0)
			m_sprite.setTexture(*m_texLeft);
		else
			m_sprite.setTexture(*m_texRight);

		m_isCaught = false;
		m_isFalling = false;
	}
	m_position.y += 1.0f;
	m_sprite.setPosition(m_position);
}

void Astro::MutantBehaviour()
{
	m_isSwarming = false;

	m_direction = m_player->getPosition() - m_position;
	float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
	m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
	m_velocity = sf::Vector2f(m_direction.x * (m_speed * 6), m_direction.y * (m_speed * 6));

	m_position += m_velocity;
}

void Astro::swarm()
{
	m_velocity += m_acceleration;
	double size = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (size > MAX_SPEED) {
		m_velocity = normalize(m_velocity) * MAX_SPEED;
		m_velocity = sf::Vector2f(m_velocity.x * MAX_SPEED, m_velocity.y * MAX_SPEED);
	}

	m_position += m_velocity;
	m_acceleration = sf::Vector2f(0, 0);
}

void Astro::WrapAround()
{
	if (m_position.x <= m_worldStart)
		m_position = sf::Vector2f(m_worldEnd, m_position.y);
	else if (m_position.x > m_worldEnd)
		m_position = sf::Vector2f(m_worldStart, m_position.y);
}

bool Astro::enemyDetected(){ return false; }

void Astro::evadeObstacle()
{
	if (m_isMutant)
	{
		m_direction = m_position - m_closestObstacle->getPosition();
		float length = sqrt((m_direction.x*m_direction.x) + (m_direction.y*m_direction.y));
		m_direction = sf::Vector2f(m_direction.x / length, m_direction.y / length);
		m_velocity = sf::Vector2f(m_direction.x * m_speed, m_direction.y * m_speed);
		m_position += m_velocity;
	}
}

void Astro::checkClosestObstacle()
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

void Astro::Swarm(std::vector<Astro> astronaut)
{
	sf::Vector2f R;
	int A = 300;
	int B = 15000;
	int N = 1;
	int M = 2;
	sf::Vector2f sum(0, 0);

	for (int i = 0; i < astronaut.size(); i++)
	{
		/*if (astronaut[i].isMutant())
		{*/
			R = sf::Vector2f(m_position.x - astronaut[i].getPosition().x, m_position.y - astronaut[i].getPosition().y);
			float D = std::sqrt(R.x * R.x + R.y * R.y);
			if (D > 0)
			{
				float U = -A / pow(D, N) + B / pow(D, M);
				normalize(R);
				R = sf::Vector2f(R.x * U, R.y * U);
				sum = sf::Vector2f(R.x + sum.x, R.y + sum.y);
			}
		//}
	}
	sum = sf::Vector2f(sum.x / astronaut.size() - 1, sum.y / astronaut.size() - 1);
	m_acceleration += sum;
	m_acceleration = sf::Vector2f(m_acceleration.x * 0.4f, m_acceleration.y * 0.4f);
}

sf::Vector2f Astro::Seek(sf::Vector2f vector) 
{
	sf::Vector2f desired;
	desired = sf::Vector2f(vector.x - m_position.x, vector.y - m_position.y);

	desired = normalize(desired);
	desired = sf::Vector2f(desired.x * MAX_SPEED, desired.y * MAX_SPEED);
	
	m_acceleration = sf::Vector2f(desired.x - m_velocity.x, desired.y - m_velocity.y);
	double size = sqrt((m_acceleration.x * m_acceleration.x) + (m_acceleration.y * m_acceleration.y));

	if (size > MAX_FORCE)
		m_acceleration = normalize(m_acceleration) * MAX_FORCE;

	return m_acceleration;
}

sf::Vector2f Astro::normalize(sf::Vector2f vector)
{
	sf::Vector2f tmp = vector;
	float mag = sqrt(vector.x * vector.x + vector.y * vector.y);

	if (mag > 0)
		tmp = sf::Vector2f(vector.x / mag, vector.y / mag);
	else
		tmp = tmp;

	return tmp;
}