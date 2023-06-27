#include <iostream>
using namespace std;

// Se incluira todas las librerias de todos los archivos que se han creado
#include "geometry/mesh3D.hpp"
#include "math_utilities/matrix_operations.hpp"
#include "mef_utilities/mef_process.hpp"
#include "gid/input_output.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Code doesn´t work it must be:\n";
        cout << "-MEF filename\n";
        exit(EXIT_FAILURE);
    }
    Mesh3D M;

    cout << "Right now we are reading the geometry and mesh data...\n\n";
    string filename(argv[1]);
    read_input(filename, &M);

    short numNodes = M.getQuantity(NUM_NODES);
    short numElements = M.getQuantity(NUM_ELEMENTS);
    Matrix K(numNodes, numElements), local_Ks[numElements];
    Vector b(numNodes), local_bs[numElements];

    cout << "**********Creating local systems**********\n\n";
    // Aqui se agrega las funciones de mef_utilities
    create_local_systems(local_Ks, local_bs, numElements, &M);

    cout << "**********Performing Assembly**********\n\n";
    assembly(&K, &bm local_Ks, local_bs, numElements, &M);

    // K.show();
    // b.show();

    cout << "**********Applying Neumann Boundary Conditions**********\n\n";
    applyNeumannBoundaryConditions(&b, &M);

    // b.show();

    cout << "**********Applying Dirichlet Boundary Conditions**********\n\n";
    applyDirichletBoundaryConditions(&K, &b, &M);
    // K.show();
    // b.show();

    cout << "**********Solving global system**********\n\n";
    Vector T(b.getSize()), T_full(numNodes);
    solveSystem(&K, &b, &T);
    // T.show();

    cout << "**********Preparing results**********\n\n";
    mergeResultsWithDirichlet(&T, &T_full, numNodes, &M);
    // T_full.show();

    cout << "**********Writing output file**********\n\n";
    write_output(filename, &T_full);

    return 0;
}