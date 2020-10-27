#pragma once

#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Behaviours.h"

class Player
{
public:
	Player();
	~Player();

	void update(sf::Time t_deltaTime);

	void draw(sf::RenderWindow &t_renderWindow);

	void setUpPlayer();

	void movement();

	sf::Vector2f getPos();

	sf::Vector2f getVelocity();


private:

	//the player sprite
	sf::Sprite m_playerSprite;

	//the player texture
	sf::Texture m_playerText;

	//the behaviours class used for equations
	Behaviours m_behaviours;

	//the players position
	sf::Vector2f m_position;

	//the players velocity
	sf::Vector2f m_velocity;


	//the players orientation/rotation
	float m_orientation;

	//the max speed the player can reach
	float m_maxSpeed = 15;

	float m_speed; // the current speed of the player

	//how quickly the player can rotate 
	float rotationDeg = 3;


};

