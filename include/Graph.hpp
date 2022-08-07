#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include "Node.hpp"
#include "defines.hpp"

using namespace std;

class Graph
{
private:
    int order;
    int edges_count;
    Node *first_node;
    Node *last_node;
    float lightest_node_weight;
    struct timeval begin, end;
    long timeLimit;

public:
    // Constructor and destructor
    Graph();
    ~Graph();

    // Getters
    int getOrder();
    int getNumberEdges();
    Node *getFirstNode();
    Node *getLastNode();
    Node *getNode(int id);
    Node *getNodePosition(int position);

    // Other methods
    void insertNode(int id, float weight);
    void insertEdge(int source_id, float source_weight, int target_id, float target_weight, float edge_weight);
    void removeNode(int id);
    bool searchNode(int id);
    void setAllNonVisited();
    bool allNodesUsed();
    vector<int> nonUsedNodes();

    
};

#endif // GRAPH_HPP_INCLUDED