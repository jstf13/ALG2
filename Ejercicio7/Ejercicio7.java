import java.util.Scanner;

abstract class Cola {
    abstract void insertar(int elemento);
    abstract void desencolar();
    abstract int tope();
    abstract boolean esVacia();
    abstract boolean estaLlena();
    abstract int obtenerMaximaSumaEnComun(Cola c1, Cola c2, Cola c3, int sumaC1, int sumaC2, int sumaC3);
};

class NodoLista {
    public NodoLista sig;
    public NodoLista ant;
    public int dato;
    public NodoLista() {};
    public NodoLista(int unDato, NodoLista unSig, NodoLista unAnt) {
        dato = unDato;
        sig = unSig;
        ant = unAnt;
    };
    public NodoLista(int unDato) {
        dato = unDato;
        sig = null;
        ant = null;
    };
};

class Lista {
    private NodoLista ppio;

    public Lista() { ppio = null; }

    public void insertar(int dato) {
        NodoLista nuevoNodo =  new NodoLista(dato, this.ppio, null);
        if(this.ppio != null) {
            this.ppio.ant = nuevoNodo;
        }
        ppio = nuevoNodo;
    }

    public int obtenerMenor() {
		if(esVacia())
			throw new Error("La lista esta vacia");
        NodoLista menor = this.ppio;
        NodoLista aux = this.ppio;
        while(aux != null) {
            if(menor.dato > aux.dato) {
                menor = aux;
            }
            aux = aux.sig;
        }
        return menor.dato;
    }

    public void eliminarMenor() {
		if(esVacia())
			throw new Error("La lista esta vacia");
        NodoLista menor = this.ppio;
        NodoLista aux = this.ppio;
        while(aux != null) {
            if(menor.dato > aux.dato) {
                menor = aux;
            }
            aux = aux.sig;
        }

        // elimino el nodo que contiene el menor dato
        if(menor.ant != null) {
            menor.ant.sig = menor.sig;
        }else {
            ppio = menor.sig;
        }
        if(menor.sig != null) {
            menor.sig.ant = menor.ant;
        }
    }

    public boolean esVacia() {
        return ppio == null;
    }

    public int maximaSumatoriaEnComun(Cola c1, Cola c2, Cola c3, int sumaC1, int sumaC2, int sumaC3) 
    {
        
        return 0;
    }
};

class ColaImpLista extends Cola {
    private Lista miLista;

    public ColaImpLista() {
        miLista = new Lista();
    }
    public void insertar(int el) {
        miLista.insertar(el);
    }
    public void desencolar() {
        miLista.eliminarMenor();
    }
    public int tope() {
		return miLista.obtenerMenor();
	}
    public boolean esVacia() {
        return miLista.esVacia();
    }
    public boolean estaLlena() {
        return false;
    }
    public int obtenerMaximaSumaEnComun(Cola c1, Cola c2, Cola c3, int sumaC1, int sumaC2, int sumaC3) {
		return miLista.maximaSumatoriaEnComun(c1, c2, c3, sumaC1, sumaC2, sumaC3);
	}
};

public class Ejercicio7 {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);
        
        Cola c1 = new ColaImpLista();
		Cola c2 = new ColaImpLista();
        Cola c3 = new ColaImpLista();

        int elemento;
        int sumaC1 = 0;
        int largoC1 = entrada.nextInt();
        for (int i = 0; i < largoC1; i++)
        {
            elemento = entrada.nextInt();
			c1.insertar(elemento);
            sumaC1 += elemento;
        }

        int sumaC2 = 0;
        int largoC2 = entrada.nextInt();
        for (int i = 0; i < largoC2; i++)
        {
            elemento = entrada.nextInt();
			c2.insertar(elemento);
            sumaC2 += elemento;
        }

        int sumaC3 = 0;
        int largoC3 = entrada.nextInt();
        for (int i = 0; i < largoC3; i++)
        {
            elemento = entrada.nextInt();
			c3.insertar(elemento);
            sumaC3 += elemento;
        }

        /*
        System.out.println(sumaC1);
        System.out.println(sumaC2);
        System.out.println(sumaC3);
        */

        int sumaComun = obtenerMaximaSumaEnComun(c1, c2, c3, sumaC1, sumaC2, sumaC3);
        System.out.println(sumaComun);
    }
}