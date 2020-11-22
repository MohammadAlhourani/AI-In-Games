#include "Map.h"

Map::Map() : m_mapGraph(2500), m_vertexes(sf::LinesStrip, 2)
{
	if (!m_costFont.loadFromFile("Assets\\Font\\ariblk.ttf"))
	{
		std::cout << "error loading font" << std::endl;
	}

	neighbourAlgorithm();
	loadSquare();

	

}

Map::~Map()
{
}

void Map::draw(sf::RenderWindow& t_window)
{
	for(auto square : squares)
	{
		t_window.draw(square);
	}

	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		int currentNode = 0;

		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{

				t_window.draw(m_mapGraph.nodeIndex(currentNode)->m_data.m_costText);

				currentNode++;

			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		int currentNode = 0;

		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				if (m_mapGraph.nodeIndex(currentNode)->m_data.goal == false && m_mapGraph.nodeIndex(currentNode)->target() != nullptr)
				{
					sf::Vector2f vector1 = sf::Vector2f(m_mapGraph.nodeIndex(currentNode)->m_data.m_positionX, m_mapGraph.nodeIndex(currentNode)->m_data.m_positionY);

					sf::Vector2f vector2 = sf::Vector2f(m_mapGraph.nodeIndex(currentNode)->target()->m_data.m_positionX, m_mapGraph.nodeIndex(currentNode)->target()->m_data.m_positionY);

					m_vertexes[0].position = vector1;

					m_vertexes[1].position = vector2;


					t_window.draw(m_vertexes);
				}
				currentNode++;

			}
		}
	}
	
	
	
	
}

//creates the graph nodes and arcs between the nodes
void Map::neighbourAlgorithm()
{
	NodeData nodeData;
	int CurrentnodeIndex = 0;

	m_mapGraph.clearMarks();

	//creates the graph nodes 
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			nodeData.m_name = std::to_string(CurrentnodeIndex);

			nodeData.m_pathCost = 0;

			nodeData.m_positionX = (col * NODE_WIDTH) + (NodeSize / 2);
			nodeData.m_positionY = (row * NODE_HEIGHT) + (NodeSize / 2);

			nodeData.row = row;
			nodeData.col = col;
			nodeData.num = CurrentnodeIndex;

			nodeData.m_costText.setFont(m_costFont);

			nodeData.m_costText.setCharacterSize(10);
			nodeData.m_costText.setString(std::to_string(nodeData.m_pathCost));
			nodeData.m_costText.setFillColor(sf::Color::White);
			nodeData.m_costText.setPosition(sf::Vector2f(nodeData.m_positionX - (NodeSize / 2), nodeData.m_positionY - (NodeSize / 2)));

			m_mapGraph.addNode(nodeData, CurrentnodeIndex++);

		}
	}

	CurrentnodeIndex = 0;

	//links the graph node arcs to the nodes neighbours
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			
			// List all neighbors:
			for (int direction = 0; direction < 9; direction++)
			{
				if (direction == 4) continue; // Skip 4, this is ourself.

				int n_row = row + ((direction % 3) - 1); // Neighbor row
				int n_col = col + ((direction / 3) - 1); // Neighbor column

				// Check the bounds:
				if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS)
				{
					//find the neighbour nodes by checking the row and col against the nodes row and col in the graph
					int nodeIndex = 0;
					for (int Xpos = 0; Xpos < ROWS; Xpos++)
					{
						//std::cout << "row: " << row << std::endl;
						for (int Ypos = 0; Ypos < COLS; Ypos++)
						{
							if (m_mapGraph.nodeIndex(nodeIndex)->m_data.row == n_row &&
								m_mapGraph.nodeIndex(nodeIndex)->m_data.col == n_col)
							{
								m_mapGraph.addArc(CurrentnodeIndex,  nodeIndex , NodeSize);
							}
							nodeIndex++;
						}
					}
				}
			}
			CurrentnodeIndex++;
		}
	}
}

