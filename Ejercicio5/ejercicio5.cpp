#include <cstdlib>
#include <iostream>
#include <cassert>

using namespace std;

template <class T>
struct NodoLista
{
    T dato;
    NodoLista *sig;
    NodoLista(T &aData) : dato(aData), sig(0) {}
    NodoLista(T &aData, NodoLista *aSig) : dato(aData), sig(aSig) {}
};

struct Arista
{
    int origen;
    int destino;
    Arista(int aOrigen, int aDestino) : origen(aOrigen), destino(aDestino) {}
};

typedef NodoLista<Arista> *ListaAristas;

class Graph
{
public:
    virtual void insertarArista(int origen, int destino) = 0;
    virtual ListaAristas adyacentes(int origen) = 0;
    virtual void dfs(int salida, bool listaVisitados[]) = 0;
    virtual void imprimir() = 0;
};

class ListaAdyacencia : public Graph
{
private:
    ListaAristas *listaAdyacencia;
    int vertice;
    int arista;
    int destino;

public:
    ListaAdyacencia(int cantidadVertices)
    {
        this->listaAdyacencia = new ListaAristas[cantidadVertices + 1];
        this->vertice = cantidadVertices;
        this->arista = 0;
        this->destino = 0;

        for (int i = 1; i <= cantidadVertices; i++)
        {
            listaAdyacencia[i] = 0;
        }
    }

    void insertarArista(int origen, int destino)
    {
        Arista a = Arista(origen, destino);
        NodoLista<Arista> *nuevo = new NodoLista<Arista>(a, listaAdyacencia[origen]);
        listaAdyacencia[origen] = nuevo;
    }

    ListaAristas adyacentes(int origen)
    {
        ListaAristas listaARetornar = NULL;
        ListaAristas aux = listaAdyacencia[origen];

        while (aux != NULL)
        {
            Arista aristaAux = aux->dato;
            listaARetornar = new NodoLista<Arista>(aristaAux, listaARetornar);
            aux = aux->sig;
        }
        return listaARetornar;
    }

    void dfs(int salida, bool listaVisitados[])
    {
        listaVisitados[salida] = true;
        ListaAristas adyacentes = listaAdyacencia[salida];

        while (adyacentes != NULL)
        {
            if (adyacentes->dato.destino && listaVisitados[adyacentes->dato.destino] == false)
            {
                destino = adyacentes->dato.destino;
                dfs(destino, listaVisitados);
            }
            adyacentes = adyacentes->sig;
        }
    }

    void imprimir()
    {
        for (int i = 1; i <= vertice; i++)
        {
            ListaAristas adyacentes = listaAdyacencia[i];
            while (adyacentes != NULL)
            {
                cout << i << " " << adyacentes->dato.destino << endl;
                adyacentes = adyacentes->sig;
            }
        }
    }
};

bool *inicializarVisitados(int cantidadVertices, bool visitados[])
{
    for (int i = 1; i <= cantidadVertices; i++)
    {
        visitados[i] *= false;
    }
    return visitados;
}