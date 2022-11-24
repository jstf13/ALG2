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

bool sonTodosTrue(int *listaVisitados, int verticeAEvaluar ,int cantidadVertices)
{
    for (int i = 1; i <= cantidadVertices; i++)
    {
        if (i != verticeAEvaluar && listaVisitados[i] == 0)
        {
            return false;
        }
    }
    return true;
}

void DFS(Grafo *grafo, int origen, int prohibido, int *visitados){
    if(origen == prohibido)
        return;

    visitados[origen] = 1;
    ListaAristas adyacentes = grafo->adyacentes(origen);

    ListaAristas aux = adyacentes;
    while(aux != NULL){
        aux = aux->sig;
    }

    while(adyacentes != NULL){
        int destinoArista = adyacentes->dato.destino;
        if(!visitados[destinoArista]){
            DFS(grafo, destinoArista, prohibido, visitados);
        }
        adyacentes = adyacentes->sig;
    }
}

int *inicializarVisitados(int cantidadVertices){
    int *visitados = new int[cantidadVertices + 1];
    for(int i = 1; i <= cantidadVertices; i++){
        visitados[i] = 0;
    }
    return visitados;
}

bool esPuntoDeArticulacion(Grafo *grafo, int verticeAEvaluarA, int verticeAEvaluearB, int cantidadDeVertices){
    int *visitados = inicializarVisitados(cantidadDeVertices);

    ListaAristas adyacentes = grafo->adyacentes(verticeAEvaluarA);
    int nodoSalida = adyacentes->dato.destino;
    DFS(grafo, nodoSalida, verticeAEvaluarA, visitados);
    if(!sonTodosTrue(visitados, verticeAEvaluarA, cantidadDeVertices))
        return true;

    visitados = inicializarVisitados(cantidadDeVertices);

    adyacentes = grafo->adyacentes(verticeAEvaluearB);
    nodoSalida = adyacentes->dato.destino;

    DFS(grafo, nodoSalida, verticeAEvaluearB, visitados);
    if(!sonTodosTrue(visitados, verticeAEvaluearB, cantidadDeVertices))
        return true;

    return false;
}

bool esTriconexo(Grafo *grafo, int cantidadVertices)
{
    for (int i = 1; i <= cantidadVertices; i++)
    {
        for (int j = 1; j <= cantidadVertices; j++)
        {
            if(i != j && esPuntoDeArticulacion(grafo, i, j, cantidadVertices)){
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
    
    if(esTriconexo(grafo, cantidadVertices)){
        cout << 1 << endl;
    }else{
        cout << 0 << endl;
    }
    return 0;
};