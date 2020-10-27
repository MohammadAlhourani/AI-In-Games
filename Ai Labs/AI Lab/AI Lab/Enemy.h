#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Globals.h"
#include "Behaviours.h"

//the enemy behaviours
enum class mode
{
	Arrive,
	Flee,
	Seek,
	Wander,
	Pursue

};

class Enemy
{
public:
	Enemy();
	Enemy(int t_mode);
	~Enemy();

	void update(sf::Time t_deltaTime);

	void draw(sf::RenderWindow &t_renderWindow);

	void setUpEnemy();

	void detectPlayer();

	void movement(sf::Time t_deltaTime);

	void getPlayerPos(sf::Vector2f t_playerPos);

	void getPlayerVelocity(sf::Vector2f t_playerVelocity);

	void setActive();

	void setSlow();

private:

	sf::Sprite m_enemySprite;
	sf::Texture m_enemyText;

	sf::CircleShape m_visionCone;

	Behaviours m_behaviours;

	sf::Vector2f m_direction;

	sf::Vector2f m_position;

	sf::Vector2f m_velocity;

	sf::Vector2f m_acceleration;

	float m_orientation;

	float m_maxSpeed;

	float m_speed;

	sf::Vector2f m_playerPos;
	sf::Vector2f m_playerVelocity;

	float m_steerTimer;

	mode m_mode;

	float m_visRadius;

	bool m_active;

	sf::Text m_label;
	sf::Font m_font;

};

