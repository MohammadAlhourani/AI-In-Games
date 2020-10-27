#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Globals.h"

class Behaviours
{
public:
	Behaviours();
	~Behaviours();

	float Length(const sf::Vector2f t_vect);

	float getNewOrientation(const float t_currentOrientation, const sf::Vector2f t_velocity);

	float getRotation(sf::Vector2f t_vect);

	sf::Vector2f unitVec(const sf::Vector2f t_vect);

	sf::Vector2f rotate(float t_degrees, sf::Vector2f t_velocity);

	sf::Vector2f steer(sf::Vector2f t_velocity, const int t_max, const int t_min);

	float angleBetween(const sf::Vector2f t_vect1,const sf::Vector2f t_vect2);

	void boundary(sf::Vector2f& t_position , sf::Sprite t_charSprite);

	int random(int t_max, int t_min);


	//goes directly to a target location
	void seek(sf::Vector2f &t_position, sf::Vector2f t_target, sf::Vector2f& t_velocity, float &t_speed);

	//moves away from a target or location
	void flee(sf::Vector2f &t_position, sf::Vector2f t_fleeFrom, sf::Vector2f& t_velocity, float &t_speed);

	//goes towards a location or target but slows down and stop when reaching
	void arrive(sf::Vector2f &t_position, sf::Vector2f t_target, sf::Vector2f& t_velocity, float &t_speed);

	//traverses randomly changing direction every 3 seconds
	void wander(sf::Time t_deltaTime, sf::Vector2f &t_position, sf::Vector2f& t_velocity, float &t_speed, float &t_timer);


	void dynamicSeek(sf::Vector2f& t_position, sf::Vector2f t_target, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed);

	void dynamicFlee(sf::Vector2f& t_position, sf::Vector2f t_fleeFrom, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed);

	void dynamicArrive(sf::Vector2f& t_position, sf::Vector2f t_target, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed , float t_maxSpeed);

	void dynamicWander(sf::Vector2f& t_position, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration , float& t_speed);
	
	void pursue(sf::Vector2f& t_position,sf::Vector2f t_target, sf::Vector2f t_targetVelocity, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed , float t_maxTimePred);



private:

	//convert radians to degrees
	const float m_radToDeg = (180.0f / 3.14f);

	//converts degrees to radians
	const float m_degToRad = (3.14f / 180.0f);
};



