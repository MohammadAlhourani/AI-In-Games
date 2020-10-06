#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void update(sf::Time t_deltaTime);

	void draw(sf::RenderWindow &t_renderWindow);

	void setUpEnemy();

	void boundary();

	void movement();

	float getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity);

	sf::Vector2f unitVec(sf::Vector2f t_vect);

	float Length(sf::Vector2f t_vect);

private:

	sf::Sprite m_enemySprite;
	sf::Texture m_enemyText;

	sf::Vector2f m_direction;

	sf::Vector2f m_position;

	sf::Vector2f m_velocity;

	float m_orientation;

	float m_maxSpeed;

	float m_speed;

};

