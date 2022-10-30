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

class Grafo
{
public:
    virtual void insertarArista(int origen, int destino) = 0;
    virtual ListaAristas adyacentes(int origen) = 0;
    virtual void dfs(int salida, bool listaVisitados[]) = 0;
    virtual void imprimir() = 0;
};

class ListaAdyacencia : public Grafo
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

        if (origen != destino)
        {
            Arista a2 = Arista(destino, origen);
            NodoLista<Arista> *nuevo2 = new NodoLista<Arista>(a2, listaAdyacencia[destino]);
            listaAdyacencia[destino] = nuevo2;
        }
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

bool sonTodosTrue(bool listaVisitados[], int cantidadVertices)
{
    for (int i = 1; i <= cantidadVertices; i++)
    {
        if (listaVisitados[i] == 0)
        {
            return false;
        }
    }
    return true;
}

bool esTriconexo(Grafo *grafo, int cantidadVertices)
{
    bool *visitados = new bool[cantidadVertices + 1]; 

    for (int i = 1; i <= cantidadVertices; i++)
    {
        for (int j = 1; j <= cantidadVertices; j++)
        {
            inicializarVisitados(cantidadVertices, visitados);

                visitados[i] = true;
                if(i != j)
                {
                    visitados[j] = true;
                    grafo->dfs(i, visitados);
                    
                    if (!sonTodosTrue(visitados, cantidadVertices))
                        return false;

                }
        }
    }
    return true;
}

int main()
{
    int cantidadVertices, numAristas;
    int origen, destino;

    cin >> cantidadVertices;
    cin >> numAristas;
    Grafo *grafo = new ListaAdyacencia(cantidadVertices);

    for (int i = 0; i < numAristas; i++)
    {
        cin >> origen >> destino;
        grafo->insertarArista(origen, destino);
    }

    cout << esTriconexo(grafo, cantidadVertices) << endl;
    return 0;
};