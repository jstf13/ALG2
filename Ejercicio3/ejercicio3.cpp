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
    int weight;
    Arista(int aOrigen, int aDestino, int aWeight) : origen(aOrigen), destino(aDestino), weight(aWeight) {}
};

typedef NodoLista<Arista> *ListaAristas;

class Grafo
{
public:
    virtual void insertarArista(int origen, int destino, int weight) = 0;
    virtual ListaAristas adyacentes(int origen) = 0;
    virtual void dfs(int salida, bool listaVisitados[]) = 0;
    virtual void sortAdyacentList(ListaAristas *list, int amountOfVertex) = 0;
    virtual ListaAristas *getAdyacentList() = 0;
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

    void insertarArista(int origen, int destino, int wheight)
    {
        Arista a = Arista(origen, destino, wheight);
        NodoLista<Arista> *nuevo = new NodoLista<Arista>(a, listaAdyacencia[origen]);
        listaAdyacencia[origen] = nuevo;

        if (origen != destino)
        {
            Arista a2 = Arista(destino, origen, wheight);
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
            // cout << "while dfs adentro" << endl;
            if (adyacentes->dato.destino && listaVisitados[adyacentes->dato.destino] == false)
            {
                destino = adyacentes->dato.destino;
                dfs(destino, listaVisitados);
            }
            adyacentes = adyacentes->sig;
        }
    }

    // void sortAdyacentList() with bubble sort and sort by weight
    void sortAdyacentList(ListaAristas *list, int amountOfVertex)
    {
        for (int i = 0; i < amountOfVertex; i++)
        {
            ListaAristas aux = list[i];
            ListaAristas aux2 = list[i];
            while (aux != NULL)
            {
                while (aux2 != NULL)
                {
                    if (aux->dato.destino < aux2->dato.destino)
                    {
                        Arista auxArista = aux->dato;
                        aux->dato = aux2->dato;
                        aux2->dato = auxArista;
                    }
                    aux2 = aux2->sig;
                }
                aux = aux->sig;
                aux2 = list[i];
            }
        }
    }

    ListaAristas *getAdyacentList()
    {
        return this->listaAdyacencia;
    }

    void imprimir()
    {
        for (int i = 1; i <= vertice; i++)
        {
            ListaAristas adyacentes = listaAdyacencia[i];
            while (adyacentes != NULL)
            {
                cout << i << " " << adyacentes->dato.destino << " " << adyacentes->dato.weight << endl;
                adyacentes = adyacentes->sig;
            }
        }
    }
};

// disjoin set
class DisjoinSet
{
private:
    int *parent;
    int *rank;
    int n;

public:
    DisjoinSet(int n)
    {
        this->n = n;
        this->parent = new int[n + 1];
        this->rank = new int[n + 1];

        for (int i = 0; i <= n; i++)
        {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (u != parent[u])
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (rank[x] > rank[y])
        {
            parent[y] = x;
        }
        else
        {
            parent[x] = y;
        }

        if (rank[x] == rank[y])
        {
            rank[y]++;
        }
    }
};

// Kruksal with disjoint set implementation with NodoLista
int kruskal(ListaAdyacencia list, int cantidadVertices, NodoLista<int> *vertexToIgnore, int amountOfVertexToIgnore)
{
    ListaAristas *adyacentList = list.getAdyacentList();
    // inicializar el conjunto disjunto
    DisjoinSet *disjoinSet = new DisjoinSet(cantidadVertices);
 
    // inicializar el índice para el resultado
    int index = 0;
 
    // inicializar el resultado
    ListaAristas *resultado = new ListaAristas[cantidadVertices];
 
    // ordenar las aristas en orden creciente de peso
    list.sortAdyacentList(adyacentList, cantidadVertices);

cout << "------------------" << endl;
    list.imprimir();
cout << "------------------" << endl;

 
    // recorrer las aristas ordenadas
    for (int i = 1; i <= cantidadVertices; i++)
    {
        ListaAristas adyacentes = adyacentList[i];
        while (adyacentes != NULL)
        {
            int origen = adyacentes->dato.origen;
            int destino = adyacentes->dato.destino;
 
            int x = disjoinSet->find(origen);
            int y = disjoinSet->find(destino);
 
            //Si no existen en vertexToIgnore
            NodoLista<int> *aux = vertexToIgnore;
            bool isIgnored = false;
            for (int i = 0; i < amountOfVertexToIgnore; i++)
            {
                if (x == aux->dato || y == aux->dato)
                    isIgnored = true;
                aux = aux->sig;
            }
            
            // si no forma un ciclo, incluir la arista
            if (x != y && !isIgnored)
            {
                resultado[index] = new NodoLista<Arista>(adyacentes->dato, resultado[index]);
                index++;
                disjoinSet->merge(x, y);
            }
            adyacentes = adyacentes->sig;
        }
    }
    // print resultado
    for (int i = 0; i < index; i++)
    {
        cout << resultado[i]->dato.origen << " " << resultado[i]->dato.destino << " " << resultado[i]->dato.weight << endl;
    }   
}

bool *inicializarVisitados(int cantidadVertices, bool visitados[])
{
    for (int i = 1; i <= cantidadVertices; i++)
    {
        visitados[i] *= false;
    }
    return visitados;
}


int main(){
    
    int vertexAmount;
    int edgeAmount;

    int originVertex;
    int destinyVertex;
    int weight;

    int amoutOfVertexToIgnore;
    int vetexToIgnore;

    cin >> vertexAmount;
    cin >> edgeAmount;

    ListaAdyacencia *grafo = new ListaAdyacencia(vertexAmount);

    for (int i = 0; i < edgeAmount; i++)
    {
        cin >> originVertex;
        cin >> destinyVertex;
        cin >> weight;
        grafo->insertarArista(originVertex, destinyVertex, weight);
    }
    grafo->imprimir();

    cin >> amoutOfVertexToIgnore;
    NodoLista<int> *vertexToIgnore;

    for (int i = 0; i < amoutOfVertexToIgnore; i++)
    {
        cin >> vetexToIgnore;
        vertexToIgnore = new NodoLista<int>(vetexToIgnore, vertexToIgnore);
    }


    cout << "Kruskal" << endl;
    cout << " " << endl;
    kruskal(*grafo, vertexAmount, vertexToIgnore, amoutOfVertexToIgnore);
    cout << " " << endl;
    cout << "Kruskal end" << endl;

    return 0;
}