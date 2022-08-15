#ifndef AE6A7111_91DB_4FA5_A8D1_BA926D46C876
#define AE6A7111_91DB_4FA5_A8D1_BA926D46C876

#include "defines.hpp"

struct SolutionEdge
{
    int id_source;
    int id_target;
    float weight;
    int cost;
    int heuristic;
};

struct StateInfos
{
    int parent;
    int id;
    int cost;
    int heuristic;
};

#endif /* AE6A7111_91DB_4FA5_A8D1_BA926D46C876 */
