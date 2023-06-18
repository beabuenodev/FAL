// Beatriz Bueno Almagro

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/* Resuelto modificando el algoritmo de mergeshort
*  Como las operaciones añadidas de mergeshort son constantes, el coste del algoritmo es igual al de quicksort
*  Coste - O (n log n)
*/

int mezclar(vector <int>& v, int i, int f) {
    int m = (i + f) / 2;
    int j = m + 1, x = 0, n = f - i + 1, k = i;
    int c = 0;
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

int inversiones(vector<int>& v, int i, int f) {
    int c = 0;
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

int battlestarGalactica(vector <int>& v) {
    return inversiones(v, 0, v.size() - 1);
}

bool resuelveCaso() {

    //Leer caso de prueba: cin>>...
    int n, aux;
    vector <int> v;
    cin >> n;
    if (!std::cin)
        return false;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        v.push_back(aux);
    }
    //Resolver problema
    //Escribir resultado
    cout << battlestarGalactica(v) << "\n";
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