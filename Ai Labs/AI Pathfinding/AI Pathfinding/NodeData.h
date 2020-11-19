#pragma once
#include  <string>

// ---------------------------------------------------------------------
//  Name:           NodeData
//  Description:    A simple struct to encapsulate all the node data.
//                  Add or remove fields as required.               
// ---------------------------------------------------------------------
struct NodeData
{
	std::string m_name;
	int m_pathCost;

	int row;
	int col;
	int num;

	bool start = false;

	bool goal = false;

	bool passable = true;

	sf::Text m_costText;

	float m_hueristic;
	float m_positionX;
	float m_positionY;
};
