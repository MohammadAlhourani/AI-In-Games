#include "Behaviours.h"

Behaviours::Behaviours()
{
}

Behaviours::~Behaviours()
{
}

float Behaviours::Length(const sf::Vector2f t_vect)
{
	float length = sqrt((t_vect.x * t_vect.x) + (t_vect.y * t_vect.y));
	return length;
}

float Behaviours::getNewOrientation(const float t_currentOrientation, const sf::Vector2f t_velocity)
{
	if (Length(t_velocity) > 0)
	{
		return ((atan2(-t_velocity.x, t_velocity.y)) * m_radToDeg + 180);
	}
	else
	{
		return t_currentOrientation + 180;
	}
}

float Behaviours::getRotation(sf::Vector2f t_vect)
{
	if (Length(t_vect) > 0)
	{
		return ((atan2(t_vect.x, t_vect.y)) * m_radToDeg);
	}
	else
	{
		return 0;
	}
}

sf::Vector2f Behaviours::unitVec(const sf::Vector2f t_vect)
{
	sf::Vector2f unit = sf::Vector2f(0, 0);

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

sf::Vector2f Behaviours::rotate(float t_degrees, sf::Vector2f t_velocity)
{
	float radians = t_degrees * m_degToRad;

	const float cos = std::cos(radians);
	const float sin = std::sin(radians);

	t_velocity.x = ((t_velocity.x * cos) - (t_velocity.y * sin));
	t_velocity.y = ((t_velocity.x * sin) + (t_velocity.y * cos));

	return t_velocity;
}

sf::Vector2f Behaviours::steer(sf::Vector2f t_velocity, const int t_max, const int t_min)
{
	int randNum = rand() % ((t_max - t_min) + 1) + t_min;

	t_velocity += rotate(randNum, t_velocity);

	return t_velocity;
}

float Behaviours::angleBetween(const sf::Vector2f t_vect1, const sf::Vector2f t_vect2)
{
	float dotProd = (t_vect1.x * t_vect2.x) + (t_vect1.y * t_vect2.y);

	float cosine = dotProd / (Length(t_vect1) * Length(t_vect2));

	float angle = (std::acos(cosine)) * m_radToDeg;

	return angle;
}

void Behaviours::boundary(sf::Vector2f& t_position, sf::Sprite t_charSprite)
{
	if (t_position.x < 0 - t_charSprite.getGlobalBounds().width)
	{
		t_position.x = WINDOW_WIDTH;
	}
	else if (t_position.x > WINDOW_WIDTH + t_charSprite.getGlobalBounds().width)
	{
		t_position.x = 0;
	}

	if (t_position.y < 0 - t_charSprite.getGlobalBounds().height)
	{
		t_position.y = WINDOW_HEIGHT;
	}
	else if (t_position.y > WINDOW_HEIGHT + t_charSprite.getGlobalBounds().height)
	{
		t_position.y = 0;
	}
}

int Behaviours::random(int t_max, int t_min)
{
	return rand() % ((t_max - t_min) + 1) + t_min;
}

void Behaviours::seek(sf::Vector2f& t_position, sf::Vector2f t_target, sf::Vector2f& t_velocity, float& t_speed)
{
	t_velocity = t_target - t_position;

	t_velocity = unitVec(t_velocity) * t_speed;

	t_position += t_velocity;
}

void Behaviours::flee(sf::Vector2f& t_position, sf::Vector2f t_fleeFrom, sf::Vector2f& t_velocity, float& t_speed)
{
	t_speed = 1;

	t_velocity = t_position - t_fleeFrom;

	t_velocity = unitVec(t_velocity) * t_speed;

	t_position += t_velocity;
}

void Behaviours::arrive(sf::Vector2f& t_position, sf::Vector2f t_target, sf::Vector2f& t_velocity, float& t_speed)
{
	if (Length(t_target - t_position) < 45)
	{
		t_speed = 0;
	}
	else if (Length(t_target - t_position) < 90)
	{
		t_speed = 2.5;

		t_velocity = t_target - t_position;

		t_velocity = unitVec(t_velocity) * t_speed;

		t_position += t_velocity;
	}
	else
	{
		t_speed = 5;

		t_velocity = t_target - t_position;

		t_velocity = unitVec(t_velocity) * t_speed;

		t_position += t_velocity;
	}
}

void Behaviours::wander(sf::Time t_deltaTime, sf::Vector2f& t_position, sf::Vector2f& t_velocity, float& t_speed, float& t_timer)
{
	t_timer += t_deltaTime.asSeconds();

	if (t_timer > 1)
	{
		t_velocity = steer(t_velocity, 45, -45);

		t_timer = 0;
	}

	t_velocity = unitVec(t_velocity) * t_speed;

	t_position += t_velocity;
}

void Behaviours::dynamicSeek(sf::Vector2f& t_position, sf::Vector2f t_target, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed)
{
	t_acceleration = t_target - t_position;

	t_velocity += t_acceleration;

	t_velocity = unitVec(t_velocity) * t_speed;

	t_position += t_velocity;
}

void Behaviours::dynamicFlee(sf::Vector2f& t_position, sf::Vector2f t_fleeFrom, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed)
{
	t_speed = 1;

	t_acceleration = t_position - t_fleeFrom;

	t_velocity += t_acceleration;

	t_velocity = unitVec(t_velocity) * t_speed;

	t_position += t_velocity;
}

void Behaviours::dynamicArrive(sf::Vector2f& t_position, sf::Vector2f t_target, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed, float t_maxSpeed)
{
	if (Length(t_target - t_position) < 45)
	{
		t_speed = 0;
	}
	else if (Length(t_target - t_position) < 90)
	{
		t_speed = (t_maxSpeed / 2);

		t_acceleration = t_target - t_position;

		t_velocity += t_acceleration;

		t_velocity = unitVec(t_velocity) * t_speed;

		t_position += t_velocity;
	}
	else
	{
		t_speed = t_maxSpeed;

		t_acceleration = t_target - t_position;

		t_velocity += t_acceleration;

		t_velocity = unitVec(t_velocity) * t_speed;

		t_position += t_velocity;
	}
}

void Behaviours::dynamicWander(sf::Vector2f& t_position, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed)
{
	sf::Vector2f target;

	if (Length(t_velocity) == 0)
	{
		target = sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);

		t_acceleration = target - t_position;

		t_velocity += t_acceleration;
	}

	target = t_position + rotate(random(5, -5), t_velocity) + t_velocity;

	dynamicSeek(t_position, target, t_velocity, t_acceleration, t_speed);
}

void Behaviours::pursue(sf::Vector2f& t_position, sf::Vector2f t_target, sf::Vector2f t_targetVelocity, sf::Vector2f& t_velocity, sf::Vector2f& t_acceleration, float& t_speed, float t_maxTimePred)
{
	auto direction = t_target - t_position;

	auto distance = Length(direction);

	auto speed = Length(t_velocity);

	float timePred;

	if (speed <= distance / t_maxTimePred)
	{
		timePred = t_maxTimePred;
	}
	else
	{
		timePred = distance / speed;
	}

	auto newTarget = t_target + t_targetVelocity * timePred;

	dynamicSeek(t_position, newTarget, t_velocity, t_acceleration, t_speed);
}



