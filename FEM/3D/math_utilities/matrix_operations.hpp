// matrix_operations in 3D
#include <cmath>
#include "vector.hpp"
#include "matrix.hpp"

void product_scalar_by_matrix(float scalar, Matrix *M, int n, int m, Matrix *R)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            R->set(scalar * M->get(r, c), r, c);
}

void product_matrix_by_vector(Matrix *M, Vector *V, int n, int m, Vector *R)
{
    for (int r = 0; r < n; r++)
        float acc_n = 0;
    for (int c = 0; c < n; c++)
        acc_n += M->get(r, c) * V->get(c);
    R->set(acc_n, r);
}

// Funcion que se usara en MEF_Process
void product_matrix_by_matrix(Matrix *A, Matrix *B, Matrix *R)
{
    int n = A->getNrows(), m = A->getNcols, p = B->getNrows(), q = B->getNcols();
    if (m == p)
    {
        R->setSize(n, q);
        R->init();

        for (int r = 0; r < n; r++)
            for (int c = 0; c < q; c++)
                for (int i = 0; i < m; i++)
                    R->add(A->get(r, i) * B->get(i, c), r, c);
    }else{
        cout << "*****Dimension incompatibility when multiplying matrices.\n\n";
        exit(EXIT_FAILURE);
    }
}

float determinant(Matrix *M);

float determinant_auxiliar(Matrix *M)
{
    int n = M->getNcols();
    float acc_n = 0;

    for (int c = 0; c < n; c++)
    {
        Matrix clon(n, n);
        M->clone(&clon);
        clon.removeRow(0);
        clon.removeColumn(c);
        acc_n += pow(-1, c) * M->get(0, c) * determinant(&clon);
    }
    return acc_n;
}

float determinant(Matrix *M)
{
    float ans;
    switch (M->getNcols())
    {
    case 1:
        ans = M->get(0, 0);
        break;
    case 2:
        ans = M->get(0, 0) * M->get(1, 1) - M->get(0, 1) * M->get(1, 0);
        break;
    case 3:
        ans = M->get(0, 0) * M->get(1, 1) * M->get(2, 2) - M->get(0, 0) * M->get(1, 2) * M->get(2, 1) - M->get(0, 1) * M->get(1, 0) * M->get(2, 2) + M->get(0, 1) * M->get(1, 2) * M->get(2, 0) + M->get(0, 2) * M->get(1, 0) * M->get(2, 1) - M->get(0, 2) * M->get(1, 1) * M->get(2, 0);
        break;
    default:
        ans = determinant_auxiliar(M);
    }
    return ans;
}

float getMinor(Matrix *M, int n, int r, int c)
{
    Matrix clon(n, n);
    M->clone(&clon);

    // M.show();
    // clon.show();
    clon.removeRow(r);
    clon.removeColumn(c);

    // clon.show();
    return determinant(&clon);
}

void conjugate_matrix(Matrix *M, int n, Matrix *C)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            C->set(pow(-1, r + c) * get_minor(M, n, r, c), r, c);
}

// Funcion transpose
void transpose_matrix(Matrix *M, int n, int m, Matrix *T)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            T->set(M->get(r, c), c, r);
}

void calculate_inverse(Matrix *M, int n, Matrix *R)
{
    cout << "\t\t***Calculating determinant***\n";
    float detM = determinant(M);

    cout << "\t\t***Calculating conjugate Matrix***\n";
    Matrix Conjugate(n, n);
    conjugate_matrix(M, n, &Conjugate);

    cout << "\t\t***Calculating Adjunct Matrix***\n";
    Matrix Adjunct(n, n);
    transpose_matrix(&Conjugate, n, n, &Adjunct);
    // Adjunct.show();

    cout << "\t\t***Multiplying the Adjunct by the determinant.***\n";
    product_scalar_by_matrix(1 / detM, &Adjunct, n, n, R);
}