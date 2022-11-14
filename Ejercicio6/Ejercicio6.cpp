#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;


int buscarSolitario(int *elementos, int inicio, int fin) {

    if(inicio == fin) {
        return -1;
    }

    int mitad =  (inicio + fin) / 2;

    if(elementos[inicio] != elementos[inicio + 1]) {
        return elementos[inicio];
    }
    if(elementos[mitad] > elementos[inicio + 1]) {
        return buscarSolitario(elementos, inicio + 2, mitad);
    }
    return buscarSolitario(elementos, mitad + 1, fin);
}

int main() {
    
    int N;
    cin >> N; // cantidad de elementos 
    
    int C[N];
    int elemento;

    for (int i = 0; i<N; i++)
    {
        cin >> elemento;
        C[i] = elemento;
    }
    
    int noRepetido = buscarSolitario(C, 0, N-1);
    
    if (noRepetido >=0)
    {
        cout << noRepetido << endl;
    }

    /*
    int posicion = -1;
    posicion = buscarSolitario(C, 0, 101);
    
    if(posicion >= 0) {
        cout << "El elemento no repetido es " <<  posicion << endl;
    }
    */

    return 0;
}
