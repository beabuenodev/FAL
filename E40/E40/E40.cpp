//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/*
* noMas(v, i, j, l) = true si {#q: 0 <= i <= q < j <= v.size(): v[q] % 2 = 1 } <= l
*                     false en caso contrario
* 
* P = {k >= 0 && l >= 0 && k <= n}
* int resolver(v, n, k, l) dev r
* Q = {r = { #i,j : k < i < j < v.size() : noMas(v, i, j, l) && j - i = k} si k != 0
            n + 1 si k == 0}
*/

int resolver(vector<int> v, int n, int k, int l) {
    if (k == 0)
        return n + 1;

    int c = 0, caux = 0, laux = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] % 2 == 1) {
            laux++;
        }
        caux++;
        if (caux >= k) {
            if (i > k && v[i - k] % 2 == 1)
                laux--;
            if (laux <= l)
                c++;
        }
    }
    return c;
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n, k, l,aux;
    cin >> n >> k >> l;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        v.push_back(aux);
    }
    //Calcula el resultado
    //Escribe el resultado

    cout << resolver(v, n, k, l) << endl;
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