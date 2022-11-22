#include <cassert>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>
using namespace std;

void colocarElNumero(string *numeros, int objeto, string &solucionActual, bool *usados)
{
    solucionActual = solucionActual + numeros[objeto];
    usados[objeto] = true;
}

void retirarElNumero(string *numeros, int objeto, string &solucionActual, bool *usados)
{
    string numeroAnterior = numeros[objeto];
    int largoNumeroAnterior = solucionActual.length() - numeroAnterior.length();
    solucionActual = solucionActual.substr(0, largoNumeroAnterior);
    usados[objeto] = false;
}

bool esMejorSolucion(string solucionActual, string mejorSolucion)
{
    if (solucionActual.length() < mejorSolucion.length())
    {
        return false;
    } 
    if (solucionActual.length() > mejorSolucion.length())
    {
        return true;
    }
    if (solucionActual.length() == mejorSolucion.length())
    {
        for (int i = 0; i <= solucionActual.length(); i++) 
        {
            if (solucionActual[i] > mejorSolucion[i]) 
            {
                return true;
            }
            else{
                if (solucionActual[i] < mejorSolucion[i]) 
                {
                    return false;
                }
            }
        }
    }
}

void mejorSuma(string *numeros, int N, bool *usados, string solucionActual, string &mejorSolucion)
{
    for (int i = 0; i < N; i++)
    {
        if (!usados[i])
        {
            colocarElNumero(numeros, i, solucionActual, usados);

            if (esMejorSolucion(solucionActual, mejorSolucion))
            {
                mejorSolucion = solucionActual;
            }

            for(int j = 0; j < N; j++)
            {
                if (!usados[j]) 
                {
                    mejorSuma(numeros, N, usados, solucionActual, mejorSolucion);
                }
            }
            retirarElNumero(numeros, i, solucionActual, usados);
        }
    }
}

int main()
{
    string solucion = "";
    int N;
    cin >> N;
    bool usados[N];
    string numeros[N];
    string elemento;

    for (int i = 0; i < N; i++)
    {
        usados[i] = false;
    }

    for (int i = 0; i < N; i++)
    {
        cin >> elemento;
        numeros[i] = elemento;
    }

    mejorSuma(numeros, N, usados, "", solucion);
    cout << solucion << endl;

    return 0;
}
