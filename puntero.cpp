//Construya una funcion que determine si un numero que recibe por parametro es palindromo
#include <iostream>
using namespace std;
bool palindromo(int* n1){
    int original = *n1;
    int invertido = 0;

    while(*n1 !=0){
        //Se hace para que cuando tenga el ultimo digito 1234->4
        int digito = (*n1)%10;

        //esta parte hara que el numero se de a la inversa 1234->4321
        invertido = (invertido)*10+digito;

        //La condicion para que salga del while
        (*n1) /= 10;
    }
    return (original == invertido) ;
}
int main()
{
    int numB = 121;
    if(palindromo(&numB) == true){
            cout<<"El numero es polindromo \n";
    }
    else{
            cout<<"El numero no es polindromo \n";
    }

    return 0;
}