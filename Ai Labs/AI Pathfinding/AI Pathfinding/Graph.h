#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <queue>
#include <vector>
#include <functional>

#include "nodeCostComparer.h"


template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;

// ---------------------------------------------------------------------
//  Name:           Graph
//  Description:    Manages the nodes and connections (arc) between them
// ---------------------------------------------------------------------
template<class NodeType, class ArcType>
class Graph 
{
public:        
	// typedef the classes to make our lives easier.
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

    // Constructor and destructor functions
    Graph( int size );
    ~Graph();

    // Accessors
    Node * nodeIndex(int index) const 
	{
		return m_nodes.at(index);
    }

    // Public member functions.
    bool addNode( NodeType data, int index );
    void removeNode( int index );
    bool addArc( int from, int to, ArcType weight );
    void removeArc( int from, int to );
    Arc* getArc( int from, int to );        
    void clearMarks();
    void depthFirst( Node* node, std::function<void(Node *)> f_visit);

	void ucs(Node* start, Node* dest, std::function<void(Node*)> f_visit, std::vector<Node*>& path);

	void aStar(Node* start, Node* dest, std::vector<Node>& path, std::function<void(Node*)> f_visit);
	
    void breadthFirst( Node* node, std::function<void(Node *)> f_visit);
	void adaptedBreadthFirst( Node* current, Node* goal );	

	void nodeCosts(Node* goal);

	void calHeuristic(Node* goal);

	void setTargetsNull();

private:
	// ----------------------------------------------------------------
	//  Description:    A container of all the nodes in the graph.
	// ----------------------------------------------------------------

	std::vector<Node*> m_nodes;

};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    Constructor, this constructs an empty graph
//  Arguments:      The maximum number of nodes.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::Graph( int maxNodes ) : m_nodes( maxNodes, nullptr) 
{  
}

// ----------------------------------------------------------------
//  Name:           ~Graph
//  Description:    destructor, This deletes every node
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::~Graph() {
   for( int index = 0; index < m_nodes.size(); index++ ) 
   {
        if( m_nodes[index] != nullptr ) 
		{
			delete m_nodes.at(index);
        }
   }
}

// ----------------------------------------------------------------
//  Name:           addNode
//  Description:    This adds a node at a given index in the graph.
//  Arguments:      The first parameter is the data to store in the node.
//                  The second parameter is the index to store the node.
//  Return Value:   true if successful
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode( NodeType data, int index ) 
{
   bool nodeNotPresent = false;
   // find out if a node does not exist at that index.
   if ( nullptr == m_nodes.at(index) ) 
   {
      nodeNotPresent = true;
      // create a new node, put the data in it, and unmark it.
	  m_nodes.at(index) = new Node;
	  m_nodes.at(index)->m_data = data;
	  m_nodes.at(index)->setMarked(false);
    }
        
    return nodeNotPresent;
}

// ----------------------------------------------------------------
//  Name:           removeNode
//  Description:    This removes a node from the graph
//  Arguments:      The index of the node to return.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeNode( int index ) 
{
     // Only proceed if node does exist.
     if( nullptr != m_nodes.at(index) ) 
	 {
         // now find every arc that points to the node that
         // is being removed and remove it.        
         Arc* arc;

         // loop through every node
         for( int node = 0; node < m_nodes.size(); node++ ) 
		 {
              // if the node is valid...
              if( nullptr != m_nodes.at(node) ) {
                  // see if the node has an arc pointing to the current node.
                  arc = m_nodes.at(node)->getArc(m_nodes.at(index) );
              }
              // if it has an arc pointing to the current node, then
              // remove the arc.
              if( arc != 0 ) {
                  removeArc( node, index );
              }
         }
        

        // now that every arc pointing to the current node has been removed,
        // the node can be deleted.
        delete m_nodes.at(index);
		m_nodes.at(index) = nullptr;       
    }
}

// ----------------------------------------------------------------
//  Name:           addArd
//  Description:    Adds an arc from the first index to the 
//                  second index with the specified weight.
//  Arguments:      The first argument is the originating node index
//                  The second argument is the ending node index
//                  The third argument is the weight of the arc
//  Return Value:   true on success.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addArc( int from, int to, ArcType weight ) {
     bool proceed = true; 
     // make sure both nodes exist.
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) 
	 {
         proceed = false;
     }
        
     // if an arc already exists we should not proceed
     if( m_nodes.at(from)->getArc( m_nodes.at(to) ) != nullptr ) 
	 {
         proceed = false;
     }

     if (proceed == true) 
	 {
        // add the arc to the "from" node.
		 m_nodes.at(from)->addArc(m_nodes.at(to), weight );
     }
        
     return proceed;
}


