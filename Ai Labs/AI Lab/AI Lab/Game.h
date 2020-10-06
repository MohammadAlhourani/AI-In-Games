#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window; // main SFML window

	bool m_exitGame; // control exiting game

	Player m_player;
	Enemy m_enemy;

};

#endif // !GAME_HPP

