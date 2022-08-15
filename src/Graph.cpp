#include "defines.hpp"
#include "Graph.hpp"
#include "random/Xoshiro256plus.h"

using namespace std;

// Constructor
Graph::Graph()
{
    this->order = this->edges_count = 0;
    this->first_node = this->last_node = nullptr;
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

// Searches

void Graph::backtracking()
{
    int s0 = 0;
    int s = s0;
    int goal = this->order - 1; // last node

    this->reset();

    if (this->backtrackingAux(0, goal) == false)
    {
        cout << "No solution" << endl;
        return;
    }
    cout << "\nPrint Backtracking Solution? (y/n) ";
    string o;
    cin >> o;
    if (o == "y" || o == "Y")
        this->printSolution();
    cout << "\nBacktracking Infos ---------------------" << endl;
    this->printEstatisticas();
}

bool Graph::backtrackingAux(int s, int goal)
{
    if (s == goal)
    {
        this->in_solution.at(s) = true;
        return true;
    }
    // cout << "s = " << s << "   goal = " << goal << endl;
    if (s >= 0 && s < this->order)
    {
        if (this->in_solution[s] == true)
        {
            return false;
        }

        this->in_solution.at(s) = true;
        this->nos_abertos.push_back(s);
        this->foi_aberto.at(s) = true;

        // left
        Edge *e = this->getNode(s)->getEdge(s - 1);
        if (e != nullptr && this->backtrackingAux(s - 1, goal))
        {
            SolutionEdge edge;
            edge.id_source = s;
            edge.id_target = s - 1;
            edge.weight = e->getWeight();
            this->solution.push_back(edge);
            return true;
        }

        // right
        e = this->getNode(s)->getEdge(s + 1);
        if (e != nullptr && this->backtrackingAux(s + 1, goal))
        {
            SolutionEdge edge;
            edge.id_source = s;
            edge.id_target = s + 1;
            edge.weight = e->getWeight();
            this->solution.push_back(edge);
            return true;
        }

        // top
        e = this->getNode(s)->getEdge(s - this->n);
        if (e != nullptr && this->backtrackingAux(s - this->n, goal))
        {
            SolutionEdge edge;
            edge.id_source = s;
            edge.id_target = s - this->n;
            edge.weight = e->getWeight();
            this->solution.push_back(edge);
            return true;
        }

        // bottom
        e = this->getNode(s)->getEdge(s + this->n);
        if (e != nullptr && this->backtrackingAux(s + this->n, goal))
        {
            SolutionEdge edge;
            edge.id_source = s;
            edge.id_target = s + this->n;
            edge.weight = e->getWeight();
            this->solution.push_back(edge);
            this->foi_fechado.at(s) = true;
            this->nos_fechados.push_back(s);
            return true;
        }
        // cout << "164" << endl;
        this->in_solution.at(s) = false;
    }
    return false;
}

void Graph::breadthFirstSearch()
{
    int s0 = 0;
    int s = s0;
    int goal = this->order - 1; // last node
    bool success = false;

    this->reset();

    this->nos_abertos.push_back(s);
    this->foi_aberto.at(s) = true;

    int index = 0;

    while (success == false && this->isNode2Expand())
    {
        if (s == goal)
        {
            success = true;
            break;
        }

        Edge *e;
        // left
        if (s - 1 >= 0)
        {
            e = this->getNode(s)->getEdge(s - 1);
            if (e != nullptr && this->foi_aberto.at(s - 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s;
                edge.id_target = s - 1;
                edge.weight = e->getWeight();
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s - 1);
                this->foi_aberto.at(s - 1) = true;
            }
        }

        // right
        if (s + 1 < this->order)
        {
            e = this->getNode(s)->getEdge(s + 1);
            if (e != nullptr && this->foi_aberto.at(s + 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s;
                edge.id_target = s + 1;
                edge.weight = e->getWeight();
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s + 1);
                this->foi_aberto.at(s + 1) = true;
            }
        }

        // top
        if (s - this->n >= 0)
        {
            e = this->getNode(s)->getEdge(s - this->n);
            if (e != nullptr && this->foi_aberto.at(s - this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s;
                edge.id_target = s - this->n;
                edge.weight = e->getWeight();
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s - this->n);
                this->foi_aberto.at(s - this->n) = true;
            }
        }

        // bottom
        if (s + this->n < this->order)
        {
            e = this->getNode(s)->getEdge(s + this->n);
            if (e != nullptr && this->foi_aberto.at(s + this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s;
                edge.id_target = s + this->n;
                edge.weight = e->getWeight();
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s + this->n);
                this->foi_aberto.at(s + this->n) = true;
            }
        }

        this->nos_fechados.push_back(s);
        this->foi_fechado.at(s) = true;
        index++; // next in queue
        s = this->nos_abertos.at(index);
        // cout << "s: " << s << endl;
    }
    vector<SolutionEdge> aux;
    for (int i = this->solution.size() - 1; i >= 0; i--)
    {
        if (this->solution[i].id_target == goal)
        {
            aux.push_back(this->solution[i]);
            int id_s = this->solution[i].id_source;

            for (int j = i - 1; j >= 0; j--)
            {
                if (this->solution[j].id_target == id_s)
                {
                    id_s = this->solution[j].id_source;
                    aux.push_back(this->solution[j]);
                }
            }
            break;
        }
    }
    this->solution = aux;
    cout << "\nPrint Breadth First Solution? (y/n) ";
    string o;
    cin >> o;
    if (o == "y" || o == "Y")
        this->printSolution();
    cout << "\nBreadth First Infos ---------------------" << endl;
    this->printEstatisticas();
}

void Graph::deepSearch()
{
    int s0 = 0;
    int s = s0;
    int goal = this->order - 1; // last node
    bool success = false;

    this->reset();

    this->nos_abertos.push_back(s);
    this->foi_aberto.at(s) = true;

    while (success == false && this->isNode2Expand())
    {
        if (s == goal)
        {
            success = true;
            break;
        }

        Edge *e;
        // left
        if (s - 1 >= 0)
        {
            e = this->getNode(s)->getEdge(s - 1);
            if (e != nullptr && this->foi_aberto.at(s - 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s;
                edge.id_target = s - 1;
                edge.weight = e->getWeight();
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s - 1);
                this->foi_aberto.at(s - 1) = true;
            }
        }

        // right
        if (s + 1 < this->order)
        {
            e = this->getNode(s)->getEdge(s + 1);
            if (e != nullptr && this->foi_aberto.at(s + 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s;
                edge.id_target = s + 1;
                edge.weight = e->getWeight();
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s + 1);
                this->foi_aberto.at(s + 1) = true;
            }
        }

        // top
        if (s - this->n >= 0)
        {
            e = this->getNode(s)->getEdge(s - this->n);
            if (e != nullptr && this->foi_aberto.at(s - this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s;
                edge.id_target = s - this->n;
                edge.weight = e->getWeight();
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s - this->n);
                this->foi_aberto.at(s - this->n) = true;
            }
        }

        // bottom
        if (s + this->n < this->order)
        {
            e = this->getNode(s)->getEdge(s + this->n);
            if (e != nullptr && this->foi_aberto.at(s + this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s;
                edge.id_target = s + this->n;
                edge.weight = e->getWeight();
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s + this->n);
                this->foi_aberto.at(s + this->n) = true;
            }
        }

        this->nos_fechados.push_back(s);
        this->foi_fechado.at(s) = true;

        for (int i = this->nos_abertos.size() - 1; i >= 0; i--)
        {
            if (this->foi_fechado[this->nos_abertos[i]] == false)
            {
                s = this->nos_abertos[i];
                break;
            }
        }
        // cout << "s: " << s << endl;
    }
    vector<SolutionEdge> aux;
    for (int i = this->solution.size() - 1; i >= 0; i--)
    {
        if (this->solution[i].id_target == goal)
        {
            aux.push_back(this->solution[i]);
            int id_s = this->solution[i].id_source;

            for (int j = i - 1; j >= 0; j--)
            {
                if (this->solution[j].id_target == id_s)
                {
                    id_s = this->solution[j].id_source;
                    aux.push_back(this->solution[j]);
                }
            }
            break;
        }
    }
    this->solution = aux;
    cout << "\nPrint Deep Search Solution? (y/n) ";
    string o;
    cin >> o;
    if (o == "y" || o == "Y")
        this->printSolution();
    cout << "\nDeep Search Infos ---------------------" << endl;
    this->printEstatisticas();
}

void Graph::buscaOrdenada()
{
    int s0 = 0;
    // int s = s0;
    int goal = this->order - 1; // last node
    bool success = false;
    int l, r, t, b;
    l = r = t = b = 0;

    this->reset();

    StateInfos s;
    s.id = s0;
    s.cost = 0;

    this->nos_abertos.push_back(s.id);
    this->foi_aberto.at(s.id) = true;
    this->aux_nos_abertos.push_back(s);

    while (success == false && this->aux_nos_abertos.size() > 0)
    {
        if (s.id == goal)
        {
            success = true;
            break;
        }

        // left
        if (s.id - 1 >= 0)
        {
            if (this->graph_matrix[s.id][s.id - 1] != 0 && this->foi_fechado.at(s.id - 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id - 1;
                edge.weight = this->graph_matrix[s.id][s.id - 1];
                l += edge.weight;
                edge.cost = l;
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id - 1);
                this->foi_aberto.at(s.id - 1) = true;

                StateInfos si;
                si.id = s.id - 1;
                si.cost = l;
                this->aux_nos_abertos.push_back(si);
            }
        }

        // right
        if (s.id + 1 < this->order)
        {
            if (this->graph_matrix[s.id][s.id + 1] != 0 && this->foi_fechado.at(s.id + 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id + 1;
                edge.weight = this->graph_matrix[s.id][s.id + 1];
                r += edge.weight;
                edge.cost = r;
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id + 1);
                this->foi_aberto.at(s.id + 1) = true;

                StateInfos si;
                si.id = s.id + 1;
                si.cost = r;
                this->aux_nos_abertos.push_back(si);
            }
        }

        // top
        if (s.id - this->n >= 0)
        {
            if (this->graph_matrix[s.id][s.id - this->n] != 0 && this->foi_fechado.at(s.id - this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id - this->n;
                edge.weight = this->graph_matrix[s.id][s.id - this->n];
                t += edge.weight;
                edge.cost = t;
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id - this->n);
                this->foi_aberto.at(s.id - this->n) = true;

                StateInfos si;
                si.id = s.id - this->n;
                si.cost = t;
                this->aux_nos_abertos.push_back(si);
            }
        }

        // bottom
        if (s.id + this->n < this->order)
        {
            if (this->graph_matrix[s.id][s.id + this->n] != 0 && this->foi_fechado.at(s.id + this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id + this->n;
                edge.weight = this->graph_matrix[s.id][s.id + this->n];
                b += edge.weight;
                edge.cost = b;
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id + this->n);
                this->foi_aberto.at(s.id + this->n) = true;

                StateInfos si;
                si.id = s.id + this->n;
                si.cost = b;
                this->aux_nos_abertos.push_back(si);
            }
        }

        this->nos_fechados.push_back(s.id);
        this->foi_fechado.at(s.id) = true;

        for (size_t i = 0; i < this->aux_nos_abertos.size(); i++)
        {
            if (this->aux_nos_abertos.at(i).id == s.id)
            {
                this->aux_nos_abertos.erase(this->aux_nos_abertos.begin() + i);
                break;
            }
        }

        int min = 99999;
        int min_index = -1;
        for (size_t i = 0; i < this->aux_nos_abertos.size(); i++)
        {
            if (this->aux_nos_abertos.at(i).cost < min)
            {
                min = this->aux_nos_abertos.at(i).cost;
                min_index = i;
            }
        }
        s = this->aux_nos_abertos.at(min_index);

        // cout << "s: " << s << endl;
    }
    vector<SolutionEdge> aux;
    vector<int> erase_index;
    for (size_t i = 0; i < this->solution.size(); i++)
    {
        for (size_t j = i + 1; j < this->solution.size(); j++)
        {
            if (this->solution[j].id_target == this->solution[i].id_target)
            {
                if (this->solution[j].cost >= this->solution[i].cost)
                {
                    erase_index.push_back(j);
                }
                else
                {
                    erase_index.push_back(i);
                }
            }
        }
    }

    for (int i = this->solution.size() - 1; i >= 0; i--)
    {
        if (find(erase_index.begin(), erase_index.end(), i) == erase_index.end())
        {
            if (this->solution[i].id_target == goal)
            {
                aux.push_back(this->solution[i]);
                int id_s = this->solution[i].id_source;

                for (int j = i - 1; j >= 0; j--)
                {
                    if (find(erase_index.begin(), erase_index.end(), j) == erase_index.end())
                    {
                        if (this->solution[j].id_target == id_s)
                        {
                            id_s = this->solution[j].id_source;
                            aux.push_back(this->solution[j]);
                        }
                    }
                }
                break;
            }
        }
    }
    this->solution = aux;
    cout << "\nPrint Busca Ordenada Solution? (y/n) ";
    string o;
    cin >> o;
    if (o == "y" || o == "Y")
        this->printSolution();
    cout << "\nBusca Ordenada Infos ---------------------" << endl;
    this->printEstatisticas();
}

void Graph::greedy()
{
    int s0 = 0;
    // int s = s0;
    int goal = this->order - 1; // last node
    bool success = false;
    int l, r, t, b;
    l = r = t = b = 0;

    this->reset();

    StateInfos s;
    s.id = s0;
    s.heuristic = this->heuristics[s.id];

    this->nos_abertos.push_back(s.id);
    this->foi_aberto.at(s.id) = true;
    this->aux_nos_abertos.push_back(s);

    while (success == false && this->aux_nos_abertos.size() > 0)
    {
        if (s.id == goal)
        {
            success = true;
            break;
        }

        // left
        if (s.id - 1 >= 0)
        {
            if (this->graph_matrix[s.id][s.id - 1] != 0 && this->foi_fechado.at(s.id - 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id - 1;
                edge.weight = this->graph_matrix[s.id][s.id - 1];
                edge.heuristic = this->heuristics[edge.id_target];
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id - 1);
                this->foi_aberto.at(s.id - 1) = true;

                StateInfos si;
                si.id = s.id - 1;
                si.heuristic = this->heuristics[si.id];
                this->aux_nos_abertos.push_back(si);
            }
        }

        // right
        if (s.id + 1 < this->order)
        {
            if (this->graph_matrix[s.id][s.id + 1] != 0 && this->foi_fechado.at(s.id + 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id + 1;
                edge.weight = this->graph_matrix[s.id][s.id + 1];
                r += edge.weight;
                edge.cost = r;
                edge.heuristic = this->heuristics[edge.id_target];
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id + 1);
                this->foi_aberto.at(s.id + 1) = true;

                StateInfos si;
                si.id = s.id + 1;
                si.heuristic = this->heuristics[si.id];
                this->aux_nos_abertos.push_back(si);
            }
        }

        // top
        if (s.id - this->n >= 0)
        {
            if (this->graph_matrix[s.id][s.id - this->n] != 0 && this->foi_fechado.at(s.id - this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id - this->n;
                edge.weight = this->graph_matrix[s.id][s.id - this->n];
                edge.heuristic = this->heuristics[edge.id_target];
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id - this->n);
                this->foi_aberto.at(s.id - this->n) = true;

                StateInfos si;
                si.id = s.id - this->n;
                si.heuristic = this->heuristics[si.id];
                this->aux_nos_abertos.push_back(si);
            }
        }

        // bottom
        if (s.id + this->n < this->order)
        {
            if (this->graph_matrix[s.id][s.id + this->n] != 0 && this->foi_fechado.at(s.id + this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id + this->n;
                edge.weight = this->graph_matrix[s.id][s.id + this->n];
                edge.heuristic = this->heuristics[edge.id_target];
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id + this->n);
                this->foi_aberto.at(s.id + this->n) = true;

                StateInfos si;
                si.id = s.id + this->n;
                si.heuristic = this->heuristics[si.id];
                this->aux_nos_abertos.push_back(si);
            }
        }

        this->nos_fechados.push_back(s.id);
        this->foi_fechado.at(s.id) = true;

        for (size_t i = 0; i < this->aux_nos_abertos.size(); i++)
        {
            if (this->aux_nos_abertos.at(i).id == s.id)
            {
                this->aux_nos_abertos.erase(this->aux_nos_abertos.begin() + i);
                break;
            }
        }

        int min = 99999;
        int min_index = -1;
        for (size_t i = 0; i < this->aux_nos_abertos.size(); i++)
        {
            if (this->aux_nos_abertos.at(i).heuristic < min)
            {
                min = this->aux_nos_abertos.at(i).heuristic;
                min_index = i;
            }
        }
        s = this->aux_nos_abertos.at(min_index);

        // cout << "s: " << s << endl;
    }
    vector<SolutionEdge> aux;
    vector<int> erase_index;
    for (size_t i = 0; i < this->solution.size(); i++)
    {
        for (size_t j = i + 1; j < this->solution.size(); j++)
        {
            if (this->solution[j].id_target == this->solution[i].id_target)
            {
                if (this->solution[j].heuristic >= this->solution[i].heuristic)
                {
                    erase_index.push_back(j);
                }
                else
                {
                    erase_index.push_back(i);
                }
            }
        }
    }

    for (int i = this->solution.size() - 1; i >= 0; i--)
    {
        if (find(erase_index.begin(), erase_index.end(), i) == erase_index.end())
        {
            if (this->solution[i].id_target == goal)
            {
                aux.push_back(this->solution[i]);
                int id_s = this->solution[i].id_source;

                for (int j = i - 1; j >= 0; j--)
                {
                    if (find(erase_index.begin(), erase_index.end(), j) == erase_index.end())
                    {
                        if (this->solution[j].id_target == id_s)
                        {
                            id_s = this->solution[j].id_source;
                            aux.push_back(this->solution[j]);
                        }
                    }
                }
                break;
            }
        }
    }
    this->solution = aux;
    cout << "\nPrint Greedy Solution? (y/n) ";
    string o;
    cin >> o;
    if (o == "y" || o == "Y")
        this->printSolution();
    cout << "\nGreedy Infos ---------------------" << endl;
    this->printEstatisticas();
}

void Graph::Astar()
{
    int s0 = 0;
    int goal = this->order - 1; // last node
    bool success = false;
    int l, r, t, b;
    l = r = t = b = 0;

    this->reset();

    StateInfos s;
    s.id = s0;
    s.cost = 0;
    s.heuristic = this->heuristics[s.id];

    this->nos_abertos.push_back(s.id);
    this->foi_aberto.at(s.id) = true;
    this->aux_nos_abertos.push_back(s);

    while (success == false && this->aux_nos_abertos.size() > 0)
    {
        if (s.id == goal)
        {
            success = true;
            break;
        }

        // left
        if (s.id - 1 >= 0)
        {
            if (this->graph_matrix[s.id][s.id - 1] != 0 && this->foi_fechado.at(s.id - 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id - 1;
                edge.weight = this->graph_matrix[s.id][s.id - 1];
                l += edge.weight;
                edge.cost = l;
                edge.heuristic = this->heuristics[edge.id_target];
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id - 1);
                this->foi_aberto.at(s.id - 1) = true;

                StateInfos si;
                si.id = s.id - 1;
                si.cost = l;
                si.heuristic = this->heuristics[si.id];
                this->aux_nos_abertos.push_back(si);
            }
        }

        // right
        if (s.id + 1 < this->order)
        {
            if (this->graph_matrix[s.id][s.id + 1] != 0 && this->foi_fechado.at(s.id + 1) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id + 1;
                edge.weight = this->graph_matrix[s.id][s.id + 1];
                r += edge.weight;
                edge.cost = r;
                edge.heuristic = this->heuristics[edge.id_target];
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id + 1);
                this->foi_aberto.at(s.id + 1) = true;

                StateInfos si;
                si.id = s.id + 1;
                si.cost = r;
                si.heuristic = this->heuristics[si.id];
                this->aux_nos_abertos.push_back(si);
            }
        }

        // top
        if (s.id - this->n >= 0)
        {
            if (this->graph_matrix[s.id][s.id - this->n] != 0 && this->foi_fechado.at(s.id - this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id - this->n;
                edge.weight = this->graph_matrix[s.id][s.id - this->n];
                t += edge.weight;
                edge.cost = t;
                edge.heuristic = this->heuristics[edge.id_target];
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id - this->n);
                this->foi_aberto.at(s.id - this->n) = true;

                StateInfos si;
                si.id = s.id - this->n;
                si.cost = t;
                si.heuristic = this->heuristics[si.id];
                this->aux_nos_abertos.push_back(si);
            }
        }

        // bottom
        if (s.id + this->n < this->order)
        {
            if (this->graph_matrix[s.id][s.id + this->n] != 0 && this->foi_fechado.at(s.id + this->n) == false)
            {
                SolutionEdge edge;
                edge.id_source = s.id;
                edge.id_target = s.id + this->n;
                edge.weight = this->graph_matrix[s.id][s.id + this->n];
                b += edge.weight;
                edge.cost = b;
                edge.heuristic = this->heuristics[edge.id_target];
                this->solution.push_back(edge);
                this->nos_abertos.push_back(s.id + this->n);
                this->foi_aberto.at(s.id + this->n) = true;

                StateInfos si;
                si.id = s.id + this->n;
                si.cost = b;
                si.heuristic = this->heuristics[si.id];
                this->aux_nos_abertos.push_back(si);
            }
        }

        this->nos_fechados.push_back(s.id);
        this->foi_fechado.at(s.id) = true;

        for (size_t i = 0; i < this->aux_nos_abertos.size(); i++)
        {
            if (this->aux_nos_abertos.at(i).id == s.id)
            {
                this->aux_nos_abertos.erase(this->aux_nos_abertos.begin() + i);
                break;
            }
        }

        int min = 99999;
        int min_index = -1;
        for (size_t i = 0; i < this->aux_nos_abertos.size(); i++)
        {
            if (this->aux_nos_abertos.at(i).cost + this->aux_nos_abertos.at(i).heuristic < min)
            {
                min = this->aux_nos_abertos.at(i).cost + this->aux_nos_abertos.at(i).heuristic;
                min_index = i;
            }
        }
        s = this->aux_nos_abertos.at(min_index);

        // cout << "s: " << s << endl;
    }
    vector<SolutionEdge> aux;
    vector<int> erase_index;
    for (size_t i = 0; i < this->solution.size(); i++)
    {
        for (size_t j = i + 1; j < this->solution.size(); j++)
        {
            if (this->solution[j].id_target == this->solution[i].id_target)
            {
                if (this->solution[j].cost + this->solution[j].heuristic >= this->solution[i].cost + this->solution[i].heuristic)
                {
                    erase_index.push_back(j);
                }
                else
                {
                    erase_index.push_back(i);
                }
            }
        }
    }

    for (int i = this->solution.size() - 1; i >= 0; i--)
    {
        if (find(erase_index.begin(), erase_index.end(), i) == erase_index.end())
        {
            if (this->solution[i].id_target == goal)
            {
                aux.push_back(this->solution[i]);
                int id_s = this->solution[i].id_source;

                for (int j = i - 1; j >= 0; j--)
                {
                    if (find(erase_index.begin(), erase_index.end(), j) == erase_index.end())
                    {
                        if (this->solution[j].id_target == id_s)
                        {
                            id_s = this->solution[j].id_source;
                            aux.push_back(this->solution[j]);
                        }
                    }
                }
                break;
            }
        }
    }
    this->solution = aux;
    cout << "\nPrint A* Solution? (y/n) ";
    string o;
    cin >> o;
    if (o == "y" || o == "Y")
        this->printSolution();
    cout << "\nA* Infos ---------------------" << endl;
    this->printEstatisticas();
}

