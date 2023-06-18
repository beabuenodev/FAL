//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

//Resuelto por búsqueda binaria - Coste O(log n)
/*
* Recurrencia:
* - Ecuación de recurrencia
* T(n) = k0               si n = 0
*        T(n div 2) + k1  si n > 0
* - Postulado
* T(n) e O(log n), siendo n el tamaño del vector.
*/

int bin_search(vector<int> const& v, int i, int f, const int d, const int iniv) {
    if (f > i) {
        int m = (i + f) / 2;
        if (m == 0)  
            return v[m] + d;
        if (m == v.size() - 1) {
            if (v[m - 1] == v[m] - d)
                return v[m] + d;
            return v[m] - d;
        }
        if (v[m - 1] != v[m] - d)
            return v[m] - d;
        if (v[m] != iniv + (d * m)) // si el numero del medio no es el deberia estar por progesion, el que falla está a la izq
            return bin_search(v, i, m, d, iniv);
        else  //si la progresion binaria es correcta, esta a la der
            return bin_search(v, m, f, d, iniv);
    } 
}

int resolver(vector<int> v, const int d) {
    if (d == 0)
        return v[0];
    return bin_search(v, 0, v.size(), d, v[0]);
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n, d, aux;
    vector<int> v;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        v.push_back(aux);
    }
    //Calcula el resultado
    //Escribe el resultado
    cout << resolver(v, d) << '\n';
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