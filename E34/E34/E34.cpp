//Beatriz Bueno Almagro E09

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
* Arbol de exploracion
* El arbol de exploracion de este algoritmo de vuelta atrás tiene como raíces m caminos, y cada uno bifurca en m - 1 caminos
* restantes para completar la solución, y así sucesivamente. La solución tiene un total de n nodos, uno por cada quitanieves
* 
* Marcaje
* El vector de marcas tiene como tamaño m caminos e indica los caminos ya utilizados, ya que solo se puede usar uno
* por camino
*/

bool esValida(const int i, const int k, vector<bool> const& marcas, const vector<int>carros, const vector<int>caminos) {
    return !marcas[i] && carros[k] <= caminos[i];
}

bool esSolucion(const int k, const int n) {
    return k == n - 1;
}

bool esMejor(const int suma, const int mejorsuma) {
    return suma > mejorsuma;
}

void vueltaAtras(const int n, const int m, const vector<int> carros, const vector<int> caminos, const vector<vector<int>> calidades,
    vector<int>& sol, int& suma, int& mejorsuma, vector <bool>& marcas, int k) { //k indica el nodo en el que estamos, por lo que es el quitanieves. entonces i debe ser el camino
    if (k == n) {
        if (suma > mejorsuma)
            mejorsuma = suma;
    }
    else {
        for (int i = 0; i < m; i++) { //!ultimohijonivel(k) - recorremos los caminos
            sol[k] = i; //a la maquina k le asignamos el camino i
            suma += calidades[k][i]; //actualizamos la suma con la calidad actual
            if (esValida(i, k, marcas, carros, caminos)) {
                if (esSolucion(k, n)) {
                    if (esMejor(suma, mejorsuma)) {
                        mejorsuma = suma;
                    }
                }
                else {
                    marcas[i] = true;
                    vueltaAtras(n, m, carros, caminos, calidades, sol, suma, mejorsuma, marcas, k + 1);
                    marcas[i] = false;
                }
            }
            suma -= calidades[k][i];
        }
        //Al carro no se le incluye ningun camino
        vueltaAtras(n, m, carros, caminos, calidades, sol, suma, mejorsuma, marcas, k + 1);
    }
    
}

int resolver(const int n, const int m, const vector<int> carros, const vector<int> caminos, const vector<vector<int>> calidades) {
    if (n == 0) {
        return 0;
    }
    vector<int> solv(n);
    vector<bool> marcas(m, false);
    int sol = -1, suma = 0;
    vueltaAtras(n, m, carros, caminos, calidades, solv, suma, sol, marcas, 0);
    return sol;
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n, m, aux;
    cin >> n >> m;
    vector <int> carros, caminos;
    vector <vector<int>> calidades(n,  vector<int>(m));
    for (int i = 0; i < n; i++) {
        cin >> aux;
        carros.push_back(aux);
    }
    for (int i = 0; i < m; i++) {
        cin >> aux;
        caminos.push_back(aux);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> calidades[i][j];
        }
    }
    //Calcula el resultado
    cout << resolver(n, m, carros, caminos, calidades)<< '\n'; 
    //Escribe el resultado
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}