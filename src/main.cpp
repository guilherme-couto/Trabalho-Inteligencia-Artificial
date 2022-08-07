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

    cout << "\nBuilding a random maze..." << endl;
    Graph *maze = genRandomMaze(maze_order);
    cout << "Maze order: " << maze->getOrder() << endl;
    cout << "Maze edges count: " << maze->getNumberEdges() << endl;
    cout << "Maze done!" << endl;
    cout << "Print maze? (y/n) ";
    string yon;
    cin >> yon;
    if(yon == "y" || yon == "Y")
        printMaze(maze);

    int option;
    do
    {
        cout << "\nEscolha uma opção\n" << endl;
        cout << "1 - Backtracking" << endl;
        cout << "2 - Busca em Largura" << endl;
        cout << "3 - Busca em Profundidade" << endl;
        cout << "4 - Busca Ordenada" << endl;
        cout << "5 - Busca Gulosa" << endl;
        cout << "6 - Busca A*" << endl;
        cout << "7 - Busca IDA*" << endl;
        cout << "8 - Todas as buscas" << endl;
        cout << "0 - Sair" << endl;
        cout << "\nSua opcao: ";
        cin >> option;
    } while (option != 0 );

    return 0;
}
