#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "NodeData.h"


class Map
{
public:
	/// <summary>
	/// Map Constructor
	/// </summary>
	Map();

	/// <summary>
	/// Map Deconstructor
	/// </summary>
	~Map();

	/// <summary>
	/// Draws the map
	/// </summary>
	void draw(sf::RenderWindow& t_window);



	/// <summary>
	/// Creates the graph nodes and arcs
	/// </summary>
	void neighbourAlgorithm();

	/// <summary>
	/// Creates squares on nodes for A* Testing / Checking
	/// </summary>
	void loadSquare();

	void setStart(sf::Vector2f t_pos);

	void setGoal(sf::Vector2f t_pos);

	int getXY(sf::Vector2f t_pos);

	int getStart();

	int getGoal();

	void setImpassable(sf::Vector2f t_pos);

	void setVectorField();

	void vectorFieldPathing();

private:


	Graph<NodeData, int> m_mapGraph; //Graph of nodes for the map

	std::vector<sf::RectangleShape> squares; //Vector of squares 

	sf::Font m_costFont;

	const int NODE_WIDTH = 16;
	const int NODE_HEIGHT = 16;

	int const ROWS = 50; //Number of rows in the graph
	int const COLS = 50; //Number of columns in the graph

	int NodeSize = 16; 

	std::vector<GraphNode<NodeData, int>> m_pathToGoal;

	std::vector<sf::Vector2f> m_vectorField;

	sf::VertexArray m_vertexes;
};