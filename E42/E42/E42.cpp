//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/*
* Este ejercicio está resuelto por Vuelta Atrás
*  - ARBOL EXPLORACIÓN
*       El arbol de exploración tiene como solución una tupla de pares {((x00, x01), ...,  (xn-1,0 , xn-1,1)}, donde n = numero de modelos
*       y forall k: o <= k < n : (xk = sol[k] = (tk, zk) = conjunto que tiene el modelo k) 
*  - MARCADORES
*       marcasT: forall i : 0 <= i < n : marcasT[i] = true si se ha usado, false en caso contrario
*       marcasZ: forall i : 0 <= i < n : marcasT[i] = true si se ha usado, false en caso contrario
*  - EXPLICACION PODAS
*       Para mejorar el coste asintótico se usa la siguiente función de poda:
*       Usamos un vector<int> prefmax de tamaño n (numero de modelos) y en el que se guarda el máximo de preferencia alcanzable para cada
*       modelo. También se emplea un int prefalcanzable, que se actualiza restando los modelos ya establecidos. Si en un punto de la sol
*       parcial la suma mas prefalcanzable es menor que la mejorsuma actual, entonces es imposible superarla, podemos podar esa rama.
*/

bool esValida(const int i, const int j, vector<bool> const& marcasT, vector<bool> const& marcasZ) {
    return !marcasT[i] && !marcasZ[j];
}

bool esPrometedor(const int suma, const int mejorsuma, const int prefalcanzable) {
    return !((suma + prefalcanzable) < mejorsuma);
}

void inicializarPoda(const int n, vector<vector<int>> const& T, vector<vector<int>> const& Z, vector<int>& prefmax, int& prefalcanzable) {
    vector<int>prefmaxT(n, -1);
    //max trajes
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (prefmaxT[i] == -1 || T[i][j] > prefmaxT[i])
                prefmaxT[i] = T[i][j];
        }
    }
    vector<int>prefmaxZ(n, -1);
    //max zapatos
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (prefmaxZ[i] == -1 || Z[i][j] > prefmaxZ[i])
                prefmaxZ[i] = Z[i][j];
        }
    }
    //combinamos
    for (int i = 0; i < n; i++) {
        prefmax[i] = prefmaxT[i] * prefmaxZ[i];
        prefalcanzable += prefmax[i];
    }
}

void vueltaAtras(const int n, vector<vector<int>> const& T, vector<vector<int>> const& Z, int& suma, int& mejorsuma, vector<bool>& marcasT, vector<bool>& marcasZ, vector<int>& prefmax, int& prefalcanzable, int k) {
    for (int i = 0; i < n; i++) { //Trajes
        for (int j = 0; j < n; j++) { //Zapatos
            suma += T[k][i] * Z[k][j];
            prefalcanzable -= prefmax[k];
            if (esValida(i, j, marcasT, marcasZ)) {
                if (k == n - 1) { //esSolucion
                    if (suma > mejorsuma)
                        mejorsuma = suma;
                }
                else if (k < n && esPrometedor(suma, mejorsuma, prefalcanzable)) {
                    marcasT[i] = true;
                    marcasZ[j] = true;
                    vueltaAtras(n, T, Z, suma, mejorsuma, marcasT, marcasZ, prefmax, prefalcanzable, k + 1);
                    marcasT[i] = false;
                    marcasZ[j] = false;
                }
            }
            suma -= T[k][i] * Z[k][j];
            prefalcanzable += prefmax[k];
        }
    }
}

int vueltaAtras(const int n, vector<vector<int>> const& T, vector<vector<int>> const& Z) {
    int suma = 0, mejorsuma = -1, prefalcanzable = 0;
    vector<bool> marcasT(n, false), marcasZ(n, false);
    vector<int>prefmax(n, -1);
    inicializarPoda(n, T, Z, prefmax, prefalcanzable);
    vueltaAtras(n, T, Z, suma, mejorsuma, marcasT, marcasZ, prefmax, prefalcanzable, 0);
    return mejorsuma;
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n;
    cin >> n;
    vector<vector<int>> T(n, vector<int>(n)), Z(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> T[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> Z[i][j];
        }
    }
    //Calcula el resultado
    //Escribe el resultado
    cout << vueltaAtras(n, T, Z) << '\n';
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