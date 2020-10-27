/// <summary>
/// @author Mohammad Alhourani
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32U }, "Ai Lab 1" },
	m_exitGame{false} //when true game will exit
{
	//setting up the enemies and inserting them into the vector array

		Enemy* temp = new Enemy(0);

		m_enemies.push_back(*temp);

		temp = new Enemy(0);

		temp->setSlow();

		m_enemies.push_back(*temp);

		temp = new Enemy(2);

		m_enemies.push_back(*temp);

		temp = new Enemy(3);

		m_enemies.push_back(*temp);

		temp = new Enemy(4);

		m_enemies.push_back(*temp);
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but method needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	// updating the player
	m_player.update(t_deltaTime);


	//updating the enemies passing in the players position and velocity
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].getPlayerPos(m_player.getPos());
		m_enemies[i].getPlayerVelocity(m_player.getVelocity());
		m_enemies[i].update(t_deltaTime);
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	//drawing the player
	m_player.draw(m_window);

	//drawing the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].draw(m_window);
	}

	m_window.display();
}

