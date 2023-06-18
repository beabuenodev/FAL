//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/* Resuelto modificando el algoritmo de mergeshort
*  Como las operaciones añadidas de mergeshort son constantes, el coste del algoritmo es igual al de mergeshort
*  Coste - O (n log n)
*/

long long int mezclar(vector <int>& v, int i, int f) {
    int m = (i + f) / 2;
    int j = m + 1, x = 0, n = f - i + 1, k = i;
    long long int c = 0;
    vector <int> aux;
    aux.resize(n);

    while (k <= m && j <= f) {
        if (v[k] <= v[j]) {
            aux[x] = v[k];
            k++;
        }
        else {
            aux[x] = v[j];
            c = c + abs(i + x - j);
            j++;
        }
        x++;
    }

    while (k <= m) {
        aux[x] = v[k];
        x++;
        k++;
    }

    while (j <= f) {
        aux[x] = v[j];
        c = c + abs(i + x - j);
        x++;
        j++;
    }

    for (int x = 0; x < n; x++) {
        v[i + x] = aux[x];
    }

    return c;
}

long long int inversiones(vector<int>& v, int i, int f) {
    long long int c = 0;
    int aux;
    if (i == f) //solo un elemento
        c = 0;
    else if (i + 1 == f) { // dos elementos
        c = 0;
        if (v[i] > v[f]) {
            aux = v[i];
            v[i] = v[f];
            v[f] = aux;
            c++;
        }
    }
    else {
        int m = (i + f) / 2;
        c += inversiones(v, i, m);
        c += inversiones(v, m + 1, f);
        c += mezclar(v, i, f);
    }
    return c;
}

long long int inversiones(vector <int>& v) {
    if (v.size() == 0 || v.size() == 1)
        return 0;
    return inversiones(v, 0, v.size() - 1);
}

void resuelveCaso() {
    //resuelve aqui tu caso
    int n, aux;
    vector <int> v;
    //Lee los datos
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        v.push_back(aux);
    }
    //Calcula el resultado
    long long int inv = inversiones(v);
    //Escribe el resultado
    cout << inv << "\n";
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