void Graph::IDAstar()
{
    int s0 = 0;
    int goal = this->order - 1; // last node
    bool success = false;
    int l, r, t, b;
    l = r = t = b = 0;
    int patamar, patamar_old;
    int mvmt = 1;

    this->reset();

    StateInfos s;
    s.parent = -1;
    s.id = s0;
    s.cost = 0;
    s.heuristic = this->heuristics[s.id];
    patamar = s.cost + s.heuristic;
    patamar_old = -1;

    this->nos_abertos.push_back(s.id);
    this->foi_aberto.at(s.id) = true;
    this->aux_nos_abertos.push_back(s);

    while (true)
    {
        l = r = t = b = 0;
        this->reset();
        this->nos_abertos.push_back(s.id);
        this->foi_aberto.at(s.id) = true;
        this->aux_nos_abertos.push_back(s);

        if (this->IDAstarAux(s, goal, l, r, t, b, patamar))
        {
            break;
        }
        if (patamar == 99999)
        {
            cout << "No solution found" << endl;
            break;
        }
    }

    cout << "\nPrint IDA* Solution? (y/n) ";
    string o;
    cin >> o;
    if (o == "y" || o == "Y")
        this->printSolution();
    cout << "\nIDA Infos ---------------------" << endl;

    this->printEstatisticas();
}

