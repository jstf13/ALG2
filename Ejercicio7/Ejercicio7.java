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

    public int maximaSuma(int s1, int s2, int s3) {
        int maximo = 0;
        
        if (s1 > s2 && s1 > s3) 
        {
            maximo = s1;
        }

        if (s2 > s1 && s2 > s3) 
        {
            maximo = s2;
        }

        if (s3 > s1 && s3 > s2) 
        {
            maximo = s3;
        }

        return maximo;
    }

    public int maximaSumatoriaEnComun(Cola c1, Cola c2, Cola c3, int sumaC1, int sumaC2, int sumaC3) 
    {
        int maximaSuma = maximaSuma(sumaC1, sumaC2, sumaC3);
        int minimoC1;
        int minimoC2;
        int minimoC3;
        boolean encontreMaximoComun = false; 

        if (maximaSuma == sumaC1 && maximaSuma == sumaC2 && maximaSuma == sumaC3) 
        {
            encontreMaximoComun = true;
            return maximaSuma;
        }
        else 
        {
            if (!c1.esVacia() && !c2.esVacia() && !c3.esVacia() && !encontreMaximoComun) 
            {
                if (maximaSuma == sumaC1) 
                {
                    minimoC1 = c1.obtenerMenor();
                    c1.eliminarMenor();
                    sumaC1 -= minimoC1;
                    maximaSuma = maximaSuma(sumaC1, sumaC2, sumaC3);
                    return maximaSumatoriaEnComun(c1, c2, c3, sumaC1, sumaC2, sumaC3);
                }
                else {
                    if (maximaSuma == sumaC2) 
                    {
                        minimoC2 = c2.obtenerMenor();
                        c2.eliminarMenor();
                        sumaC2 -= minimoC2;
                        maximaSuma = maximaSuma(sumaC1, sumaC2, sumaC3);
                        return maximaSumatoriaEnComun(c1, c2, c3, sumaC1, sumaC2, sumaC3);
                    }
                    else {
                        if (maximaSuma == sumaC3) 
                        {
                            minimoC3 = c3.obtenerMenor();
                            c3.eliminarMenor();
                            sumaC3 -= minimoC3;
                            maximaSuma = maximaSuma(sumaC1, sumaC2, sumaC3);
                            return maximaSumatoriaEnComun(c1, c2, c3, sumaC1, sumaC2, sumaC3);
                        }
                    }
                }
            }
        }
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

        int sumaComun = c1.obtenerMaximaSumaEnComun(c1, c2, c3, sumaC1, sumaC2, sumaC3);
        System.out.println(sumaComun);
    }
}