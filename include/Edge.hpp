#ifndef EDGE_HPP_INCLUDED
#define EDGE_HPP_INCLUDED

using namespace std;

// Edge class
class Edge
{
private:
    int target_id;
    int target_position;
    Edge *next_edge;
    float weight;
    bool printed;

public:
    // Constructor and destructor
    Edge(int target_id, int target_position);
    ~Edge();

    // Getters
    int getTargetId();
    int getTargetPosition();
    Edge *getNextEdge();
    float getWeight();
    bool getPrinted();

    // Setters
    void setNextEdge(Edge *edge);
    void setWeight(float weight);
    void setPrinted(bool printed);
};

#endif // EDGE_HPP_INCLUDED