void Map::loadSquare()
{
	sf::RectangleShape theSquare;

	squares.clear();

	int nodeIndex = 0;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (m_mapGraph.nodeIndex(nodeIndex)->m_data.passable == true && 
				m_mapGraph.nodeIndex(nodeIndex)->m_data.start == false && 
				m_mapGraph.nodeIndex(nodeIndex)->m_data.goal == false)
			{
				theSquare = sf::RectangleShape(sf::Vector2f(NODE_WIDTH, NODE_HEIGHT));
				theSquare.setFillColor(sf::Color(0, 0, 0, 150));
				theSquare.setOutlineThickness(1);
				theSquare.setOutlineColor(sf::Color(255, 255, 255, 255));
				theSquare.setPosition(col * NODE_WIDTH, row * NODE_HEIGHT);
			}
			else if (m_mapGraph.nodeIndex(nodeIndex)->m_data.start == true && m_mapGraph.nodeIndex(nodeIndex)->m_data.passable == true)
			{
				theSquare = sf::RectangleShape(sf::Vector2f(NODE_WIDTH, NODE_HEIGHT));
				theSquare.setFillColor(sf::Color(0, 255, 0, 150));
				theSquare.setOutlineThickness(1);
				theSquare.setOutlineColor(sf::Color(0, 0, 0, 255));
				theSquare.setPosition(col * NODE_WIDTH, row * NODE_HEIGHT);
			}
			else if (m_mapGraph.nodeIndex(nodeIndex)->m_data.goal == true && m_mapGraph.nodeIndex(nodeIndex)->m_data.passable == true)
			{
				theSquare = sf::RectangleShape(sf::Vector2f(NODE_WIDTH, NODE_HEIGHT));
				theSquare.setFillColor(sf::Color(255, 255, 0, 150));
				theSquare.setOutlineThickness(1);
				theSquare.setOutlineColor(sf::Color(0, 0, 0, 255));
				theSquare.setPosition(col * NODE_WIDTH, row * NODE_HEIGHT);
			}
			else
			{
				theSquare = sf::RectangleShape(sf::Vector2f(NODE_WIDTH, NODE_HEIGHT));
				theSquare.setFillColor(sf::Color(255, 255, 255, 150));
				theSquare.setOutlineThickness(1);
				theSquare.setOutlineColor(sf::Color(0, 0, 0, 255));
				theSquare.setPosition(col * NODE_WIDTH, row * NODE_HEIGHT);
			}

			squares.push_back(theSquare);

			nodeIndex++;
		}
	}
}



void Map::resetNodes()
{
	neighbourAlgorithm();
}

NodeData Map::getNodeData(int t_index)
{
	return m_mapGraph.nodeIndex(t_index)->m_data;
}

void Map::pathFind(int t_startNode, int t_GoalNode, std::vector<GraphNode<NodeData, int>>& t_path)
{
	m_mapGraph.aStar(m_mapGraph.nodeIndex(t_startNode), m_mapGraph.nodeIndex(t_GoalNode), t_path, {});
}


void Map::setStart(sf::Vector2f t_pos)
{
	int currentNode = 0;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{

			m_mapGraph.nodeIndex(currentNode)->m_data.start = false;
			currentNode++;

		}
	}
	m_mapGraph.nodeIndex(getXY(t_pos))->m_data.start = true;

	loadSquare();
}

