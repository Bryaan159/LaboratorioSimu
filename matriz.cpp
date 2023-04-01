//Construya una funcion que reciba una matriz y 2 enteros a y b que reemplace todas las ocurrencias de a por b
#include <iostream>
#include <cstdlib>
using namespace std;

void reemplazarMatriz(int** matriz, int* row , int* col, int* a, int* b)
{   
    bool encontrado = false;
    for(int k = 0; k<(*row)*(*col);k++){
        if(matriz[k/(*col)][k%(*col)] == *a){
            matriz[k/(*col)][k%(*col)] = *b;
            encontrado = true;
        }
    }
    if(encontrado == false)
        cout<<"El numero no se encuentra en la matriz \n";
        cout<<"\n";
    return;
}
void mostrar(int** matrizNumero, int nrow, int ncol){
    for(int k = 0; k<nrow*ncol;k++){
        cout<<matrizNumero[k/ncol][k%nrow]<<" ";
        if ((k + 1) % ncol == 0) {
        cout << endl; // Salto de línea después de cada fila
        }
    }
}
int main()
{
    //Matriz quemada
    //En este caso la matriz es de 3x3
    int n = 3;
    int &nrow = n; int &ncol = n;
    int** matrizNumero  = (int**) malloc(sizeof(int*)*n);

    //Se accede para poder convertirlo en matriz bidimensional
    for(int i = 0;i<n;i++){
        matrizNumero[i] = (int*) malloc(sizeof(int)*n);
    }

    matrizNumero [0][0] = 10;   matrizNumero [0][1] = 11;   matrizNumero [0][2] = 12;
    matrizNumero [1][0] = 20;   matrizNumero [1][1] = 21;   matrizNumero [1][2] = 22;
    matrizNumero [2][0] = 30;   matrizNumero [2][1] = 31;   matrizNumero [2][2] = 32;

    cout<<"La posicion [0][0] es:  "<<*(*(matrizNumero +0)+0)<<"\n";


    //Mostrar la matriz original
    mostrar(matrizNumero,nrow,ncol);

    int numeroCambiar;
    int numeroComparar;
    //En cuestiones de la matriz los datos estan quemados por lo tanto tendra que verla primero
    cout <<"Ingrese el numero que desea comparar:\n ";
    cin >> numeroComparar;

    cout <<"Ingrese el numero que desea cambiar:\n ";
    cin >> numeroCambiar;

    //Para poder reemplazar el numero que entro y por el nuevo
    reemplazarMatriz(matrizNumero, &nrow, &ncol, &numeroComparar, &numeroCambiar);

    //Mostrar la matriz modificada
    mostrar(matrizNumero,nrow,ncol);

    //Liberar la memoria
    for (int i = 0; i < n; i++) {
        free(matrizNumero[i]);
    }
    free(matrizNumero);
    cout<<"El espacio de memoria ya es liberado \n";
    return 0;
}