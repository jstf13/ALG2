#define TABLA_HASH_ABIERTA
#include <string>
#include <iostream>
using namespace std;

struct NodoLista
{
    string clave;
    int valor;
    NodoLista *sig;
    NodoLista(string unaClave, int unValor) : clave(unaClave), valor(unValor), sig(0){};
    NodoLista(string unaClave, int unValor, NodoLista *unSig) : clave(unaClave), valor(unValor), sig(unSig){};
};

class TablaHashCerrada

{
private:
    typedef NodoLista *List;
    List *tabla;
    int tam;

    float factorCarga()
    {
        return (float)this->numElem / this->tam;
    };

    bool insert(List *tabla, string clave, int valor, int pos)
    {
        if (tabla[pos] == NULL)
        {
            tabla[pos] = new NodoLista(clave, valor);
            return true;
        }
        else
        {
            if (tabla[pos]->clave == clave)
            {
                tabla[pos]->valor += valor;
                return false;
            }
            else
            {
                pos++;
                if (pos == this->tam || pos == this->tam * 2)
                    pos = 0;                
                return insert(tabla, clave, valor, pos);
            }
        }
    };

    bool deleteElem(string clave, List &list)
    {
        if (list == NULL)
        {
            return false;
        }
        else
        {
            if (list->clave == clave)
            {
                List aux = list;
                list = list->sig;
                delete aux;
                return true;
            }
            else
            {
                return deleteElem(clave, list->sig);
            }
        }
    };

    bool keyExists(string clave, NodoLista *list)
    {
        if (list == NULL)
        {
            return false;
        }
        else
        {
            if (list->clave == clave)
            {
                return true;
            }
            else
            {
                return keyExists(clave, list->sig);
            }
        }
    };

    bool getKey(string clave, List list)
    {
        if (list == NULL)
        {
            return false;
        }
        else
        {
            if (list->clave == clave && list->valor > 0)
            {
                list->valor--;
                return true;
            }
            else
            {
                return getKey(clave, list->sig);
            }
        }
    };

    int funcionHash(string clave, int miTam)
    {
        int suma = 0;
        for (int i = 0; i < clave.length(); i++)
        {
            suma = 31 * suma + int(clave[i]);
        }
        return suma;
    };

public:
    int numElem;
    TablaHashCerrada(int unTam)
    {
        this->tam = unTam;
        this->tabla = new List[this->tam];
        for (int i = 0; i < this->tam; i++)
        {
           this->tabla[i] = NULL;
        }
        numElem = 0;
    };

    void rehash()
    {
        List *nuevaTabla = new List[tam * 2];
        for (int i = 0; i < tam * 2; i++)
        {
            nuevaTabla[i] = NULL;
        }

        for (int i = 0; i < tam; i++)
        {
            List list = tabla[i];
            if(list != NULL)
            {
                insert(nuevaTabla, list->clave, list->valor, funcionHash(list->clave, (tam * 2)));
            }
        }
        tabla = nuevaTabla;
        tam = tam * 2;
    };    

    void insertar(string clave, int valor)
    {
        int pos = abs(funcionHash(clave, tam)) % tam;
        if (insert(tabla, clave, valor, pos))
        {
            numElem++;
            if (factorCarga() > 0.5)
            {
                rehash();
            }
        }
    };

    void deleteElem(string clave)
    {
        int pos = abs(funcionHash(clave, tam)) % tam;
        if (deleteElem(clave, tabla[pos]))
        {
            numElem--;
        }
    };

    bool existe(string clave)
    {
        int pos = abs(funcionHash(clave, tam)) % tam;
        clave = toupper(clave[0]);
        
        return keyExists(clave, tabla[pos]);
    };

    bool getKey(string clave)
    {
        int pos = abs(funcionHash(clave, tam)) % tam;
        return getKey(clave, tabla[pos]);
    };

    void imprimir()
    {
        for (int i = 0; i < tam; i++)
        {
            cout << i << ": ";
            NodoLista *list = tabla[i];
            while (list != NULL)
            {
                cout << list->clave << " ";
                cout << list->valor << " ";
                list = list->sig;
            }
            cout << endl;
        }
    };
};


int main()
{
    int users;
    string email;

    cin >> users;

    TablaHashCerrada tabla(users * 2);

    while (users > 0)
    {
        cin >> email;
        tabla.insertar(email, 1);
        users--;
    }
    
    cout << tabla.numElem << endl;

    return 0;
}
