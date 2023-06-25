// Sofía Boudere E07 y Beatriz Bueno Almagro E09

// Comentario general sobre la solucion,
// explicando como se resuelve el problema

// Definicion del espacio de soluciones y del arbol de exploracion

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// IMPLEMENTACION DEL ALGORITMO DE VUELTA ATRAS
// Explicaciones detalladas sobre la implementacion
// Indicacion de los marcadores utilizados
/*
* Descripcion espacio de soluciones
* Nuestro espacio de soluciones es un arbol con ramificaciones en el caso de que se sume o se reste el siguiente
* elemento.
*		1
*	 + / \ -
*	  3   3
*    / \  / \
*	(...) (...)
*
* El tamaño del arbol es el tamaño del vector
*/

// PODA UTILIZADA
/* Usamos un parametro que tenga las sumas totales del vector, siempre que miremos si es valido miramos si es prometedor, le sumamos y restamos
* esa suma total (a la que le restamos los elementos que vamos añadiendo), si no se acerca a m, podamos esa rama
*/

bool esSolucion(vector<int> const& v, const int m, const int k, const int suma) {
	if (k == v.size() - 1 && suma == m)
		return true;
	return false;
}

bool esValido(vector<int> const& v, const int m, const int k, const int suma) {
	if (k < v.size())
		return true;
	else return false;
}

bool esPrometedor(vector<int> const& v, const int m, const int k, const int suma, const int sumatotal) {
	if (suma + sumatotal < m || suma - sumatotal > m)
		return false;
	else return true;

}

void vueltaAtras(vector<int> const& v, int m, int k, int& suma, bool& essol, int& sumatotal) {
	if (k < v.size()) {
		if (suma + sumatotal >= m) {
			suma += v[k];
			sumatotal -= v[k];
			if (esSolucion(v, m, k, suma)) {
				essol = true;
				return;
			}
			else
				vueltaAtras(v, m, k + 1, suma, essol, sumatotal);
			suma -= v[k];
			sumatotal += v[k];
		}
		if (suma - sumatotal <= m) {
			suma += -v[k];
			sumatotal -= v[k];
			if (esSolucion(v, m, k, suma)) {
				essol = true;
				return;
			}
			else 
				vueltaAtras(v, m, k + 1, suma, essol, sumatotal);
			suma += v[k];
			sumatotal += v[k];
		}
	}
}

int sumaTotal(vector<int> const& v) {
	int suma = 0;
	for (int i = 0; i < v.size(); i++) {
		suma += v[i];
	}
	return suma;
}

void vueltaAtras(vector<int> const v, int m, bool& essol) {
	if (v.size() == 1) {
		if (v[0] == m)
			essol = true;
		return;
	}
	else if (v.size() == 0) {
		if (m == 0)
			essol = true;
		return;
	}
	int k = 1, suma = v[0];
	int sumatotal = sumaTotal(v);
	vueltaAtras(v, m, k, suma, essol, sumatotal);
	return;
}



void resuelveCaso() {
	int numElems = 0; size_t n; int m;
	std::cin >> m >> numElems;
	std::vector<int> v(numElems);
	for (int& i : v) std::cin >> i;
	bool b = false;

	//LLAMAR AQUI AL ALGORITMO DE VUELTA ATRAS
	vueltaAtras(v, m, b);

	if (b)
		std::cout << "SI" << "\n";
	else
		std::cout << "NO" << "\n";
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("sample3.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resuelveCaso();



#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}