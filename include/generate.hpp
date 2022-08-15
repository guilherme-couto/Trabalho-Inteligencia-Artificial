#ifndef GENERATE_HPP_INCLUDED
#define GENERATE_HPP_INCLUDED

#include "Graph.hpp"
#include "defines.hpp"
#include "random/Xoshiro256plus.h"

using namespace std;

int matrixTargetNode(int maze_order, int source)
{
    int n = ceil(sqrt(maze_order)); // to represent maze as a matrix
    int last_line_start = n * (maze_order / n);
    int element_line_type, element_col_type;
    int target = -1;
    vector<int> v;
    v.clear();

    if (source < n)
    {
        element_line_type = 1; // element in first line
    }
    else if (source >= last_line_start)
    {
        element_line_type = 2; // element in last line
    }
    else
    {
        element_line_type = 3; // element in intermediate lines
    }

    if (source % n == 0)
    {
        element_col_type = 1; // element in first column
    }
    else if ((source + 1) % n == 0)
    {
        element_col_type = 2; // element in last column
    }
    else
    {
        element_col_type = 3; // element in intermediate columns
    }

    do
    {
        if (element_line_type == 1)
        {
            if (element_col_type == 1)
            {
                v = {source + 1, source + n};
            }
            else if (element_col_type == 2)
            {
                v = {source - 1, source + n};
            }
            else if (element_col_type == 3)
            {
                v = {source + 1, source - 1, source + n};
            }
        }
        else if (element_line_type == 2)
        {
            if (element_col_type == 1)
            {
                v = {source + 1, source - n};
            }
            else if (element_col_type == 2)
            {
                v = {source - 1, source - n};
            }
            else if (element_col_type == 3)
            {
                v = {source + 1, source - 1, source - n};
            }
        }
        else if (element_line_type == 3)
        {
            if (element_col_type == 1)
            {
                v = {source + 1, source + n, source - n};
            }
            else if (element_col_type == 2)
            {
                v = {source - 1, source + n, source - n};
            }
            else if (element_col_type == 3)
            {
                v = {source + 1, source - 1, source + n, source - n};
            }
        }

        Xoshiro256plus rand(time(NULL));
        int random_number;
        random_number = rand.next() % v.size();
        target = v[random_number];
    } while (target >= maze_order);

    return target;
}

Graph *genRandomMaze(int maze_order)
{
    Xoshiro256plus rand(time(NULL));
    Graph *maze2return = new Graph();

    int random_number;

    // 1st: insert nodes
    for (size_t i = 0; i < maze_order; i++)
    {
        maze2return->insertNode(i, 0.0);
    }

    // 2nd: create path from start to finish
    int source = 0; // 0 is the start
    int target = -1;

    while (target != maze_order - 1)
    {
        target = matrixTargetNode(maze_order, source);
        if (target > maze_order - 1)
            cout << "source " << source << " -- target " << target << endl;
        int cost = rand.next() % 20;
        maze2return->insertEdge(source, 0.0, target, 0.0, cost+1);
        source = target;
    }

    // 3rd: add some random edges if some node isnt being used
    while (!maze2return->allNodesUsed())
    {
        vector<int> rcl = maze2return->nodesToUse();
        int source_index = rand.next() % rcl.size();
        source = rcl.at(source_index); // restricted candidate list

        if (source != maze_order - 1)
        {
            target = matrixTargetNode(maze_order, source);
            if (maze2return->getNode(target)->getOutDegree() == 0)
            {
                int cost = rand.next() % 20;
                maze2return->insertEdge(source, 0.0, target, 0.0, cost+1);
            }
        }
    }
    return maze2return;
}

void printMaze(Graph *maze)
{
    int maze_order = maze->getOrder();
    int n = ceil(sqrt(maze_order));
    int id = 0;
    int aux = id;
    string s;

    cout << "\nEntrance: " << 0 << endl;
    cout << "Exit: " << maze_order - 1 << endl;
    cout << "Edges weight (id id weight):" << endl;
    for (Node *node = maze->getFirstNode(); node != nullptr; node = node->getNextNode())
    {
        for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            if (edge->getPrinted() == false)
            {
                cout << "(" << node->getId() << " " << edge->getTargetId() << " " << edge->getWeight() << ")  ";
                edge->setPrinted(true);
                Edge *aux = maze->getNode(edge->getTargetId())->getEdge(node->getId());
                aux->setPrinted(true);
            }
        }
    }

    cout << "\n\n\n"
         << endl;

    for (size_t i = 0; i < maze_order / n + 1; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (id < 10)
                s = " ";
            else
                s = "";

            cout << " " << s << id;

            if (maze->getNode(id)->getEdge(id + 1) != nullptr)
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

            if (maze->getNode(aux)->getEdge(aux + n) != nullptr)
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

#endif // GENERATE_HPP_INCLUDED