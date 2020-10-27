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
	m_behaviours.boundary(m_position , m_playerSprite);

	movement();
}


/// <summary>
/// the draw function simply draws the player
/// </summary>
/// <param name="t_renderWindow"></param>
void Player::draw(sf::RenderWindow &t_renderWindow)
{

	t_renderWindow.draw(m_playerSprite);
}

/// <summary>
/// sets up the players sprite, loading the texture and setting the origin to the centre of the sprite
/// giving the player a random starting rotation 
/// </summary>
void Player::setUpPlayer()
{
	if (m_playerText.loadFromFile("ASSETS/IMAGES/playerShip.png"))
	{
		m_playerSprite.setTexture(m_playerText);
	}

	m_position = sf::Vector2f(750, 650);
	
	m_playerSprite.setOrigin(m_playerSprite.getGlobalBounds().width / 2, m_playerSprite.getGlobalBounds().height / 2);
	m_playerSprite.setScale(2, 2);

	m_speed = 0;
	m_orientation = 0;

	m_velocity = sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT) - m_position;

	m_orientation = m_behaviours.getNewOrientation(m_orientation, m_velocity);

	m_playerSprite.setPosition(m_position);
	m_playerSprite.setRotation(m_orientation);
}


void Player::movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_speed < m_maxSpeed || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_speed < m_maxSpeed)
	{
		m_speed++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_speed > 0 ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_speed > 0)
	{
		m_speed--;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_velocity = m_behaviours.rotate(rotationDeg, m_velocity);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_velocity = m_behaviours.rotate(-rotationDeg, m_velocity);
	}

	m_position +=  m_behaviours.unitVec(m_velocity) * m_speed;

	m_orientation = m_behaviours.getNewOrientation(m_orientation, m_velocity);

	m_playerSprite.setPosition(m_position);
	m_playerSprite.setRotation(m_orientation);
}

sf::Vector2f Player::getPos()
{
	return m_position;
}

sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}
