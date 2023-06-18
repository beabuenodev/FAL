//Beatriz Bueno Almagro E09

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/*
* Arbol de exploracion
* El arbol de exploracion de este algoritmo de vuelta atrás tiene como raíces n funcionarios, y cada uno bifurca en n - 1 funcionarios
* restantes para completar la solución, y así sucesivamente. La solución tiene un total de n nodos
* 
* Explicación de Poda
* se implementa un vector mintrabajo que aloja el minimo de tiempo sea el funcionario que sea y
* por cada funcion parcial sumamos todos los tiempos (de mintrabajo) que nos quedan, y si es mayor que la mejorsol
* cortamos esa rama ya que nunca llegaremos a una suma menor.
*/

bool esValida(const int i, vector<int> const& marcas) {
    return marcas[i] <= 1;
}

bool esSolucion(const int n, const int k) {
    return n == k + 1;
}

bool esMejor(const int suma, const int mejorsuma) {
    return mejorsuma == -1 || suma < mejorsuma;
}

bool esCompletable(const int k, const int n) {
    return k < n - 1;
}

bool esPrometedor(const int suma, const int mejorsuma, const int auxmin) {
    int aux = suma + auxmin;
    return mejorsuma == -1 || aux < mejorsuma;
}

void funcionarios(vector<vector<int>> const& mat, const int n, vector<int>& sol, int& suma, vector<int>& mejorsol, int& mejorsuma, int k, vector<int>& marcas, vector<int> const& mintrabajo, int& auxmin) {
    for (int i = 0; i < n; i++) {
        sol[k] = i;
        marcas[i]++;
        suma += mat[i][k]; 
        auxmin -= mintrabajo[k];
        if (esValida(i, marcas)) {
            if (esSolucion(n, k)) {
                if (esMejor(suma, mejorsuma)) {
                    mejorsol = sol;
                    mejorsuma = suma;
                }
            }
            else if (esCompletable(k, n) && esPrometedor(suma, mejorsuma, auxmin)) {
                funcionarios(mat, n, sol, suma, mejorsol, mejorsuma, k + 1, marcas, mintrabajo, auxmin);
            }
        }
        marcas[i]--;
        suma -= mat[i][k];
        auxmin += mintrabajo[k];
    }
}

int funcionarios(vector<vector<int>> const& mat, const int n) {
    vector<int> sol(n), mejorsol(n), mintrabajo(n, -1);
    int suma = 0, mejorsuma = -1;
    vector<int> marcas(n, 0);
    int auxmin = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mintrabajo[j] == -1 || mat[i][j] < mintrabajo[j]) {
                if (mat[i][j] < mintrabajo[j])
                    auxmin -= mintrabajo[j];
                auxmin += mat[i][j];
                mintrabajo[j] = mat[i][j];
            }
        }
    }
    funcionarios(mat, n, sol, suma, mejorsol, mejorsuma, 0, marcas, mintrabajo, auxmin);
    return mejorsuma;
}

bool resuelveCaso() {
    //Leer caso de prueba: cin>>...
    int n;
    cin >> n;
    if (n == 0)
        return false;
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    //Resolver problema
    int sol = funcionarios(mat, n);
    //Escribir resultado
    cout << sol << "\n";
    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}