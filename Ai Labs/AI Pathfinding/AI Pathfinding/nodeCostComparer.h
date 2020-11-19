#pragma once


template <class NodeType, class ArcType> class GraphNode;

template<class NodeType, class ArcType>
class NodeSearchCostComparer 
{ 
public: 
	
	typedef GraphNode<NodeType, ArcType> Node;

	bool operator()(Node* n1, Node* n2)
	{
		return n1->m_data.m_pathCost + n1->m_data.m_hueristic > n2->m_data.m_pathCost + n2->m_data.m_hueristic;
	};
};
#include "GraphNode.h"