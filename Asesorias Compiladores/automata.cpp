#include <iostream> // entrada / salida
#include <utility>  // agregar los pair
#include <vector>   // agrega las lista

using namespace std;

// Recuerden una pareja guarda dos valores pair<tipo1, tipo2>
// pareja.first  obtiene el primer  valor
// pareja.second obtiene el segundo valor


// Representación del automata como un grafo(arreglo de listas de parejas)
vector<vector<pair<int, char>>> grafo(1000, vector<pair<int, char>>());


// Agrega una transición al automata
void agregar(int u, int v, char c) {
  grafo[u].push_back({v, c});
}

// cadena a validar
string cadena;

// marca como true a los estados finales o de aceptación
vector<bool> aceptacion(1000, false);
// vector auxiliar para imprimir el camino recorrido
vector<pair<int, char>> nodos;
// estado inicial
int inicial;


// Algoritmo de búsqueda
// parametros nodo actual, índice del caracter que estamos procesando.
void busqueda(int nodo, int idx) {
  // Se ejecuta cuando no hay más caracteres que procesar y
  // el nodo actual es un estado de aceptación
  if (idx == cadena.size() && aceptacion[nodo]) {
     cout << inicial;
     for (auto n: nodos)
       cout << " -> " << n.first << " " << n.second;
     cout << endl;
  }
  // itera sobre todos los vecinos del nodo
  for (auto v: grafo[nodo]) {
    // Transición con epsilon
    if (v.second == 'E') {
      nodos.push_back({v.first, v.second});
      busqueda(v.first, idx);
      nodos.pop_back();
    }
    if (idx <= cadena.size() && cadena[idx] == v.second) {
      nodos.push_back({v.first, v.second});
      busqueda(v.first, idx + 1);
      nodos.pop_back();
    }
  }
}

int main() {
  inicial = 0;
  cadena = "abab";
  agregar(0, 0, 'a');
  agregar(0, 0, 'b');
  agregar(0, 1, 'a');
  agregar(1, 2, 'b');
  aceptacion[2] = true;
  busqueda(inicial, 0);
  return 0;
}
