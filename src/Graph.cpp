#include "defines.hpp"
#include "Graph.hpp"
#include "random/Xoshiro256plus.h"

using namespace std;

// Constructor
Graph::Graph()
{
    this->order = this->edges_count = 0;
    this->first_node = this->last_node = nullptr;
    this->lightest_node_weight = 0.0;
}

// Destructor
Graph::~Graph()
{
    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {
        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{
    return this->order;
}

int Graph::getNumberEdges()
{
    return this->edges_count;
}

Node *Graph::getFirstNode()
{
    return this->first_node;
}

Node *Graph::getLastNode()
{
    return this->last_node;
}

Node *Graph::getNode(int id)
{
    Node *node = this->first_node;

    while (node != nullptr)
    {
        if (node->getId() == id)
            return node;
        node = node->getNextNode();
    }
    return nullptr;
}

Node *Graph::getNodePosition(int position)
{
    Node *node = this->first_node;

    while (node != nullptr)
    {
        if (node->getPosition() == position)
            return node;

        node = node->getNextNode();
    }
    return nullptr;
}

// Others methods
void Graph::insertNode(int id, float weight)
{
    // if node id already exists
    if (this->first_node != nullptr)
    {
        // create a new node and last = new node
        Node *new_node = new Node(id);
        new_node->setPosition(this->order);
        new_node->setWeight(weight);
        this->last_node->setNextNode(new_node);
        this->last_node = new_node;
        if (weight < this->lightest_node_weight)
            this->lightest_node_weight = weight;
    }
    else
    {
        // if node id doesnt exist, create new node and first = last = new node
        Node *new_node = new Node(id); 
        new_node->setPosition(this->order);
        new_node->setWeight(weight); 
        this->first_node = new_node;
        this->last_node = new_node;
        this->lightest_node_weight = weight; 
    }
    this->order = this->order + 1;
}

void Graph::insertEdge(int source_id, float source_weight, int target_id, float target_weight, float edge_weight)
{
    Node *node = getNode(source_id);
    Node *aux = getNode(target_id);

    // if node doesnt exist
    if (node == nullptr)
    {
        return;
    }

    // if aux doesnt exist
    if (aux == nullptr)
    {
        return;
    }

    // if both exist
    if (node != nullptr && aux != nullptr)
    {
        // if edge doesnt exist
        if (!node->searchEdge(target_id))
        {
            node->insertEdge(target_id, aux->getPosition(), edge_weight);
            this->edges_count++;

            // return edge
            if (!aux->searchEdge(source_id))
            {
                aux->insertEdge(source_id, node->getPosition(), edge_weight);
            }
        }
    }
}

void Graph::removeNode(int id)
{
    Node *node = getNode(id);

    if (node == nullptr)
        return;
    
    // if node is the first, next node will be the new first
    else if (node == this->first_node)
        this->first_node = node->getNextNode();

    else
    {
        Node *aux = this->first_node;

        while (aux->getNextNode() != node)
            aux = aux->getNextNode();

        if (node == this->last_node)
            this->last_node = aux;

        aux->setNextNode(node->getNextNode());
    }

    // delete node
    delete node;
    this->order--;
}

bool Graph::searchNode(int id)
{
    Node *node = getNode(id);

    if (node == nullptr)
        return false;
    else
        return true;
}

void Graph::setAllNonVisited()
{
    Node *node = this->first_node; 

    while (node != nullptr)
    {
        node->setVisited(false);   
        node = node->getNextNode(); 
    }
}

bool Graph::allNodesUsed()
{
    Node *node = this->first_node; 

    while (node != nullptr)
    {
        if (node->getOutDegree() == 0)
        {
            return false;
        }
        node = node->getNextNode();
    }
    return true;
}

vector<int> Graph::nonUsedNodes()
{
    vector<int> nonused;
    Node *node = this->first_node; 

    while (node != nullptr)
    {
        if (node->getOutDegree() == 0)
        {
            nonused.push_back(node->getId());
        }
        node = node->getNextNode();
    }
    return nonused;
}