// ----------------------------------------------------------------
//  Name:           removeArc
//  Description:    This removes the arc from the first index to the second index
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeArc( int from, int to ) 
{
     // Make sure that the node exists before trying to remove
     // an arc from it.
     bool nodeExists = true;
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) 
	 {
         nodeExists = false;
     }

     if (nodeExists == true) 
	 {
        // remove the arc.
		 m_nodes.at(from)->removeArc(m_nodes.at(to) );
     }
}


// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    Gets a pointer to an arc from the first index
//                  to the second index.
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   pointer to the arc, or 0 if it doesn't exist.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc( int from, int to ) 
{
     Arc* arc = 0;
     // make sure the to and from nodes exist
     if( nullptr != m_nodes.at(from) && nullptr != m_nodes.at(to) ) 
	 {
         arc = m_nodes.at(from)->getArc(m_nodes.at(to) );
     }
                
     return arc;
}


// ----------------------------------------------------------------
//  Name:           clearMarks
//  Description:    This clears every mark on every node.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::clearMarks() 
{
     for( int index = 0; index < m_nodes.size(); index++ ) 
	 {
          if( nullptr != m_nodes.at(index) ) 
		  {
			  m_nodes.at(index)->setMarked(false);
          }
     }
}


// ----------------------------------------------------------------
//  Name:           depthFirst
//  Description:    Performs a depth-first traversal on the specified 
//                  node.
//  Arguments:      The first argument is the starting node
//                  The second argument is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::depthFirst( Node* node, std::function<void(Node *)> f_visit ) 
{
     if( nullptr != node ) {
           // process the current node and mark it
           f_visit( node );
           node->setMarked(true);

           // go through each connecting node
           auto iter = node->arcList().begin();
           auto endIter = node->arcList().end();
        
		   for( ; iter != endIter; ++iter) 
		   {
			    // process the linked node if it isn't already marked.
                if ( (*iter).node()->marked() == false ) 
				{
                   depthFirst( (*iter).node(), f_visit);
                }            
           }
     }
}

template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::ucs(Node* start, Node* dest, std::function<void(Node*)> f_visit, std::vector<Node*>& path)
{
	std::priority_queue<Node*, std::vector<Node*>, NodeSearchCostComparer<NodeType,ArcType>> pq;

	for (auto nodes : m_nodes)
	{
		nodes->m_data.m_pathCost = INT_MAX;
	}

	start->m_data.m_pathCost = 0;

	pq.push(start);

	start->setMarked(true);

	while (pq.empty() == false && pq.top() != dest)
	{
		auto iter = pq.top()->arcList().begin();
		auto endIter = pq.top()->arcList().end();

		for (; iter != endIter; iter++)
		{
			Arc arc = (*iter);
			if ((*iter).node() != pq.top()->previous())
			{
				ArcType distC = arc.weight() + pq.top()->m_data.m_pathCost;
				if (distC < arc.node()->m_data.m_pathCost)
				{
					arc.node()->m_data.m_pathCost = distC;
					(*iter).node()->setPrevious(pq.top());
				}

				if ((*iter).node()->marked() == false)
				{
					pq.push((*iter).node());

					(*iter).node()->setMarked(true);
				}
			}

		}
		pq.pop();
	}	

	auto pathnode = dest;

	while (pathnode != NULL)
	{
		path.push_back(pathnode);

		pathnode = pathnode->previous();
	}

	std::cout << "end" << std::endl;
}

template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::aStar(Node* start, Node* dest, std::vector<Node>& path, std::function<void(Node*)> f_visit)
{
	std::priority_queue<Node*, std::vector<Node*>, NodeSearchCostComparer<NodeType, ArcType>> pq;
	path.clear();


	calHeuristic(dest);

	for (auto & nodes : m_nodes)
	{
		//nodes->m_data.m_pathCost = INT_MAX;
		nodes->setPrevious(nullptr);
		nodes->setMarked(false);
	}

	//start->m_data.m_pathCost = 0;

	pq.push(start);

	start->setMarked(true);

	while (pq.empty() == false && pq.top() != dest)
	{
		auto iter = pq.top()->arcList().begin();
		auto endIter = pq.top()->arcList().end();

		for (; iter != endIter; iter++)
		{
			Arc arc = (*iter);
			if ((*iter).node() != pq.top()->previous() && pq.top()->m_data.passable == true)
			{
				ArcType distC = (*iter).weight() + pq.top()->m_data.m_pathCost;

				if (distC < arc.node()->m_data.m_pathCost)
				{
					arc.node()->m_data.m_pathCost = distC;
					(*iter).node()->setPrevious(pq.top());
				}

				if ((*iter).node()->marked() == false)
				{
					pq.push((*iter).node());

					(*iter).node()->setMarked(true);
				}
			}

		}
		pq.pop();
	}

	auto pathnode = dest;

	while (pathnode != NULL)
	{
		path.push_back(*pathnode);

		pathnode = pathnode->previous();
	}
}


