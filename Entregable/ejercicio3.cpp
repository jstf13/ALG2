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
    Arista(){}
    Arista(int aOrigen, int aDestino, int aWeight) : origen(aOrigen), destino(aDestino), weight(aWeight) {}
};

typedef NodoLista<Arista> *ListaAristas;

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

        for (int i = 0; i < n; i++)
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

        if(x == y)
            return;

        if (rank[x] > rank[y])
        {
            parent[y] = x;
        }
        else if(rank[x] < rank[y])
        {
            parent[x] = y;
        }

        else
        {
            parent[x] = y;
            rank[y]++;    
        }
    }
};


class Grafo
{
public:
    virtual void AgregarArista(int origin, int destiny, int wheight) = 0;
    virtual void kruskal(int *vertexToIgnore) = 0;
    virtual void imprimir() = 0;
};

class GrafoListaAdyacencia : public Grafo
{
private:
    ListaAristas *listaAdyacencia;
    int vertice;
    int arista;
    int destino;

    int getNoProcesados(Arista *aristas, bool *procesados)
    {
        int min = -1;
        int ValorMinimo;
        for (int i = 0; i < arista; i++)
        {
            if (!procesados[i])
            {
                if (min == -1 || ValorMinimo > aristas[i].weight)
                {
                    min = i;
                    ValorMinimo = aristas[i].weight;
                }
            }
        }
        return min;
    }

    void CargarAristas(Arista *aristas)
    {
        int i = 0;
        for (int j = 1; j < vertice; j++)
        {
            ListaAristas aux = listaAdyacencia[j];
            while (aux != NULL)
            {
                Arista arista = aux->dato;
                if(j < arista.destino){
                    aristas[i++] = arista;
                }
                aux = aux->sig;
            }
        }
    }
 
public:
    GrafoListaAdyacencia(int cantidadVertices)
    {
        this->listaAdyacencia = new ListaAristas[cantidadVertices + 1];
        this->vertice = cantidadVertices;
        this->arista = 0;
        this->destino = 0;

        for (int i = 1; i <= cantidadVertices; i++)
        {
            listaAdyacencia[i] = NULL;
        }
    }

    void AgregarArista(int origin, int destiny, int wheight)
    {
        Arista a = Arista(origin, destiny, wheight);
        NodoLista<Arista> *nuevo = new NodoLista<Arista>(a, listaAdyacencia[origin]);
        listaAdyacencia[origin] = nuevo;

        if (origin != destiny)
        {
            Arista a2 = Arista(destiny, origin, wheight);
            NodoLista<Arista> *nuevo2 = new NodoLista<Arista>(a2, listaAdyacencia[destiny]);
            listaAdyacencia[destiny] = nuevo2;
        }
        this->arista++;
    }

    ListaAristas AdyacentesA(int origin)
    {
        ListaAristas listToReturn = NULL;
        ListaAristas aux = ListaAristas(origin);
        while (aux != NULL)
        {
            Arista auxEdge = aux->dato;
            listToReturn = new NodoLista<Arista>(auxEdge, listToReturn);
            aux = aux->sig;
        }
        return listToReturn;
    }

    void SortList(Arista *aristas, int n, bool *utilizados){
        int i = 0;
        int j = n - 1;
        Arista pivot = aristas[n / 2];
        while (i <= j)
        {
            while (aristas[i].origen < pivot.origen || (aristas[i].origen == pivot.origen && aristas[i].destino < pivot.destino))
            {
                i++;
            }
            while (aristas[j].origen > pivot.origen || (aristas[j].origen == pivot.origen && aristas[j].destino > pivot.destino))
            {
                j--;
            }
            if (i <= j)
            {
                Arista aux = aristas[i];
                aristas[i] = aristas[j];
                aristas[j] = aux;
                bool aux2 = utilizados[i];
                utilizados[i] = utilizados[j];
                utilizados[j] = aux2;
                i++;
                j--;
            }
        }
        if (j > 0)
        {
            SortList(aristas, j + 1, utilizados);
        }
        if (i < n)
        {
            SortList(aristas + i, n - i, utilizados + i);
        }
    }


    void kruskal(int *verticesAIgnorar)
    {
        Arista *aristas = new Arista[arista];
        bool *proceced = new bool[arista]();
        bool *utilized = new bool[arista]();
        DisjoinSet *disjoinSet = new DisjoinSet(vertice + 1);

        CargarAristas(aristas);

        for (int i = 0; i < arista; i++)
        {
            int lowerNotVisitedEdge = getNoProcesados(aristas, proceced);
            Arista minEedge = aristas[lowerNotVisitedEdge];
            proceced[lowerNotVisitedEdge] = true;

            if (verticesAIgnorar[minEedge.origen] == 0 && verticesAIgnorar[minEedge.destino] == 0)
            {
                if(disjoinSet->find(minEedge.origen) != disjoinSet->find(minEedge.destino)){
                    utilized[lowerNotVisitedEdge] = true;
                    disjoinSet->merge(minEedge.origen, minEedge.destino);
                }
            }
        }
        SortList(aristas, arista, utilized);

        int total = 0;
        for (int i = 0; i < arista; i++)
        {
            if(utilized[i]){
                total++;
            }
        }
        cout << total << endl;

        for (int i = 0; i < arista; i++)
        {
            if(utilized[i]){
                cout << aristas[i].origen << " " << aristas[i].destino << " " << aristas[i].weight << endl;
            }
        }
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

bool *inicializarVisitados(int cantidadVertices, bool visitados[])
{
    for (int i = 1; i <= cantidadVertices; i++)
    {
        visitados[i] *= false;
    }
    return visitados;
}


int main(){
    
    int cantidadVertices;
    int cantidadAristas;

    int verticeOrigen;
    int verticeDestino;
    int peso;

    int cantidadVerticesIgnorar;
    int verticeIgnorar;

    cin >> cantidadVertices;
    cin >> cantidadAristas;

    Grafo *grafo = new GrafoListaAdyacencia(cantidadVertices);
    bool *procesado = new bool[cantidadAristas];

    for (int i = 0; i < cantidadAristas; i++)
    {
        cin >> verticeOrigen;
        cin >> verticeDestino;
        cin >> peso;
        grafo->AgregarArista(verticeOrigen, verticeDestino, peso);
    }

    cin >> cantidadVerticesIgnorar;
    int *vertexToIgnoreList = new int[cantidadVertices + 1];

    for (int i = 1; i <= cantidadVertices; i++)
    {
        vertexToIgnoreList[i] = 0;
    }

    for (int i = 1; i <= cantidadVertices; i++)
    {
        cin >> verticeIgnorar;
        vertexToIgnoreList[verticeIgnorar] = 1;
    }

    grafo->kruskal(vertexToIgnoreList);

    return 0;
}