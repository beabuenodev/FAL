// NOMBRE Y APELLIDOS: Beatriz Bueno Almagro E09
// DNI: 

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

//DESCRIPCION DEL ESPACIO DE SOLUCIONES
/*
* El arbol de soluciones de este ejercicio tiene n + 1 nodos iniciales, n siendo el número de ciudades, y el +1 el caso en el que no se asigna a ninguna ciudad. 
* Cada nivel es una patrulla distinta, a la que le intentamos asignar una ciudad, o la dejamos en reserva. 
* 
* El espacio de búsqueda es este arbol en el que la solución es una tupla (x0, ..., xm - 1) siendo m el número de patrullas
*/

//MARCADORES UTILIZADOS
/*
* Los marcadores empleados para mejorar la eficiencia de las funciones son: un contador de ciudades ya completas (cumplen el min de soldados indicado) y un vector
* de los soldados que hay por ciudad
*/
//PODA DE OPTIMALIDAD
/*
* Si en una sol parcial, el salario actual mas el salario minimo * el numero de soldados restantes es mayor que el salario mejor, nunca se llegaría a una solucion mejor
* por esa rama, y por lo tanto podemos podarla
*/


//ALGORITMO DE VUELTA ATRÁS

bool esValida(vector<int> const& soldados_ciudad, vector<int> const& G, const int i) {
	return soldados_ciudad[i] <= G[i];
}

bool ciudadCompleta(vector<int> const& soldados_ciudad, vector<int> const& G, vector<int> const& L, vector<int> const& P, const int i, const int k) {
	return soldados_ciudad[i] >= L[i] && soldados_ciudad[i] - P[k] < L[i]; 
}

bool esSolucion(const int k, const int m) {
	return k == m - 1;
}

bool esPrometedor(const int suma, const int mejorsuma, const int salariomin, const int soldados_restantes, const int k, vector<int> const& P, vector<int> const& L) {
	return suma + salariomin * (soldados_restantes - P[k]) < mejorsuma;
}

void vueltaAtras(const int n, const int m, const int r, vector<int> const& L, vector<int> const& G, vector<int> const& S, vector<int> const& P, int& suma, int& mejorsuma,
	int& c_completas, vector<int>& soldados_ciudad, int& salariomin, int& soldados_restantes, int k) {
	for (int i = 0; i < n; i++) {
		soldados_ciudad[i] += P[k];
		suma += (S[i] * P[k]);
		if (esValida(soldados_ciudad, G, i)) {
			if (ciudadCompleta(soldados_ciudad, G, L, P, i, k)) {
				c_completas++;
			}
			if (esSolucion(k, m)) {
				if (n == c_completas && suma < mejorsuma) {
					mejorsuma = suma;
				}
			}
			else if (esPrometedor(suma, mejorsuma, salariomin, soldados_restantes, k, P, L)) {
				soldados_restantes -= P[k];
				vueltaAtras(n, m, r, L, G, S, P, suma, mejorsuma, c_completas, soldados_ciudad, salariomin, soldados_restantes, k + 1);
			}
			if (ciudadCompleta(soldados_ciudad, G, L, P, i, k)) {
				c_completas--;
			}
		}
		soldados_ciudad[i] -= P[k];
		suma -= (S[i] * P[k]);
	}

	suma += r * P[k];
	if (esSolucion(k, m)) {
		if (n == c_completas && suma < mejorsuma) {
			mejorsuma = suma;
		}
	}
	else {
		if (esPrometedor(suma, mejorsuma, salariomin, soldados_restantes, k, P, L)) {
			soldados_restantes -= P[k];
			vueltaAtras(n, m, r, L, G, S, P, suma, mejorsuma, c_completas, soldados_ciudad, salariomin, soldados_restantes, k + 1);
		}
	}
	suma -= r * P[k];
}

int vueltaAtras(const int n, const int m, const int r, vector<int> const& L, vector<int> const& G, vector<int> const& S, vector<int> const& P) {
	int salariomin = INT_MAX, soldados_restantes = 0, mejorsuma = INT_MAX, suma = 0, c_completas = 0;
	vector<int> soldados_ciudad(n, 0);
	for (int i = 0; i < n; i++) {
		salariomin = min(salariomin, min(S[i], r));
	}
	for (int i = 0; i < m; i++) {
		soldados_restantes += P[i];
	}
	vueltaAtras(n, m, r, L, G, S, P, suma, mejorsuma, c_completas, soldados_ciudad, salariomin, soldados_restantes, 0);
	return mejorsuma;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta
void resuelveCaso() {
	int n, m, r; //ciudades, patrullas y sueldo de reserva
	cin >> n >> m >> r;
	vector<int> L(n), G(n), S(n); //minimo, maximo de personas admitidas en la ciudad y salarios por ciudad
	vector<int> P(m); //personas por patrulla

	for (int i = 0; i < n; ++i)
		cin >> L[i];
	for (int i = 0; i < n; ++i)
		cin >> G[i];
	for (int i = 0; i < n; ++i)
		cin >> S[i];
	for (int i = 0; i < m; ++i)
		cin >> P[i];

	int salarioMejor; bool sepuede = false;

	//LLamada inicial al algoritmo de vuelta atras
	salarioMejor = vueltaAtras(n, m, r, L, G, S, P);
	if (salarioMejor != INT_MAX)
		sepuede = true;

	if (sepuede)
		cout << salarioMejor << "\n";
	else
		cout << "NO\n";
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


	// Para restablecer entrada. Comentar para acepta el reto

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}