#include <cstdlib>
#include <vector>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Edge
{
    int origin;
    int destiny;
    int weight;
    Edge(int origin, int destiny, int weight) : origin(origin), destiny(destiny), weight(weight) {}
};

typedef vector<Edge> *ListaAristas;

class Grafo
{
public:
    virtual void insertarArista(int origin, int destiny, int weight) = 0;
    virtual vector<Edge> getListaAdyacencia() = 0;
    // virtual ListaAristas adyacentes(int origin) = 0;
    // virtual void dfs(int salida, bool listaVisitados[]) = 0;
    virtual void imprimir() = 0;
};

class ListaAdyacencia : public Grafo
{
private:
    vector<Edge> listaAdyacencia;
    int vertice;
    int edge;
    int destiny;

public:
    ListaAdyacencia(int cantidadVertices)
    {
        this->listaAdyacencia = vector<Edge>(cantidadVertices + 1);
        this->vertice = cantidadVertices;
        this->edge = 0;
        this->destiny = 0;
    }

    vector<Edge> getListaAdyacencia()
    {
        return this->listaAdyacencia;
    }

    void insertarArista(int origin, int destiny, int weight)
    {
        Edge e = Edge(origin, destiny, weight);
        listaAdyacencia.push_back(e);

        if (origin != destiny)
        {
            Edge e2 = Edge(destiny, origin, weight);
            listaAdyacencia.push_back(e2);
        }
    }

    // ListaAristas adyacentes(int origin)
    // {
    //     ListaAristas listaARetornar = NULL;
    //     ListaAristas aux = listaAdyacencia[origin];

    //     while (aux != NULL)
    //     {
    //         Edge aristaAux = aux->dato;
    //         listaARetornar = new NodoLista<Edge>(aristaAux, listaARetornar);
    //         aux = aux->sig;
    //     }
    //     return listaARetornar;
    // }

    // void dfs(int salida, bool listaVisitados[])
    // {
    //     listaVisitados[salida] = true;
    //     ListaAristas adyacentes = listaAdyacencia[salida];

    //     while (adyacentes != NULL)
    //     {
    //         // cout << "while dfs adentro" << endl;
    //         if (adyacentes->dato.destiny && listaVisitados[adyacentes->dato.destiny] == false)
    //         {
    //             destiny = adyacentes->dato.destiny;
    //             dfs(destiny, listaVisitados);
    //         }
    //         adyacentes = adyacentes->sig;
    //     }
    // }

    void imprimir()
    {
        for (int i = 0; i < listaAdyacencia.size(); i++)
        {
            cout << listaAdyacencia[i].origin << " " << listaAdyacencia[i].destiny << " " << listaAdyacencia[i].weight << endl;
        }
    }
};

class DisjointSet
{
    unordered_map<int, int> parent;
 
public:
    // realizar la operación MakeSet
    void makeSet(int n)
    {
        // crea `n` conjuntos disjuntos (uno para cada vértice)
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
 
    // Encuentra la raíz del conjunto al que pertenece el elemento `k`
    int Find(int k)
    {
        // si `k` es root
        if (parent[k] == k) {
            return k;
        }
 
        // recurre para el padre hasta que encontramos la raíz
        return Find(parent[k]);
    }
 
    // Realizar Unión de dos subconjuntos
    void Union(int a, int b)
    {
        // encuentra la raíz de los conjuntos en los que se encuentran los elementos
        // Pertenece `x` e `y`
        int x = Find(a);
        int y = Find(b);
 
        parent[x] = y;
    }
};

struct compare
{
    bool operator() (Edge const &a, Edge const &b) const {
        return a.weight > b.weight;
    }
};

// Función para construir MST usando el algoritmo de Kruskal
vector<Edge> runKruskalAlgorithm(vector<Edge> edges, int n)        
{
    // almacena los arista presentes en MST
    vector<Edge> MST;
 
    // inicializa la clase `DisjointSet`
    DisjointSet ds;
 
    // crea un conjunto singleton para cada elemento del universo
    ds.makeSet(n);
 
    // ordena las aristas aumentando el peso
    sort(edges.begin(), edges.end(), compare());
 
    // MST contiene exactamente los arista `V-1`
    while (MST.size() != n - 1)
    {
        // considera el siguiente borde con peso mínimo del graph
        Edge next_edge = edges.back();
        edges.pop_back();
 
        // encuentra la raíz de los conjuntos a los que pertenecen dos extremos
        // los vértices de la siguiente arista pertenecen
        int x = ds.Find(next_edge.origin);
        int y = ds.Find(next_edge.destiny);
 
        // si ambos extremos tienen diferentes padres, pertenecen a
        // diferentes componentes conectados y se pueden incluir en MST
        if (x != y)
        {
            MST.push_back(next_edge);
            ds.Union(x, y);
        }
    }
    return MST;
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

    cin >> vertexAmount;
    cin >> edgeAmount;

    Grafo *grafo = new ListaAdyacencia(vertexAmount);

    for (int i = 0; i < edgeAmount; i++)
    {
        cin >> originVertex;
        cin >> destinyVertex;
        cin >> weight;
        grafo->insertarArista(originVertex, destinyVertex, weight);
    }

    runKruskalAlgorithm(grafo->getListaAdyacencia(), vertexAmount);

    grafo->imprimir();

    return 0;
}