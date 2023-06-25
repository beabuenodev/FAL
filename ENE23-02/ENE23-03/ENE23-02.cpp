// NOMBRE Y APELLIDOS:
// DNI:

/*
 * Comentario general sobre la solución:
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

//FUNCION RECURSIVA: con los parametros adicionales que necesites
//...

//ANALISIS DEL COSTE
//RECURRENCIA: siendo el n el numero de digitos del numero
// T(n) = c0 si n = 0 
//      = c1 si n = 1
//      = T(n - 1) + c2 si n > 1
//COSTE ASINTOTICO: O(n) - coste lineal respecto a n, el numero de digitos del numero

void recursivo(int n, int pos, int& r, int& maxi, int mind) {
    if (n < 10) {
        maxi = n;
        r = n * 3 + mind;
    }
    else {
        int digito = n % 10;
        recursivo(n / 10, pos + 1, r, maxi, min(mind, digito));
        if (pos % 2 == 0)
            r += digito * 2 + maxi;
        else
            r += digito * 3 + mind;
        maxi = max(maxi, digito);
    }
}

int resolver(int n) {
    int r;
    int maxi;
    recursivo(n, 0, r, maxi, INT_MAX);
    return r;
}

void resuelveCaso() {
    int n;
    cin >> n;
    cout << resolver(n) << endl;
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("sample2.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos = 0;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}