// ----------------------------------------------------------------
//  Name:           breadthFirst
//  Description:    Performs a depth-first traversal the starting node
//                  specified as an input parameter.
//  Arguments:      The first parameter is the starting node
//                  The second parameter is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::breadthFirst( Node* node, std::function<void(Node *)> f_visit) 
{
   if( nullptr != node ) 
   {
	  std::queue<Node*> nodeQueue;        
	  // place the first node on the queue, and mark it.
      nodeQueue.push( node );
      node->setMarked(true);

      // loop through the queue while there are nodes in it.
      while( nodeQueue.size() != 0 ) 
	  {
         // process the node at the front of the queue.
		 f_visit( nodeQueue.front() );

         // add all of the child nodes that have not been 
         // marked into the queue
         auto iter = nodeQueue.front()->arcList().begin();
         auto endIter = nodeQueue.front()->arcList().end();
         
		 for( ; iter != endIter; iter++ ) 
		 {
              if ( (*iter).node()->marked() == false) 
			  {
				 // mark the node and add it to the queue.
                 (*iter).node()->setMarked(true);
                 nodeQueue.push( (*iter).node() );
              }
         }

         // dequeue the current node.
         nodeQueue.pop();
      }
   }  
}


// ----------------------------------------------------------------
//  Name:           adaptedBreadthFirst
//  Description:    Performs a breadth-first traversal the starting node
//                  specified as an input parameter, terminating at the goal.
//  Arguments:      The first parameter is the starting node.
//                  The second parameter is the goal node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::adaptedBreadthFirst( Node* current, Node *goal ) 
{
	if (nullptr != current)
	{
		std::queue<Node*> nodeQueue;

		nodeQueue.push(current);

		current->setMarked(true);

		bool found = false;

		while (nodeQueue.size() != 0 && found == false)
		{
			Node* temp = nodeQueue.front();

			// add all of the child nodes that have not been 
			// marked into the queue
			auto iter = nodeQueue.front()->arcList().begin();
			auto endIter = nodeQueue.front()->arcList().end();

			for (; iter != endIter && found == false; iter++)
			{
				if ((*iter).node() == goal)
				{
					found = true; // found the goal node
				}

				if ((*iter).node()->marked() == false)
				{
					// mark the node and add it to the queue.
					(*iter).node()->setMarked(true);
					(*iter).node()->setPrevious(temp); // set the previous node
					nodeQueue.push((*iter).node());
				}
			}

			// dequeue the current node.
			nodeQueue.pop();
		}
	}

}

//set all nodes pathcost 
//skips any wall nodes
template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::nodeCosts(Node* goal)
{
	for (int index = 0; index < m_nodes.size(); index++)
	{
		if (m_nodes.at(index)->m_data.passable == true)
		{
			m_nodes.at(index)->setMarked(false);
			m_nodes.at(index)->m_data.m_pathCost = -1;
		}
		else
		{
			m_nodes.at(index)->setMarked(true);
			m_nodes.at(index)->m_data.m_pathCost = 999;
		}
		
	}

	std::queue<Node*> nodeQueue;

	goal->setMarked(true);
	goal->m_data.m_pathCost = 0;

	nodeQueue.push(goal);


	while (nodeQueue.size() != 0)
	{
		Node* temp = nodeQueue.front();

		auto iter = nodeQueue.front()->arcList().begin();
		auto endIter = nodeQueue.front()->arcList().end();

		for (; iter != endIter; iter++)
		{
			if ((*iter).node()->marked() == false)
			{
				(*iter).node()->m_data.m_pathCost = nodeQueue.front()->m_data.m_pathCost + 1;
				(*iter).node()->m_data.m_costText.setString(std::to_string((*iter).node()->m_data.m_pathCost));
				(*iter).node()->setMarked(true);
				nodeQueue.push((*iter).node());
			}
		}

		// dequeue the current node.
		nodeQueue.pop();
	}
}

//calculates the heuristic of each node
template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::calHeuristic(Node* goal)
{
	for (auto& nodes : m_nodes)
	{
		if (nodes != goal)
		{
			nodes->m_data.m_hueristic = sqrt(
				(pow((nodes->m_data.m_positionX - goal->m_data.m_positionX), 2.0f) +
					(pow((nodes->m_data.m_positionY - goal->m_data.m_positionY), 2.0f))));
		}
		else
		{
			nodes->m_data.m_hueristic = 0;
		}
	}
}

//sets the targets of each node to null
template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::setTargetsNull()
{
	for (auto& nodes : m_nodes)
	{
		nodes->setTarget(nullptr);
	}
}


#include "GraphNode.h"
#include "GraphArc.h"

#endif
