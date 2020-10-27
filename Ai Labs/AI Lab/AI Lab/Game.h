#ifndef GAME_HPP
#define GAME_HPP

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

	//the player
	Player m_player;

	//vector array for the enemies
	std::vector<Enemy> m_enemies;

};

#endif // !GAME_HPP

