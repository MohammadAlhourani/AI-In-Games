#pragma once

#include <SFML/Graphics.hpp>

#include "Globals.h"

class Player
{
public:
	Player();
	~Player();

	void update(sf::Time t_deltaTime);

	void draw(sf::RenderWindow &t_renderWindow);

	void setUpPlayer();

	void boundary();

	void movement();

	void rotate(float t_degrees);

	float getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity);

	sf::Vector2f unitVec(sf::Vector2f t_vect);

	float Length(sf::Vector2f t_vect);

private:

	sf::Sprite m_playerSprite;

	sf::Texture m_playerText;

	sf::Vector2f m_position;

	sf::Vector2f m_velocity;

	sf::Vector2f m_direction;

	float m_orientation;

	float m_maxSpeed = 15;

	float m_speed; // the current speed of the player

	float rotationDeg = 1;


};

