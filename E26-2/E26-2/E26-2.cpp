//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool resorver(vector<vector<int>> const& v, int dim, int& d, int fila_ini, int fila_fin, int col_ini, int col_fin) {
    if (dim == 2) {
        if (v[fila_ini][col_ini] * v[fila_fin][col_fin] == v[fila_fin][col_ini] * v[fila_ini][col_fin]) {
            d *= v[fila_ini][col_ini] * v[fila_fin][col_fin];
            return true;
        }
        else return false;
    }
    else {

    }
}

void resuelveCaso() {
    //resuelve aqui tu caso
    int n;
    //Lee los datos
    cin >> n;
    vector<vector<int>> m(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }
    //Calcula el resultado
    tSolucion sol = resolver(m, n);
    //Escribe el resultado
    if (sol.sol)
        cout << "SI " << sol.prod;
    else
        cout << "NO";
    cout << "\n";
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
