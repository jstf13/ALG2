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
    cout << "retirar numero, solucion actual: " << solucionActual << endl;
    string numeroAnterior = numeros[objeto];
    cout << "numero anterior: " << numeroAnterior << endl;
    int largoNumeroAnterior = solucionActual.length() - numeroAnterior.length();
    cout << "largo: " << largoNumeroAnterior << endl;

    solucionActual = solucionActual.substr(0, largoNumeroAnterior);
    cout << "solucion luego de quitar: " << solucionActual << endl;

    usados[objeto] = false;
}

bool esMejorSolucion(string solucionActual, string mejorSolucion)
{
    if (solucionActual.length() < mejorSolucion.length())
    {
        cout << "esMejorSolucion 1 if: " << endl;
        return false;
    } 
    else if (solucionActual.length() > mejorSolucion.length())
    {
        cout << "esMejorSolucion 2 if: " << endl;
        return true;
    } 
    else
    {
        for (int i = 0; i <= solucionActual.length(); i++) 
        {
            if (solucionActual[i] < mejorSolucion[i]) 
            {
                cout << "solucionActual[i]: " << solucionActual[i] << endl;
                cout << "mejorSolucion[i]: " << mejorSolucion[i] << endl;
                return false;
            }
        }
    }
}

bool puedeMejorar(string solucionActual, string *numeros, int objeto, bool *usados)
{
    string aux = "";
    if (!usados[objeto])
    {
        aux = solucionActual + numeros[objeto];
        cout << "puede mejorar, aux: " << aux << endl;
        return esMejorSolucion(aux, solucionActual);
    }
    return esMejorSolucion(aux, solucionActual);
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
                cout << "BT es mejor solucion " << endl;
                mejorSolucion = solucionActual;
            }

            for(int j = 0; j < N; j++)
            {
                if (!usados[j]) 
                {
                    mejorSuma(numeros, N, usados, solucionActual, mejorSolucion);
                }
            }

            /*
            if (puedeMejorar(solucionActual, numeros, i, usados))
            {
                cout << "BT puede mejorar" << endl;
                mejorSuma(numeros, N, usados, solucionActual, mejorSolucion);
            }
            */
            //mejorSuma(numeros, N + 1, usados, solucionActual, mejorSolucion);
            retirarElNumero(numeros, i, solucionActual, usados);
        }
    }
}

int main()
{
    string solucion = "";
    int N = 3;
    bool usados[N];
    string numeros[N] = {"1", "2", "3"};
    for (int i = 0; i < N; i++)
    {
        usados[i] = false;
    }
    mejorSuma(numeros, N, usados, "", solucion);
    cout << solucion << endl;

    return 0;
}
