#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int buscarSolitario(int *elementos, int posicion, int inicio, int fin) {
    int aBuscar;
    int mitad =  (inicio + fin) / 2;
    aBuscar = elementos[posicion + 1];

    if(elementos[posicion] != aBuscar) {
        return elementos[posicion];
    }
    if(elementos[mitad] > aBuscar) {
        return buscarSolitario(elementos, (posicion + 2), inicio, mitad);
    }
    return buscarSolitario(elementos, (posicion + 2), (mitad + 1), fin);
}

int main() {
    
    int N;
    cin >> N; // cantidad de elementos 
    
    int C[N];
    int elemento;

    for (int i = 0; i < N; i++)
    {
        cin >> elemento;
        C[i] = elemento;
    }
    int noRepetido = buscarSolitario(C, 0, 0, N-1);
    
    if (noRepetido >= 0)
    {
        cout << noRepetido << endl;
    }

    return 0;
}
