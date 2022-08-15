#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include "Node.hpp"
#include "Edge.hpp"
#include "Structures.hpp"
#include "defines.hpp"

using namespace std;

class Graph
{
private:
    int order;
    int edges_count;
    Node *first_node;
    Node *last_node;
    int n; // matrix representation order
    vector<SolutionEdge> solution;
    vector<bool> in_solution;
    vector<bool> foi_aberto;
    vector<bool> foi_fechado;
    vector<SolutionEdge> arestas_abertas;
    vector<int> nos_abertos;
    vector<int> nos_fechados;
    vector<StateInfos> aux_nos_abertos;
    vector<vector<int>> graph_matrix;
    vector<int> heuristics;
    vector<StateInfos> descartados;

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
    vector<vector<int>> get_graph_matrix();

    // Searches
    void backtracking();
    bool backtrackingAux(int s, int goal);
    void breadthFirstSearch();
    void deepSearch();
    void buscaOrdenada();
    void greedy();
    void Astar();
    void IDAstar();
    bool IDAstarAux(StateInfos s, int goal, int l, int r, int t, int b, int patamar);


    void addInSolution(int state);

    // Other methods
    void insertNode(int id, float weight);
    void insertEdge(int source_id, float source_weight, int target_id, float target_weight, float edge_weight);
    void removeNode(int id);
    bool searchNode(int id);
    void setAllNonVisited();
    bool allNodesUsed();
    vector<int> nonUsedNodes();
    vector<int> possibleMvmts(int state);
    void reset();
    bool isEdgeInSolution(int source_id, int target_id);
    void printEstatisticas();
    void printSolution();
    vector<int> nodesToUse();
    bool isEdgeInMaze(int source_id, int target_id);
    bool isNode2Expand();
    void create_matrix();
    void dijsktra(int goal);
};

#endif // GRAPH_HPP_INCLUDED