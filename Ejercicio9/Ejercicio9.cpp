#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

bool sePuedePodar(int candidataMetrica, int mejorSolucionMetrica)
{
    return candidataMetrica >= mejorSolucionMetrica;
}

bool esSolucion(int resto)
{
    return resto == 0;
}

bool esMejorSolucion(int candidataMetrica, int mejorSolucionMetrica)
{
    return candidataMetrica < mejorSolucionMetrica;
}

void clonarSolucion(int *origen, int *destino, int N)
{
    for (int i = 0; i < N; i++)
    {
        destino[i] = origen[i];
    }
}

bool puedoUsarNumero(int resto, int numero)
{
    return numero <= resto;
}

void usarNumero(int numero, int index, int &resto, int *candidata, int &candidataMetrica)
{
    resto -= numero;
    candidata[index]++;
    candidataMetrica++;
}

void desusarNumero(int numero, int index, int &resto, int *candidata, int &candidataMetrica)
{
    resto += numero;
    candidata[index]--;
    candidataMetrica--;
}

void sumatoria_bt(int resto, int *C, int N, int *candidata, int candidataMetrica, int *mejorSolucion, int &mejorSolucionMetrica)
{
    if (!sePuedePodar(candidataMetrica, mejorSolucionMetrica))
    {
        if (esSolucion(resto) && esMejorSolucion(candidataMetrica, mejorSolucionMetrica))
        {
            clonarSolucion(candidata, mejorSolucion, N);
            mejorSolucionMetrica = candidataMetrica;
        }
        else
        {
            for (int i = 0; i < N; i++)
            {
                int numero = C[i];
                if (puedoUsarNumero(resto, numero))
                {
                    usarNumero(numero, i, resto, candidata, candidataMetrica);
                    sumatoria_bt(resto, C, N, candidata, candidataMetrica, mejorSolucion, mejorSolucionMetrica);
                    desusarNumero(numero, i, resto, candidata, candidataMetrica);
                }
            }
        }
    }
}

void sumatoria(int *C, int N, int M)
{
    int *sandbox = new int[N + 1]();
    int *solucion = new int[N + 1]();
    int mejorSolucionMetrica = INT8_MAX;

    sumatoria_bt(M, C, N, sandbox, 0, solucion, mejorSolucionMetrica);
    if (mejorSolucionMetrica < INT8_MAX)
    {
        /*
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < solucion[i]; j++)
            {
                 cout << C[i] << endl;
            }
        }
        */
        cout << mejorSolucionMetrica << endl;
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
    
    int C[N];
    int elemento;
    
    for (int i = 0; i<N; i++)
    {
        cin >> elemento;
        C[i] = elemento;
    }
    
    int P;
    cin>> P; // cantidad casos de prueba
    
    int M = 0; // número al que se debe llegar con la suma
    //cin>> M;

    for (int i = 0; i < P; i++)
    {
        cin>> M;
        sumatoria(C, N, M);
    }
   
    return 0;
}