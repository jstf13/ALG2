#include <cassert>
#include <string>
#include <iostream>
using namespace std;


void mochilaINFRecorrido(int capacidad, int cantidadObjetos, int pesos[])
{
    int **m = new int *[cantidadObjetos + 1];
    for (int i = 0; i < cantidadObjetos + 1; i++)
    {
        m[i] = new int[capacidad + 1]();
    }

    for (int objetoHasta = 1; objetoHasta < cantidadObjetos + 1; objetoHasta++)
    {
        for (int capacidadHasta = 0; capacidadHasta < capacidad + 1; capacidadHasta++)
        {
            if (pesos[objetoHasta - 1] > capacidadHasta)
            {
                m[objetoHasta][capacidadHasta] = m[objetoHasta - 1][capacidadHasta];
            }
        
            else
            {
                int valorMochilaDePonerlo = pesos[objetoHasta - 1] + m[objetoHasta][capacidadHasta - pesos[objetoHasta - 1]];
                int valorMochilaDeNOPonerlo = m[objetoHasta - 1][capacidadHasta];
                m[objetoHasta][capacidadHasta] = valorMochilaDePonerlo > valorMochilaDeNOPonerlo ? valorMochilaDePonerlo : valorMochilaDeNOPonerlo;
            }
        }
    }

    if (m[cantidadObjetos][capacidad] == capacidad) 
    {
        cout << "1" << endl;
    } 
    else 
    {
        cout << "0" << endl;
    } 
}

int main()
{
    int N;
    cin >> N; // cantidad de elementos 
    
    int valores[N];
    int elemento;
    
    for (int i = 0; i<N; i++)
    {
        cin >> elemento;
        valores[i] = elemento;
    }
    
    int P;
    cin>> P; // cantidad casos de prueba
    
    int X;
    cin>> X; //Preguntar a qué refiere este número? Es igual a P?

    int M = 0; // número al que se debe llegar con la suma
    
    for (int i = 0; i < P; i++)
    {
        cin>> M;
        mochilaINFRecorrido(M, N, valores) ;
    }
   
    return 0;
}


