/*
    El problema es mucho texto, pero básicamente te dan las aristas de 
    un grafo (con sus nodos) para que lo construyas, y tienes que decir
    si es un arbol o no.

    Un arbol es cualquier grafo conectado y sin ciclos, osea:
        4
       / \
      2  5
        / \     Si es un arbol
       3  1
       |
       0

       3 - 0
      / \ /     No es un arbol
     2   1

    Lee primero los comentarios de aqui abajito, luego de main(), luego de tree()
    y al final de ciclo() para entenderle bien
*/

//cositas
#include <bits/stdc++.h>
using namespace std;
#define _ cin.tie(nullptr); ios_base::sync_with_stdio(false);
typedef long long lli;

//Los grafos normalmente se manejan como una lista de adyacencia
//osea, las conexiones que hay entre los vertices
list<lli> *graph;

bool ciclo(lli actual, bool visit[], lli past){
    //Marcas el vertice actual como visitado
	visit[actual] = true;
	list<lli>::iterator it;
    //Recorres el resto de la rama
	for(it = graph[actual].begin(); it != graph[actual].end(); it++){
        //Si no has visitado el que sigue, vuelves a llamar a la
        //funcion y checas a partir de ahi. Eventualmente llegas
        //al final de la rama (osea no hay ciclo) o regresas a un
        //vertice por el que ya pasaste (si hay ciclo)
		if(!visit[*it]){
		    if(ciclo(*it, visit, actual)) return true;
		}
		else if(*it != past) return true;
	}
    //Si completaste el for() sin activar ninguno de los ifs, es que
    //llegaste al final de la rama y no pasaste por un vertice ya 
    //visitado
	return false;
}

bool tree(lli n){
    //Un arreglo de bools para contar los vertices por los que has
    //pasado, se inicializa todo en falso
	bool *visited = new bool[n];
	for(lli i = 0; i < n; i++){
		visited[i] = false;
    }

    //ciclo() checa si hay ciclos (xd), pero es una funcion recursiva:
    //Basicamente, comenzamos por la raiz (el vertice -1) y vas recorriendo
    //todo el grafo en orden
	if(ciclo(0, visited, -1)) return false;

    //Si no hay ciclos, checas el arreglo para ver si efectivamente ya
    //pasaste por todos los vertices, si no, significa que el grafo
    //no es conectado
	for(lli i = 0; i < n; i++){
		if(!visited[i]) return false;
    }
	return true;
}


int main(){_
	lli n; cin >> n;

    //Esta es otra forma de inicializar la lista porque tiene que ser global. La 
    //declaras afuera de main pero la defines adentro, basicamente.
    //(se usa en otras funciones y es mas sencillo así que pasarlo por parámetros)
    graph = new list<lli>[n];
    
    //El problema te da los vertices como un numero random, pero este
    //algoritmo necesita que esten numerados de 0 hacia arriba, entonces
    //el mapa (cosa) sirve para asignar esos valores
    map<lli, lli> cosa;
    lli cont = 0;
    for(lli i = 0; i < n-1; i++){
        lli a, b; cin >> a >> b;
        //Si el valor ya existe en el mapa, le asignas lo que tengas guardado, si
        //no, lo agregas como una nueva entrada y aumentas el valor para el
        //siguiente
        if(cosa.find(a) == cosa.end()){
            cosa[a] = cont;
            cont++;
        }
        if(cosa.find(b) == cosa.end()){
            cosa[b] = cont;
            cont++;
        }

        //Ya que estan redefinidos los vertices, se agregan a la lista
        //de adyacencia. Aqui es como decir que el vertice [0] esta conectado
        //al [1], y aparte el [1] al [0], porque esto es un grafo no dirigido
        graph[cosa[a]].push_back(cosa[b]);
        graph[cosa[b]].push_back(cosa[a]);
    }

    //tree() es un bool que dice si cumple o no ser arbol
	if(tree(n)) cout << "Hemos sido bendecidos\n";
    else cout << "Que esta maldicion sea rapida\n";
	return 0;
}
