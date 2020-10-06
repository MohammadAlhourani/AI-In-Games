#include "Enemy.h"

Enemy::Enemy()
{
	setUpEnemy();
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Time t_deltaTime)
{
	boundary();
	movement();
}

void Enemy::draw(sf::RenderWindow &t_renderWindow)
{
	t_renderWindow.draw(m_enemySprite);
}

void Enemy::setUpEnemy()
{

	if (m_enemyText.loadFromFile("ASSETS/IMAGES/enemyShip.png"))
	{
		m_enemySprite.setTexture(m_enemyText);
	}

	m_enemySprite.setOrigin(26, 27);
	m_enemySprite.setScale(2, 2);

	m_position = sf::Vector2f(500, 650);

	m_orientation = 0;
	m_speed = 5;

	m_velocity = sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT) - m_position;
	m_orientation = getNewOrientation(m_orientation, m_velocity);

	m_enemySprite.setPosition(m_position);
	m_enemySprite.setRotation(m_orientation + 180);
}

void Enemy::boundary()
{
	if (m_position.x < 0)
	{
		m_position.x = WINDOW_WIDTH;
	}
	else if (m_position.x > WINDOW_WIDTH)
	{
		m_position.x = 0;
	}

	if (m_position.y < 0)
	{
		m_position.y = WINDOW_HEIGHT;
	}
	else if (m_position.y > WINDOW_HEIGHT)
	{
		m_position.y = 0;
	}
}

void Enemy::movement()
{
	m_velocity = unitVec(m_velocity) * m_speed;

	m_position += m_velocity;

	m_enemySprite.setPosition(m_position);
}

float Enemy::getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity)
{
	if (Length(t_velocity) > 0)
	{
		return ((atan2(-t_velocity.x, t_velocity.y)) * (180.0f / 3.14f));
	}
	else
	{
		return t_currentOrientation;
	}
}

sf::Vector2f Enemy::unitVec(sf::Vector2f t_vect)
{
	sf::Vector2f unit;

	float length = Length(t_vect);

	if (length != 0)
	{
		unit.x = t_vect.x / length;

		unit.y = t_vect.y / length;

		return unit;
	}
	else
	{
		return t_vect;
	}
}

float Enemy::Length(sf::Vector2f t_vect)
{
	float length = sqrt((t_vect.x * t_vect.x) + (t_vect.y * t_vect.y));
	return length;
}
