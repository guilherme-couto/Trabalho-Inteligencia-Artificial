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
    cout << "Done!" << endl;
    cout << "Print maze? (y/n) ";
    string yon;
    cin >> yon;
    if (yon == "y" || yon == "Y")
        printMaze(maze);

    maze->create_matrix();
    maze->dijsktra(maze_order - 1);

    int option;
    do
    {
        cout << "\n\nEscolha uma opção\n"
             << endl;
        cout << "1 - Backtracking"
             << "\t2 - Busca em Largura"
             << "\t3 - Busca em Profundidade" << endl;
        cout << "4 - Busca Ordenada"
             << "\t5 - Busca Gulosa"
             << "\t6 - Busca A*" << endl;
        cout << "7 - Busca IDA*"
             << "\t\t8 - Todas as buscas"
             << "\t0 - Sair" << endl;
        cout << "\nSua opcao: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            auto start = chrono::high_resolution_clock::now();
            maze->backtracking();
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;
        }
        break;

        case 2:
        {
            auto start = chrono::high_resolution_clock::now();
            maze->breadthFirstSearch();
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;
        }
        break;

        case 3:
        {
            auto start = chrono::high_resolution_clock::now();
            maze->deepSearch();
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;
        }
        break;

        case 4:
        {
            auto start = chrono::high_resolution_clock::now();
            maze->buscaOrdenada();
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;
        }
        break;

        case 5:
        {
            auto start = chrono::high_resolution_clock::now();
            maze->greedy();
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;
        }
        break;

        case 6:
        {
            auto start = chrono::high_resolution_clock::now();
            maze->Astar();
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;
        }
        break;

        case 7:
        {
            auto start = chrono::high_resolution_clock::now();
            maze->IDAstar();
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;
        }
        break;

        case 8:
        {
            auto start = chrono::high_resolution_clock::now();
            maze->backtracking();
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;

            start = chrono::high_resolution_clock::now();
            maze->breadthFirstSearch();
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;

            start = chrono::high_resolution_clock::now();
            maze->deepSearch();
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;

            start = chrono::high_resolution_clock::now();
            maze->buscaOrdenada();
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;

            start = chrono::high_resolution_clock::now();
            maze->greedy();
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;

            start = chrono::high_resolution_clock::now();
            maze->Astar();
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;

            start = chrono::high_resolution_clock::now();
            maze->IDAstar();
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout << "Duração: " << duration.count() << " ms" << endl;
        }
        break;

        default:
        {
            break;
        }
        }
    } while (option != 0);

    return 0;
}
