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

struct Edge
{
    int origen;
    int destino;
    int weight;
    Edge(){}
    Edge(int aOrigen, int aDestino, int aWeight) : origen(aOrigen), destino(aDestino), weight(aWeight) {}
};

typedef NodoLista<Edge> *EdgeList;


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
    virtual void AddEdge(int origin, int destiny, int wheight) = 0;
    virtual void kruskal(int *vertexToIgnore) = 0;
    virtual void imprimir() = 0;
};

class GraphAdyacenceList : public Grafo
{
private:
    EdgeList *listaAdyacencia;
    int vertex;
    int edge;
    int destination;

    int getNotProcecedEdge(Edge *edges, bool *proceced)
    {
        int min = -1;
        int lowerValue;
        for (int i = 0; i < edge; i++)
        {
            if (!proceced[i])
            {
                if (min == -1 || lowerValue > edges[i].weight)
                {
                    min = i;
                    lowerValue = edges[i].weight;
                }
            }
        }
        return min;
    }

    void loadEdges(Edge *edges)
    {
        int i = 0;
        for (int j = 1; j < vertex; j++)
        {
            EdgeList aux = listaAdyacencia[j];
            while (aux != NULL)
            {
                Edge edge = aux->dato;
                if(j < edge.destino){
                    edges[i++] = edge;
                }
                aux = aux->sig;
            }
        }
    }
 
public:
    GraphAdyacenceList(int vertexAmount)
    {
        this->listaAdyacencia = new EdgeList[vertexAmount + 1];
        this->vertex = vertexAmount;
        this->edge = 0;
        this->destination = 0;

        for (int i = 1; i <= vertexAmount; i++)
        {
            listaAdyacencia[i] = NULL;
        }
    }

    void AddEdge(int origin, int destiny, int wheight)
    {
        Edge a = Edge(origin, destiny, wheight);
        NodoLista<Edge> *nuevo = new NodoLista<Edge>(a, listaAdyacencia[origin]);
        listaAdyacencia[origin] = nuevo;

        if (origin != destiny)
        {
            Edge a2 = Edge(destiny, origin, wheight);
            NodoLista<Edge> *nuevo2 = new NodoLista<Edge>(a2, listaAdyacencia[destiny]);
            listaAdyacencia[destiny] = nuevo2;
        }
        this->edge++;
    }

    EdgeList adyacentsTo(int origin)
    {
        EdgeList listToReturn = NULL;
        EdgeList aux = EdgeList(origin);
        while (aux != NULL)
        {
            Edge auxEdge = aux->dato;
            listToReturn = new NodoLista<Edge>(auxEdge, listToReturn);
            aux = aux->sig;
        }
        return listToReturn;
    }

    void SortList(Edge *edges, int n, bool *utilizados){
        int i = 0;
        int j = n - 1;
        Edge pivot = edges[n / 2];
        while (i <= j)
        {
            while (edges[i].origen < pivot.origen || (edges[i].origen == pivot.origen && edges[i].destino < pivot.destino))
            {
                i++;
            }
            while (edges[j].origen > pivot.origen || (edges[j].origen == pivot.origen && edges[j].destino > pivot.destino))
            {
                j--;
            }
            if (i <= j)
            {
                Edge aux = edges[i];
                edges[i] = edges[j];
                edges[j] = aux;
                bool aux2 = utilizados[i];
                utilizados[i] = utilizados[j];
                utilizados[j] = aux2;
                i++;
                j--;
            }
        }
        if (j > 0)
        {
            SortList(edges, j + 1, utilizados);
        }
        if (i < n)
        {
            SortList(edges + i, n - i, utilizados + i);
        }
    }


    void kruskal(int *vertexToIgnore)
    {
        Edge *edges = new Edge[edge];
        bool *proceced = new bool[edge]();
        bool *utilized = new bool[edge]();
        DisjoinSet *disjoinSet = new DisjoinSet(vertex + 1);

        loadEdges(edges);

        for (int i = 0; i < edge; i++)
        {
            int lowerNotVisitedEdge = getNotProcecedEdge(edges, proceced);
            Edge minEedge = edges[lowerNotVisitedEdge];
            proceced[lowerNotVisitedEdge] = true;

            if (vertexToIgnore[minEedge.origen] == 0 && vertexToIgnore[minEedge.destino] == 0)
            {
                if(disjoinSet->find(minEedge.origen) != disjoinSet->find(minEedge.destino)){
                    utilized[lowerNotVisitedEdge] = true;
                    disjoinSet->merge(minEedge.origen, minEedge.destino);
                }
            }
        }
        SortList(edges, edge, utilized);

        int total = 0;
        for (int i = 0; i < edge; i++)
        {
            if(utilized[i]){
                total++;
            }
        }
        cout << total << endl;

        for (int i = 0; i < edge; i++)
        {
            if(utilized[i]){
                cout << edges[i].origen << " " << edges[i].destino << " " << edges[i].weight << endl;
            }
        }
    }    

    void imprimir()
    {
        for (int i = 1; i <= vertex; i++)
        {
            EdgeList adyacentes = listaAdyacencia[i];
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
    
    int vertexAmount;
    int edgeAmount;

    int originVertex;
    int destinyVertex;
    int weight;

    int amoutOfVertexToIgnore;
    int vertexToIgnore;

    cin >> vertexAmount;
    cin >> edgeAmount;

    Grafo *graph = new GraphAdyacenceList(vertexAmount);
    bool *proceced = new bool[edgeAmount];

    for (int i = 0; i < edgeAmount; i++)
    {
        cin >> originVertex;
        cin >> destinyVertex;
        cin >> weight;
        graph->AddEdge(originVertex, destinyVertex, weight);
    }

    cin >> amoutOfVertexToIgnore;
    int *vertexToIgnoreList = new int[vertexAmount + 1];

    for (int i = 1; i <= vertexAmount; i++)
    {
        vertexToIgnoreList[i] = 0;
    }

    for (int i = 1; i <= vertexAmount; i++)
    {
        cin >> vertexToIgnore;
        vertexToIgnoreList[vertexToIgnore] = 1;
    }

    graph->kruskal(vertexToIgnoreList);

    return 0;
}