#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

struct MejorRuta{
    int indice;
    int nodos_infectados;
};

class Arista{

    public:
    int origen, destino;

    Arista(int origen, int destino){
        this->origen = origen;
        this->destino = destino;
    }
};

class Grafo{

    public:

    int vertices, tiempo;
    vector<int> gradoIncidencia;
    vector<vector<int>> listaAdyacencia;

    Grafo(int vertices, int tiempo){
        this->vertices = vertices;
        this->tiempo = tiempo;

        listaAdyacencia.resize(vertices);
        gradoIncidencia.assign(vertices, 0);
    }

    ~Grafo(){}

    void añadirArista(Arista* arista){
        listaAdyacencia[arista->origen].push_back(arista->destino);
        gradoIncidencia[arista->destino]++;
    }

    void propagacionVirus(){
        vector<int> numeroNodosInfectados;
        vector<int> nodosInfectados;
        vector<int> nodosMarcados;
        vector<int> nodosAdyacente;

        for (int i = 0; i < vertices; i++){
            nodosMarcados.push_back(i);
            for (int j = 0; j < tiempo; j++){
                agregarAdyacencias(nodosAdyacente, nodosMarcados, nodosInfectados);
                moverNodosDeVectores(nodosAdyacente, nodosMarcados, nodosInfectados);
            }

            numeroNodosInfectados.push_back(nodosInfectados.size());
            nodosAdyacente.clear();
            nodosMarcados.clear();
            nodosInfectados.clear();
        }

        mayoresNumeros(numeroNodosInfectados);
    }

    void agregarAdyacencias(vector<int> &nodosAdyacente, vector<int> &nodosMarcados, vector<int> nodosInfectados){
        for(int i = 0; i < nodosMarcados.size(); i++){
            for(int j = 0; j < listaAdyacencia[nodosMarcados[i]].size(); j++){
                if(presenteEnVector(nodosAdyacente, listaAdyacencia[nodosMarcados[i]][j]) && presenteEnVector(nodosMarcados, listaAdyacencia[nodosMarcados[i]][j]) && presenteEnVector(nodosInfectados, listaAdyacencia[nodosMarcados[i]][j])){
                    nodosAdyacente.push_back(listaAdyacencia[nodosMarcados[i]][j]);
                }
            }
        }
    }

    bool presenteEnVector(vector<int> vector, int nodo){
        for(int i = 0; i < vector.size(); i++){
            if(vector[i] == nodo){
                return false;
            }
        }

        return true;
    }

    void moverNodosDeVectores(vector<int> &nodosAdyacente, vector<int> &nodosMarcados, vector<int> &nodosInfectados){
        while(!nodosMarcados.empty()){
            nodosInfectados.push_back(nodosMarcados.back());
            nodosMarcados.pop_back();
        }

        while(!nodosAdyacente.empty()){
            nodosMarcados.push_back(nodosAdyacente.back());
            nodosAdyacente.pop_back();
        }
    }

    void mayoresNumeros(vector<int> numeroNodosInfectados){
        int mayor = numeroNodosInfectados[0];
        MejorRuta ruta;
        vector<MejorRuta> mejoresRutas;

        for(int i = 1; i < numeroNodosInfectados.size(); i++){
            if(mayor < numeroNodosInfectados[i]){
                mayor = numeroNodosInfectados[i];
            }
        }

        for(int i = 0; i < numeroNodosInfectados.size(); i++){
            if(mayor == numeroNodosInfectados[i]){
                ruta.indice = i;
                ruta.nodos_infectados = numeroNodosInfectados[i];

                mejoresRutas.push_back(ruta);
            }
        }

        for(int i = 0; i < mejoresRutas.size(); i++){
            cout<<"Nodo inicial: "<<mejoresRutas[i].indice<<" Numero de nodos infectados: "<<mejoresRutas[i].nodos_infectados<<endl;
        }
    }

};

int main(){
    int n, e, t, x, y;
    string linea;
    vector<Arista> aristas;
    ifstream archivo;

    archivo.open("grafo3.txt", ios::in);

    do{

        archivo>>n>>e>>t;
        Grafo *grafo = new Grafo(n, t);

        for(int i = 0; i < e; i++){
            getline(archivo, linea);

            archivo>>x>>y;

            Arista* arista = new Arista(x, y);
        
            grafo->añadirArista(arista);
        }

        cout<<endl;
        cout<<"Nuevo Grafo: "<<endl;
        grafo->propagacionVirus();
        getline(archivo, linea);
        getline(archivo, linea);

        delete grafo;
    }while(linea == "//");

    return 0;
}