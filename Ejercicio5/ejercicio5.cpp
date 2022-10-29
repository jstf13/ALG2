#include <cstdlib>
#include <iostream>
#include <cassert>

using namespace std;

struct Nodo{
    int vertice;
    int gradoDeEntrada;
    Nodo (int v, int g) : vertice(v), gradoDeEntrada(g) {}
    Nodo () : vertice(0), gradoDeEntrada(0) {}
};

class Max_Heap
{
private:
    Nodo *heap;
    int posicionTope;
    int tam;

    int izquierda(int i)
    {
        return 2 * i;
    }

    int derecha(int i)
    {
        return 2 * i + 1;
    }

    int padre(int i)
    {
        return i / 2;
    }

    void swap(int i, int j)
    {
        Nodo temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void flotar(int i)
    {
        while (i > 1 && heap[padre(i)].gradoDeEntrada < heap[i].gradoDeEntrada)
        {
                swap(i, padre(i));
                i = padre(i);
        }
        while(i > 1 && heap[padre(i)].gradoDeEntrada == heap[i].gradoDeEntrada && heap[padre(i)].vertice < heap[i].vertice){
                swap(i, padre(i));
                i = padre(i);
        }
    }

    void hundir(int pos)
    {
        while (posicionTope > 1 && pos < posicionTope)
        {
            int izq = izquierda(pos);
            int der = derecha(pos);
            int max = pos;
            if (izq < posicionTope && heap[izq].gradoDeEntrada > heap[max].gradoDeEntrada)
                max = izq;
            else
            {
                if (izq < posicionTope && heap[izq].gradoDeEntrada == heap[max].gradoDeEntrada && heap[izq].vertice > heap[max].vertice)
                    max = izq;
            }
            if (der < posicionTope && heap[der].gradoDeEntrada > heap[max].gradoDeEntrada)
                max = der;
            else
            {
                if (der < posicionTope && heap[der].gradoDeEntrada == heap[max].gradoDeEntrada && heap[der].vertice > heap[max].vertice)
                    max = der;
            }
            if (max != pos)
            {
                swap(pos, max);
                pos = max;
            }
            else
                break;
        }
    }

public:
    Max_Heap(int tam)
    {
        this->tam = tam;
        posicionTope = 1;
        heap = new Nodo[tam+1];
    }

    Nodo tope()
    {
        return this->heap[1];
    }

    void insertar(Nodo nuevoNodo)
    {
        assert(posicionTope <= tam);
        heap[posicionTope] = nuevoNodo;
        flotar(posicionTope);
        posicionTope++;
    }

    void eliminarTope()
    {
        assert(posicionTope > 0);
        posicionTope--;
        swap(1, posicionTope);
        hundir(1);
    }

    void imprimir()
    {
        for (int i = 1; i < posicionTope; i++)
            cout << heap[i].vertice << " " << heap[i].gradoDeEntrada << endl;
        cout << endl;
    }

    bool estaVacio()
    {
        return this->posicionTope == 0;
    }

    bool estaLleno()
    {
        return this->posicionTope == this->tam;
    }
};

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


int main()
{
    int vertexAmount;
    int edgeAmount;

    int vertexStart;
    int vertexEnd;

    cin >> vertexAmount >> edgeAmount;

    Nodo *nodos = new Nodo[vertexAmount + 1];
    Max_Heap heap(vertexAmount);

    for (int i = 1; i <= vertexAmount; i++)
    {
        nodos[i] = Nodo(i, 0);
    }

    for (int i = 1; i <= edgeAmount; i++)
    {
        cin >> vertexStart >> vertexEnd;
        nodos[vertexEnd].gradoDeEntrada++;
    }

    for (int i = 1; i <= vertexAmount; i++)
    {
        heap.insertar(nodos[i]);
    }
    
    for(int i = 1; i <= vertexAmount; i++)
    {
        Nodo nodo = heap.tope();
        heap.eliminarTope();
        cout << nodo.vertice << " " << nodo.gradoDeEntrada << endl;
    }
    
    return 0;
} 