void Map::setGoal(sf::Vector2f t_pos)
{

	int currentNode = 0;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{

			m_mapGraph.nodeIndex(currentNode)->m_data.goal = false;
			currentNode++;

		}
	}

	m_mapGraph.nodeIndex(getXY(t_pos))->m_data.goal = true;

	m_mapGraph.nodeCosts(m_mapGraph.nodeIndex(getGoal()));

	loadSquare();

	setVectorField();

	vectorFieldPathing();


	currentNode = 0;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (m_mapGraph.nodeIndex(currentNode)->m_data.passable == true &&
				m_mapGraph.nodeIndex(currentNode)->m_data.start == false && 
				m_mapGraph.nodeIndex(currentNode)->m_data.goal == false)
			{
				squares[currentNode].setFillColor(sf::Color(0 + (255 - m_mapGraph.nodeIndex(currentNode)->m_data.m_pathCost * 5), 0, 0));
			}
			currentNode++;

		}
	}

	for (auto node : m_pathToGoal)
	{
		if (node.m_data.start == false && node.m_data.goal == false)
		{
			squares[node.m_data.num].setFillColor(sf::Color(0, 255, 255, 255));
		}
	}

}

int Map::getXY(sf::Vector2f t_pos)
{
	auto num = floor(t_pos.x / NODE_WIDTH) + (floor(t_pos.y / NODE_HEIGHT) * 50);

	return num;
}

int Map::getStart()
{

	int currentNode = 0;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{

			if (m_mapGraph.nodeIndex(currentNode)->m_data.start == true)
			{
				return currentNode;
			}
			currentNode++;

		}
	}
	
	return 0;
}

int Map::getGoal()
{

	int currentNode = 0;
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{

			if (m_mapGraph.nodeIndex(currentNode)->m_data.goal == true)
			{
				return currentNode;
			}
			currentNode++;

		}
	}
	return 0;
}

void Map::setImpassable(sf::Vector2f t_pos)
{
	if (m_mapGraph.nodeIndex(getXY(t_pos))->m_data.passable == true)
	{
		m_mapGraph.nodeIndex(getXY(t_pos))->m_data.passable = false;
	}
	else
	{
		m_mapGraph.nodeIndex(getXY(t_pos))->m_data.passable = true;
	}

	loadSquare();
}

void Map::setVectorField()
{
	int currentNode = 0;


	m_mapGraph.calHeuristic(m_mapGraph.nodeIndex(getGoal()));
	m_mapGraph.setTargetsNull();

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (m_mapGraph.nodeIndex(currentNode)->m_data.passable == true)
			{
				auto iter = m_mapGraph.nodeIndex(currentNode)->arcList().begin();
				auto endIter = m_mapGraph.nodeIndex(currentNode)->arcList().end();

				for (; iter != endIter; iter++)
				{
					if (m_mapGraph.nodeIndex(currentNode)->target() == nullptr && m_mapGraph.nodeIndex(currentNode)->m_data.goal == false && (*iter).node()->m_data.passable == true)
					{
						m_mapGraph.nodeIndex(currentNode)->setTarget((*iter).node());
					}
					else if (m_mapGraph.nodeIndex(currentNode)->m_data.goal == true)
					{
						continue;
					}
					else if (m_mapGraph.nodeIndex(currentNode)->target() != nullptr && (*iter).node()->m_data.passable == true)
					{
						if ((*iter).node()->m_data.m_hueristic < m_mapGraph.nodeIndex(currentNode)->target()->m_data.m_hueristic)
						{
							m_mapGraph.nodeIndex(currentNode)->setTarget((*iter).node());
						}
					}
				}
			}
			currentNode++;
		}
	}
}

void Map::vectorFieldPathing()
{
	auto iter = m_mapGraph.nodeIndex(getStart());

	m_pathToGoal.clear();
	m_vectorField.clear();
	
	for (; iter != m_mapGraph.nodeIndex(getGoal());)
	{
		if (iter->target() != nullptr)
		{
			auto temp = *(iter->target());

			m_pathToGoal.push_back(temp);

			sf::Vector2f vector = sf::Vector2f(iter->target()->m_data.m_positionX - iter->m_data.m_positionX, iter->target()->m_data.m_positionY - iter->m_data.m_positionY);

			m_vectorField.push_back(vector);



			iter = iter->target();
		}
		else
		{
			break;
		}
	}
}