bool Graph::IDAstarAux(StateInfos s, int goal, int l, int r, int t, int b, int patamar)
{

    if (s.cost + s.heuristic > patamar)
    {
        patamar = s.cost + s.heuristic;
        this->nos_fechados.push_back(s.id);
        this->foi_fechado.at(s.id) = true;
        return false;
    }
    if (s.id == goal)
    {
        return true;
    }

    int min = 99999;

    // left
    if (s.id - 1 >= 0)
    {
        if (this->graph_matrix[s.id][s.id - 1] != 0 && this->foi_fechado.at(s.id - 1) == false)
        {
            SolutionEdge edge;
            edge.id_source = s.id;
            edge.id_target = s.id - 1;
            edge.weight = this->graph_matrix[s.id][s.id - 1];
            l += edge.weight;
            edge.cost = l;
            edge.heuristic = this->heuristics[edge.id_target];

            StateInfos si;
            si.id = s.id - 1;
            si.cost = l;
            si.heuristic = this->heuristics[si.id];

            this->nos_abertos.push_back(s.id - 1);
            this->foi_aberto.at(s.id - 1) = true;
            this->aux_nos_abertos.push_back(si);

            if (this->IDAstarAux(si, goal, l, r, t, b, patamar))
            {
                this->solution.push_back(edge);
                return true;
            }
            else
            {
                if (patamar < min)
                {
                    min = patamar;
                }
            }
        }
    }

    // right
    if (s.id + 1 < this->order)
    {
        if (this->graph_matrix[s.id][s.id + 1] != 0 && this->foi_fechado.at(s.id + 1) == false)
        {
            SolutionEdge edge;
            edge.id_source = s.id;
            edge.id_target = s.id + 1;
            edge.weight = this->graph_matrix[s.id][s.id + 1];
            r += edge.weight;
            edge.cost = r;
            edge.heuristic = this->heuristics[edge.id_target];

            this->nos_abertos.push_back(s.id + 1);
            this->foi_aberto.at(s.id + 1) = true;

            StateInfos si;
            si.id = s.id + 1;
            si.cost = r;
            si.heuristic = this->heuristics[si.id];
            this->aux_nos_abertos.push_back(si);

            if (this->IDAstarAux(si, goal, l, r, t, b, patamar))
            {
                this->solution.push_back(edge);
                return true;
            }
            else
            {
                if (patamar < min)
                {
                    min = patamar;
                }
            }
        }
    }

    // top
    if (s.id - this->n >= 0)
    {
        if (this->graph_matrix[s.id][s.id - this->n] != 0 && this->foi_fechado.at(s.id - this->n) == false)
        {
            SolutionEdge edge;
            edge.id_source = s.id;
            edge.id_target = s.id - this->n;
            edge.weight = this->graph_matrix[s.id][s.id - this->n];
            t += edge.weight;
            edge.cost = t;
            edge.heuristic = this->heuristics[edge.id_target];

            this->nos_abertos.push_back(s.id - this->n);
            this->foi_aberto.at(s.id - this->n) = true;

            StateInfos si;
            si.id = s.id - this->n;
            si.cost = t;
            si.heuristic = this->heuristics[si.id];
            this->aux_nos_abertos.push_back(si);

            if (this->IDAstarAux(si, goal, l, r, t, b, patamar))
            {
                this->solution.push_back(edge);
                return true;
            }
            else
            {
                if (patamar < min)
                {
                    min = patamar;
                }
            }
        }
    }

    // bottom
    if (s.id + this->n < this->order)
    {
        if (this->graph_matrix[s.id][s.id + this->n] != 0 && this->foi_fechado.at(s.id + this->n) == false)
        {
            SolutionEdge edge;
            edge.id_source = s.id;
            edge.id_target = s.id + this->n;
            edge.weight = this->graph_matrix[s.id][s.id + this->n];
            b += edge.weight;
            edge.cost = b;
            edge.heuristic = this->heuristics[edge.id_target];

            this->nos_abertos.push_back(s.id + this->n);
            this->foi_aberto.at(s.id + this->n) = true;

            StateInfos si;
            si.id = s.id + this->n;
            si.cost = b;
            si.heuristic = this->heuristics[si.id];
            this->aux_nos_abertos.push_back(si);

            if (this->IDAstarAux(si, goal, l, r, t, b, patamar))
            {
                this->solution.push_back(edge);
                this->nos_fechados.push_back(s.id);
                this->foi_fechado.at(s.id) = true;
                return true;
            }
            else
            {
                if (patamar < min)
                {
                    min = patamar;
                    this->nos_fechados.push_back(s.id);
                    this->foi_fechado.at(s.id) = true;
                    return false;
                }
            }
        }
    }

    this->nos_fechados.push_back(s.id);
    this->foi_fechado.at(s.id) = true;
    patamar = min;
    return false;
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
    }
    else
    {
        // if node id doesnt exist, create new node and first = last = new node
        Node *new_node = new Node(id);
        new_node->setPosition(this->order);
        new_node->setWeight(weight);
        this->first_node = new_node;
        this->last_node = new_node;
    }
    this->order = this->order + 1;
    this->n = ceil(sqrt(this->order));
}

