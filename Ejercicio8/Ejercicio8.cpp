#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int **mochilaINFRecorrido(int capacidad, int cantidadObjetos, int conjunto[], int valores[])
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
            if (conjunto[objetoHasta - 1] > capacidadHasta)
            {
                m[objetoHasta][capacidadHasta] = m[objetoHasta - 1][capacidadHasta];
            }
            else
            {
                int valorMochilaDePonerlo = valores[objetoHasta - 1] + m[objetoHasta][capacidadHasta - conjunto[objetoHasta - 1]];
                int valorMochilaDeNOPonerlo = m[objetoHasta - 1][capacidadHasta];
                m[objetoHasta][capacidadHasta] = valorMochilaDePonerlo > valorMochilaDeNOPonerlo ? valorMochilaDePonerlo : valorMochilaDeNOPonerlo;
            }
        }
    }
   return m;
}

int main()
{

    int N;
    cin >> N; // cantidad de objetos

    int *elementos = new int[N + 1]();
    for (int i = 1; i <= N; i++)
    {
        elementos[i] = 0;
    }

    int K; // cantidad de valores
    int *valores = new int[N + 1]();
    for (int i = 1; i < N + 1; i++)
    {
        cin >> K;
        valores[i] = K;
        elementos[i] = K;
    }

    int M;
    cin >> M; // capacidad de la mochila

    int **matriz = new int *[N + 1];
    for (int i = 0; i < N + 1; i++)
    {
        matriz[i] = new int[N + 1]();
    }
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 0; j < N + 1; j++)
        {
            matriz[i][j] = 0;
        }
    }

    matriz = mochilaINFRecorrido(M, N + 1, elementos, valores);

    int P;
    cin >> P;
    int m;
    for (int k = 1; k < P + 1; k++)
    {
        cin >> m;
        int valor = matriz[N + 1][m];
        if (k != P)
        {
            if (valor == m)
            {
                cout << "1" << endl;
            }
            else
            {
                cout << "0" << endl;
            }
        }else{
           if (valor == m)
            {
                cout << "1";
            }
            else
            {
                cout << "0";
            } 
        }
    }

    return 0;
}