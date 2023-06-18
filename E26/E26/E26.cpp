//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct tSolucion {
    int prod;
    bool sol;
};

tSolucion resolver(vector<vector<int>> const& m, int inifila, int finfila, int inicol, int fincol) {
    int prod1 = 1, prod2 = 1;

    if (inifila == finfila - 1) {
        return { m[0][0] , true };
    }
    else {

        for (int i = inifila, j = inicol; i < finfila && j < fincol; i++, j++) {
            prod1 *= m[i][j];
        }

        for (int i = inifila, j = fincol - 1; i < finfila && j >= inicol; i++, j--) {
            prod2 *= m[i][j];
        }

        //CB
        if (prod1 != prod2) //si los prod de diagonales no son iguales:
            return { -1, false };
        else {
            int fila_med = (inifila + finfila) / 2;
            int col_med = (inicol + fincol) / 2;
            tSolucion sol1 = resolver(m, inifila, fila_med, inicol, col_med);
            tSolucion sol2 = resolver(m, fila_med, finfila, inicol, col_med);
            tSolucion sol3 = resolver(m, inifila, fila_med, col_med, fincol);
            tSolucion sol4 = resolver(m, fila_med, finfila, col_med, fincol);
            bool essol = (sol1.sol && sol2.sol && sol3.sol && sol4.sol);
            return { prod1, essol };
        }
    }
}

tSolucion resolver(vector<vector<int>> const& m, const int n) {
    if (m.size() == 0)
        return { 0,false };
    return resolver(m, 0, n, 0, n);
}

void resuelveCaso() {
    //resuelve aqui tu caso
    int n;
    //Lee los datos
    cin >> n;
    vector<vector<int>> m(n, vector<int> (n));
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