void Graph::insertEdge(int source_id, float source_weight, int target_id, float target_weight, float edge_weight)
{
    Node *node = this->getNode(source_id);
    Node *aux = this->getNode(target_id);

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
        if (!node->searchEdge(target_id) && !aux->searchEdge(source_id))
        {
            node->insertEdge(target_id, aux->getPosition(), edge_weight);
            this->edges_count++;
            node->incrementOutDegree();
            aux->incrementOutDegree();

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
    Node *node = this->getNode(id);

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
    Node *node = this->getNode(id);

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

vector<int> Graph::possibleMvmts(int state)
{
    int last_line_start = this->n * (this->order / this->n);
    int element_line_type, element_col_type;
    vector<int> v;
    v.clear();

    if (state < this->n)
    {
        element_line_type = 1; // element in first line
    }
    else if (state >= last_line_start)
    {
        element_line_type = 2; // element in last line
    }
    else
    {
        element_line_type = 3; // element in intermediate lines
    }

    if (state % this->n == 0)
    {
        element_col_type = 1; // element in first column
    }
    else if ((state + 1) % this->n == 0)
    {
        element_col_type = 2; // element in last column
    }
    else
    {
        element_col_type = 3; // element in intermediate columns
    }

    if (element_line_type == 1)
    {
        if (element_col_type == 1)
        {
            v = {state + 1, state + this->n};
        }
        else if (element_col_type == 2)
        {
            v = {state - 1, state + this->n};
        }
        else if (element_col_type == 3)
        {
            v = {state + 1, state - 1, state + this->n};
        }
    }
    else if (element_line_type == 2)
    {
        if (element_col_type == 1)
        {
            v = {state + 1, state - this->n};
        }
        else if (element_col_type == 2)
        {
            v = {state - 1, state - this->n};
        }
        else if (element_col_type == 3)
        {
            v = {state + 1, state - 1, state - this->n};
        }
    }
    else if (element_line_type == 3)
    {
        if (element_col_type == 1)
        {
            v = {state + 1, state + this->n, state - this->n};
        }
        else if (element_col_type == 2)
        {
            v = {state - 1, state + this->n, state - this->n};
        }
        else if (element_col_type == 3)
        {
            if (state + this->n < this->order)
                v = {state + 1, state - 1, state + this->n, state - this->n};
            else
                v = {state + 1, state - 1, state - this->n};
        }
    }
    return v;
}

void Graph::reset()
{
    this->solution.clear();
    this->arestas_abertas.clear();
    this->nos_abertos.clear();
    this->aux_nos_abertos.clear();
    this->nos_fechados.clear();
    this->in_solution.clear();
    this->foi_aberto.clear();
    this->foi_fechado.clear();
    this->descartados.clear();
    for (int i = 0; i < this->order; i++)
    {
        this->in_solution.push_back(false);
        this->foi_aberto.push_back(false);
        this->foi_fechado.push_back(false);
    }
}

bool Graph::isEdgeInMaze(int source_id, int target_id)
{
    Node *n1 = this->getNode(source_id);
    Node *n2 = this->getNode(target_id);

    if (n1->searchEdge(target_id))
        return true;
    if (n2->searchEdge(source_id))
        return true;
    return false;
}

bool Graph::isEdgeInSolution(int source_id, int target_id)
{
    for (int i = 0; i < this->solution.size(); i++)
    {
        int s_id = this->solution[i].id_source;
        int t_id = this->solution[i].id_target;
        if ((s_id == source_id && t_id == target_id) || (t_id == source_id && s_id == target_id))
            return true;
    }
    return false;
}

void Graph::printEstatisticas()
{
    cout << endl;
    cout << "Caminho: ";
    int cost = 0;

    for (size_t i = 0; i < this->solution.size(); i++)
    {
        if (i + 1 == this->solution.size())
        {
            cout << this->solution.at(i).id_target << " --(" << this->solution.at(i).weight << ")-- " << this->solution.at(i).id_source << endl;
        }
        else
        {
            cout << this->solution.at(i).id_target << " --(" << this->solution.at(i).weight << ")-- ";
        }
        cost += this->solution.at(i).weight;
    }
    cout << "Profundidade: " << this->solution.size() << endl;
    cout << "Custo da Solução: " << cost << endl;
    cout << "Abertos: ";
    for (size_t i = 0; i < this->nos_abertos.size(); i++)
    {

        cout << this->nos_abertos[i] << " ";
    }
    cout << endl;
    cout << "Fechados: ";
    for (size_t i = 0; i < this->nos_fechados.size(); i++)
    {

        cout << this->nos_fechados[i] << " ";
    }
    cout << endl;
}

void Graph::printSolution()
{

    int maze_order = this->order;
    int n = ceil(sqrt(maze_order));
    int id = 0;
    int aux = id;
    string s;
    cout << endl;

    for (size_t i = 0; i < maze_order / n + 1; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (id < 10)
                s = " ";
            else
                s = "";

            cout << " " << s << id;

            if (this->isEdgeInSolution(id, id + 1))
            {
                cout << " ---";
            }
            else
            {
                cout << "    ";
            }

            id++;
            if (id >= maze_order)
            {
                cout << endl;
                return;
            }
        }
        cout << endl;
        for (size_t j = 0; j < n; j++)
        {
            if (aux < 10)
                s = " ";
            else
                s = "";

            cout << " " << s;

            if (this->isEdgeInSolution(aux, aux + n))
            {
                if (aux < 10)
                {
                    cout << "|    ";
                }
                else
                {
                    cout << " |    ";
                }
            }
            else
            {
                if (aux < 10)
                {
                    cout << "     ";
                }
                else
                {
                    cout << "      ";
                }
            }

            aux++;
            if (aux >= maze_order)
            {
                cout << endl;
                return;
            }
        }
        aux = id;
        cout << endl;
    }
}

vector<int> Graph::nodesToUse()
{
    vector<int> to_return;
    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        if (node->getOutDegree() > 0 && node->getOutDegree() < 4)
        {
            to_return.push_back(node->getId());
        }
    }
    return to_return;
}

