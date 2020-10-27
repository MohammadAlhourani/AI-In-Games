#include "Enemy.h"

//default constructer
Enemy::Enemy()
{
	m_mode = mode::Wander;
	setUpEnemy();
}

//for selecting a partcular movement behaviour based of an number  
Enemy::Enemy(int t_mode)
{
	m_mode = static_cast<mode>(t_mode);
	setUpEnemy();
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Time t_deltaTime)
{

	setActive();

	//only updates if the enemy is active
	if (m_active == true)
	{
		m_behaviours.boundary(m_position, m_enemySprite);
		movement(t_deltaTime);
		detectPlayer();
	}
}

void Enemy::draw(sf::RenderWindow &t_renderWindow)
{
	//only draws if the enemy is active
	if (m_active == true)
	{
		t_renderWindow.draw(m_label);
		t_renderWindow.draw(m_visionCone);
		t_renderWindow.draw(m_enemySprite);
	}
}

void Enemy::setUpEnemy()
{
	//sets the ships sprite and label based on the behaviour 
	switch (m_mode)
	{
	case mode::Arrive:
		if (m_enemyText.loadFromFile("ASSETS/IMAGES/enemyship1.png"))
		{
			m_enemySprite.setTexture(m_enemyText);
		}

		m_direction = sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);

		m_label.setString("ARRIVE");

		break;
	case mode::Flee:
		if (m_enemyText.loadFromFile("ASSETS/IMAGES/enemyship2.png"))
		{
			m_enemySprite.setTexture(m_enemyText);
		}

		m_label.setString("FLEE");

		break;
	case mode::Seek:
		if (m_enemyText.loadFromFile("ASSETS/IMAGES/enemyship3.png"))
		{
			m_enemySprite.setTexture(m_enemyText);
		}

		m_direction = sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);

		m_velocity = sf::Vector2f(0, 0);

		m_acceleration = sf::Vector2f(0, 0);

		m_label.setString("SEEK");

		break;
	case mode::Wander:
		if (m_enemyText.loadFromFile("ASSETS/IMAGES/enemyship4.png"))
		{
			m_enemySprite.setTexture(m_enemyText);
		}

		m_label.setString("WANDER");

		break;
	case mode::Pursue:
		if (m_enemyText.loadFromFile("ASSETS/IMAGES/enemyship5.png"))
		{
			m_enemySprite.setTexture(m_enemyText);
		}

		m_label.setString("PURSUE");

		break;
	default:
		break;
	}

	if (m_font.loadFromFile("ASSETS/FONTS/ariblk.ttf"))
	{
		m_label.setFont(m_font);
	}

	m_enemySprite.setOrigin(m_enemySprite.getGlobalBounds().width / 2, m_enemySprite.getGlobalBounds().height / 2);
	m_enemySprite.setScale(2, 2);

	m_position = sf::Vector2f(500, 650);

	m_maxSpeed = 5;

	m_steerTimer = 0;

	m_orientation = 0;
	m_speed = m_maxSpeed;

	m_active = false;

	m_label.setFillColor(sf::Color::White);
	m_label.setPosition(m_position + sf::Vector2f(0,20));
	m_label.setCharacterSize(30);

	//vision cone radius
	m_visRadius = 100;

	//sets the vision cone to look like a triangle 
	//sets its colour and makes it slightly opaque	
	m_visionCone.setPointCount(3);
	m_visionCone.setFillColor(sf::Color(255,0,0,150));
	m_visionCone.setRadius(m_visRadius);
	m_visionCone.setPosition(m_position);
	m_visionCone.setOrigin((m_visRadius), 0);
	m_visionCone.setRotation(m_orientation);


	m_enemySprite.setPosition(m_position);
}

