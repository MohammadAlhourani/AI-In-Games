#include "Player.h"

Player::Player()
{
	setUpPlayer();
}

Player::~Player()
{
}

void Player::update(sf::Time t_deltaTime)
{
	boundary();

	movement();
}

void Player::draw(sf::RenderWindow &t_renderWindow)
{

	t_renderWindow.draw(m_playerSprite);
}

void Player::setUpPlayer()
{
	if (m_playerText.loadFromFile("ASSETS/IMAGES/playerShip.png"))
	{
		m_playerSprite.setTexture(m_playerText);
	}

	m_position = sf::Vector2f(750, 650);
	
	m_playerSprite.setOrigin(19, 23);
	m_playerSprite.setScale(2, 2);

	m_speed = 0;
	m_orientation = 0;

	m_velocity = sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT) - m_position;

	m_orientation = getNewOrientation(m_orientation, m_velocity);

	m_playerSprite.setPosition(m_position);
	m_playerSprite.setRotation((m_orientation * (180.0f / 3.14f)) + 180);
}

void Player::boundary()
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

void Player::movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_speed < m_maxSpeed)
	{
		m_speed++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_speed > 0)
	{
		m_speed--;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotate(rotationDeg);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotate(-rotationDeg);
	}

	m_position += unitVec(m_velocity) * m_speed;

	m_orientation = getNewOrientation(m_orientation, m_velocity);

	m_playerSprite.setPosition(m_position);
	m_playerSprite.setRotation(m_orientation + 180);
}

void Player::rotate(float t_degrees)
{
	float radians = t_degrees * (3.14f / 180.0f);

	const float cos = std::cos(radians); 
	const float sin = std::sin(radians);

	m_velocity.x = ((m_velocity.x * cos) - (m_velocity.y * sin));
	m_velocity.y = ((m_velocity.x * sin) + (m_velocity.y * cos));
}

float Player::getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity)
{
	if(Length(t_velocity) > 0) 
	{
		return ((atan2(-t_velocity.x, t_velocity.y)) * (180.0f / 3.14f));
	}
	else
	{
		return t_currentOrientation;
	}
}

float Player::Length(sf::Vector2f t_vect)
{
	float length = sqrt((t_vect.x * t_vect.x) + (t_vect.y * t_vect.y));
	return length;
}

sf::Vector2f Player::unitVec(sf::Vector2f t_vect)
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

