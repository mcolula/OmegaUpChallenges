#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int inicial, u, v, n;
char coma, sim;

int main() {
  
  ifstream fi("datos.txt"); // Abre un archivo de texto
  string linea = "";        // Auxiliar para leer linea por linea
  
  getline(fi, linea); // Quitamos la primera linea, no la usamos
  getline(fi, linea); // Quitamos la segunda linea, no la usamos
  
  
  getline(fi, linea);       // Leemos la linea del estado inicial
  stringstream s1(linea);   // cargamos la linea
  s1 >> inicial;            // leemos el estado inicial
  
  getline(fi, linea);       // Leemos la linea de los estados finales
  stringstream s2(linea);   // cargamos la linea
  while (s2 >> n) {         // lee hasta que se acaba la linea
    cout << n << " ";
    aceptacion[n] = true;   // marcamos estados de aceptación
    s2 >> coma;             // se traga la coma
  }
 
  // Lee las transiciones hasta el fin del archivo
  while (fi >> u >> coma >> sim >> coma >> v)
    agregar(u, v, sim); 

  return 0;
}