void Enemy::detectPlayer()
{
	sf::Vector2f distance = m_position - m_playerPos; //Checks what direction player is to the enemy

	float distnceMag = m_behaviours.Length(distance); //Gets the distance of the player from the enemy

	float angle = m_behaviours.angleBetween(distance, -m_velocity);  // Gets the angle from the enemy to the player

	if (distnceMag <= (m_visRadius * 2)) //If the playeris within distance of the vision cone
	{
		if (angle >= -45 && angle <= 45) //If the player is in the same angle as the vision cone
		{
			m_visionCone.setFillColor(sf::Color(255, 0, 0, 150));
		}
		else
		{
			m_visionCone.setFillColor(sf::Color(0, 255, 0, 150));
		}
	}
	else // if the player is out of the vision cone reach
	{
		m_visionCone.setFillColor(sf::Color(0, 255, 0, 150));
	}
}

void Enemy::movement(sf::Time t_deltaTime)
{
	switch (m_mode)
	{
	case mode::Arrive:
		//m_behaviours.arrive(m_position , m_direction , m_velocity , m_speed);
		m_behaviours.dynamicArrive(m_position, m_playerPos, m_velocity, m_acceleration, m_speed, m_maxSpeed);
		break;
	case mode::Flee:
		//m_behaviours.flee(m_position, m_playerPos, m_velocity, m_speed);
		m_behaviours.dynamicFlee(m_position, m_playerPos, m_velocity, m_acceleration, m_speed);
		break;
	case mode::Seek:
		//m_behaviours.seek(m_position, m_direction, m_velocity, m_speed);
		m_behaviours.dynamicSeek(m_position, m_playerPos,m_velocity,m_acceleration,m_speed);
		break;
	case mode::Wander:
		//m_behaviours.wander(t_deltaTime, m_position, m_velocity, m_speed, m_steerTimer);
		m_behaviours.dynamicWander(m_position, m_velocity, m_acceleration, m_speed);
		break;
	case mode::Pursue:
		m_behaviours.pursue(m_position, m_playerPos, m_playerVelocity, m_velocity, m_acceleration, m_speed, 0.5);
		break;
	default:
		break;
	}

	//if the ships speed is zero not to rotate the sprite or change its position
	if (m_speed > 0)
	{
		m_orientation = m_behaviours.getNewOrientation(m_orientation, m_velocity);

		m_enemySprite.setPosition(m_position);
		m_enemySprite.setRotation(m_orientation);
	}


	//gives the ship a random point to travel to
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		m_direction = sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
	}


	//sets the label position be slighlty below the ship
	m_label.setPosition(m_position + sf::Vector2f(0, 20));

	m_visionCone.setRotation(m_orientation + 180);
	m_visionCone.setPosition(m_position);
}


/// <summary>
/// sets the players position
/// </summary>
/// <param name="t_playerPos"></param>
void Enemy::getPlayerPos(sf::Vector2f t_playerPos)
{
	m_playerPos = t_playerPos;
}

/// <summary>
/// sets the players velocity
/// </summary>
/// <param name="t_playerVelocity"></param>
void Enemy::getPlayerVelocity(sf::Vector2f t_playerVelocity)
{
	m_playerVelocity = t_playerVelocity;
}


/// <summary>
/// sets the ship active or inactive
/// </summary>
void Enemy::setActive()
{
	switch (m_mode)
	{
	case mode::Arrive:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (m_active == false)
			{
				m_active = true;
			}
			else
			{
				m_active = false;
			}
		}
		break;
	case mode::Flee:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (m_active == false)
			{
				m_active = true;
			}
			else
			{
				m_active = false;
			}
		}
		break;
	case mode::Seek:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			if (m_active == false)
			{
				m_active = true;
			}
			else
			{
				m_active = false;
			}
		}
		break;
	case mode::Wander:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			if (m_active == false)
			{
				m_active = true;
			}
			else
			{
				m_active = false;
			}
		}
		break;
	case mode::Pursue:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			if (m_active == false)
			{
				m_active = true;
			}
			else
			{
				m_active = false;
			}
		}
		break;
	default:
		break;
	}
}

/// <summary>
/// slows down the ship cutting its max speed in half
/// </summary>
void Enemy::setSlow()
{
	m_maxSpeed = 2.5;

	m_speed = m_maxSpeed;

	m_label.setString(m_label.getString() + " Slow");
}


