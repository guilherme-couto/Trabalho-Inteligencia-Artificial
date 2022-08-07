#include "defines.hpp"
#include "Graph.hpp"
#include "generate.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    string program_name(argv[0]);

    cout << "Running " << program_name << "\n"
         << endl;

    int maze_order;
    do
    {
        cout << "How many nodes the maze will have? (min. 25 and max. 99)" << endl;
        cin >> maze_order;
    } while (maze_order < 25 || maze_order > 99);

    Graph *maze = genRandomMaze(maze_order);
    printMaze(maze);

    cout << "\nmaze order: " << maze->getOrder() << endl;
    cout << "maze edges count: " << maze->getNumberEdges() << endl;
    cout << endl;

    /* int option;
    do
    {
        cout << "How many nodes the maze will have? (min. 25 and max. 99)" << endl;
        cin >> maze_order;
    } while (option < 0 || maze_order > 99);

    return 0; */
}