bool Graph::isNode2Expand()
{
    for (size_t i = 0; i < this->foi_aberto.size(); i++)
    {
        if (this->foi_aberto.at(i) == false)
        {
            return true;
        }
    }
    return false;
}

void Graph::create_matrix()
{
    vector<vector<int>> matrix(this->order, vector<int>(this->order));

    this->graph_matrix = matrix;

    for (size_t i = 0; i < this->order; i++)
    {
        // inicializar a matrix representativa do grafo com G[i][j] = peso
        for (size_t j = 0; j < this->order; j++)
        {
            if (j == i)
            {
                this->graph_matrix.at(i).at(j) = 0;
            }
            else
            {
                int cost;
                if (this->getNode(i)->getEdge(j) != nullptr)
                {
                    cost = this->getNode(i)->getEdge(j)->getWeight();
                }
                else
                {
                    cost = 0;
                }
                this->graph_matrix.at(i).at(j) = cost;
            }
        }
    }
}

vector<vector<int>> Graph::get_graph_matrix()
{
    return this->graph_matrix;
}

void Graph::dijsktra(int goal)
{
    this->heuristics.clear();
    this->in_solution.clear();

    for (int i = 0; i < this->order; i++)
    {
        this->heuristics.push_back(99999); // infinity
        this->in_solution.push_back(false);
    }

    this->heuristics[goal] = 0;

    // Find shortest path for all nodes
    for (int count = 0; count < this->order - 1; count++)
    {
        int min = 99999;
        int u;

        for (int v = 0; v < this->order; v++)
        {
            if (this->in_solution[v] == false && this->heuristics[v] <= min)
            {
                min = this->heuristics[v];
                u = v;
            }
        }

        this->in_solution[u] = true; // Mark the picked node as processed

        // Update dist value of the adjacent nodes of the picked node
        for (int v = 0; v < this->order; v++)
            if (!this->in_solution[v] && this->graph_matrix[u][v] && this->heuristics[u] != 99999 && this->heuristics[u] + this->graph_matrix[u][v] < this->heuristics[v])
                this->heuristics[v] = this->heuristics[u] + this->graph_matrix[u][v];
    }
}