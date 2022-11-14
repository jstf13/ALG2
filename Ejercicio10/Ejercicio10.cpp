#include <cassert>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>
using namespace std;

void colocarTentativamenteElNumero(int numeros[], int objeto, int &solucionActual)
{
    solucionActual = solucionActual + numeros[objeto];
}
void retirarElNumero(int numeros[], int objeto, int &solucionActual)
{
    solucionActual = solucionActual - numeros[objeto];
}

bool esMejorSolucion(int solucionActual, int mejorSolucion)
{
    return solucionActual > mejorSolucion;
}

bool puedeMejorar(int solucionActual, int mejorSolucion)
{
    int aux = solucionActual + mejorSolucion;
    return aux > mejorSolucion;
}

void mejorSuma(int numeros[], int N, bool usados[], int solucionActual, int &mejorSolucion)
{
    for (int i = 0; i < N; i++)
    {
        if (!usados[i])
        {
            colocarTentativamenteElNumero(numeros, i, solucionActual);
            usados[i] = true;
            if (esMejorSolucion(solucionActual, mejorSolucion))
            {
                mejorSolucion = solucionActual;
            }
            
            if (puedeMejorar(solucionActual, mejorSolucion))
            {
                mejorSuma(numeros, N, usados, solucionActual, mejorSolucion);
            }
            
            retirarElNumero(numeros, i, solucionActual);
            usados[i] = false;
        }
    }
}

int main()
{
    int solucion = 0;
    int N = 8;
    bool usuados[N];
    int numeros[N] = {909, 11, 221, 9, 95, 4, 12, 1};
    for (int i = 0; i < N; i++)
    {
        usuados[i] = false;
    }
    mejorSuma(numeros, N, usuados, 0, solucion);
    cout << solucion << endl;

    return 0;
}
